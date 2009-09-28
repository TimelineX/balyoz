#include "GameController.h"
#include "GameFactory.h"
#include "MapProperty.h"
#define USE_SAFE
#define USE_REPORT
#define USE_ASSERT
#include "macros.h"
#include <OIS/OISInputManager.h>
#include "NxOgre.h"
#include "NxOgreVec.h"
#include "Level.h"
#include "Bullet.h"
#include "EventCollector.h"
using namespace Balyoz;
using std::list;

static GameplayInfoProvider* ms_pGameplayInfoProvider;

GameController::GameController(	
			NxOgre::World		*pNxWorld,
			NxOgre::Scene		*pNxScene,
			OGRE3DRenderSystem	*pRenderSystem,
			NxOgre::TimeController *pNxTimeController,
			Ogre::RenderWindow	*pRenderWindow, 
			Ogre::Camera		*pCamera
		)
{
	ASSERT_AND_STOP_IF_NULL( (m_pNxWorld = pNxWorld) );
	ASSERT_AND_STOP_IF_NULL( (m_pNxScene = pNxScene) );
	ASSERT_AND_STOP_IF_NULL( (m_pRenderSystem = pRenderSystem) );
	ASSERT_AND_STOP_IF_NULL( (m_pNxTimeController = pNxTimeController) );
	ASSERT_AND_STOP_IF_NULL( (m_pRenderWindow = pRenderWindow) );
	ASSERT_AND_STOP_IF_NULL( (m_pCamera = pCamera) );

	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;
	m_bBufferedJoy = false;
	m_bBufferedKeys = false;
	m_bBufferedMouse = false;

	m_pRenderWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	m_pInputManager = OIS::InputManager::createInputSystem( pl );

	//Create all devices (We only catch joystick exceptions here, as, most people have Key/Mouse)
	m_pKeyboard = static_cast<OIS::Keyboard*>(m_pInputManager->createInputObject( OIS::OISKeyboard, m_bBufferedKeys ));
	m_pMouse = static_cast<OIS::Mouse*>(m_pInputManager->createInputObject( OIS::OISMouse, m_bBufferedMouse ));
	try {
		m_pJoy = static_cast<OIS::JoyStick*>(m_pInputManager->createInputObject( OIS::OISJoyStick, m_bBufferedJoy ));
	}
	catch(...) {
		m_pJoy = 0;
	}

	//Set initial mouse clipping size
	windowResized(m_pRenderWindow);


	ms_pGameplayInfoProvider = dynamic_cast<GameplayInfoProvider*>(this);


	HumanController* hc = new HumanController();
	m_GameUnitControllers.push_back(hc);
	m_GameUnitControllerMap[hc->getName()] = hc;

	loadLevel("level-1");

	
	
}

float GameController::getFrameTime()
{
	return m_LastFrameEvent.timeSinceLastFrame;
}

void GameController::loadLevel(const std::string &levelName)
{
	Level *level = GAME_FACTORY->getLevel(levelName);
	std::list<UnitData*>::iterator it = level->m_pMapProperty->m_Units.begin();
	const std::list<UnitData*>::iterator endit = level->m_pMapProperty->m_Units.end();
	
	while(it != endit)
	{
		createGameUnit( *it );
		it++;
	}

}

GameController::~GameController(void)
{
}


GameplayInfoProvider* GameController::getInfoProvider()
{
	return ms_pGameplayInfoProvider;
}


bool GameController::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	return true;
}

bool GameController::frameStarted(const Ogre::FrameEvent& evt)
{
	m_LastFrameEvent = evt;
	m_pNxTimeController->advance(evt.timeSinceLastFrame);
	m_pMouse->capture();
	m_pKeyboard->capture();
	if(m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		return false;
	}
	runControllers();

	return true;
}

bool GameController::frameEnded(const Ogre::FrameEvent& evt)
{
	processEventQueue();
	return true;
}



GameUnit* GameController::createGameUnit(const UnitData* pUnitData)
{
	GameUnit* gu = GAME_FACTORY->getUnit(pUnitData->m_Name);
	if(!gu)
	{
		REPORT_WARNING(std::string("cannot find unit:")+ pUnitData->m_Name);
		return NULL;
	}
	NxOgre::RigidBodyDescription desc;
	desc.mDensity = 0;
	desc.mBodyFlags |= Enums::BodyFlags_FreezePositionY | Enums::BodyFlags_FreezeRotation;
	desc.mLinearDamping = 100.0f;
	NxOgre::Vec3 objectPos(pUnitData->m_Position);
	
	NxOgre::Box *box = new NxOgre::Box(1,1,2) ;
	gu->m_pBody = static_cast<PhysicsObject*>(m_pRenderSystem->createBody(box , objectPos, gu->m_Mesh.c_str(),desc));
	gu->m_pBody->m_pGameObject = gu;
	gu->m_pBody->setContactReportFlags(Enums::ContactPairFlags_All);
	
//	gu->m_pBody->
	gu->m_pBody->setContactCallback(EventCollector::getSingleton());
	float radius = 0.01f;//gu->m_pBody->getEntity()->getMesh()->getBoundingSphereRadius() / 10000.0f;
		
	gu->m_pBody->getEntity()->getParentNode()->setScale(radius*3,radius*.5,radius*3);

	if(!(m_GameUnitControllerMap[gu->m_Controller]))
	{
		REPORT_WARNING(std::string("cannot find controller:")+ gu->m_Controller);
		m_pRenderSystem->destroyBody(gu->m_pBody);
		SAFE_DELETE(gu);
		return NULL;
	}
	else
	{
		m_GameUnitControllerMap[gu->m_Controller]->registerGameObject(gu);
	}


	return gu;
}



void GameController::runControllers()
{
	list<UnitController*>::iterator it = m_GameUnitControllers.begin();	
	const list<UnitController*>::iterator endit = m_GameUnitControllers.end();	
	while(it != endit)
	{
		(*it)->run();
		it++;
	}
}
void GameController::processEventQueue()
{
}

OIS::Mouse* GameController::getMouse()
{
	return m_pMouse;
}
OIS::Keyboard* GameController::getKeyboard()
{
	return m_pKeyboard;
}

#include <cstdlib> 
#include "GameController.h"
#include "GameFactory.h"
#define USE_SAFE
#define USE_REPORT
#define USE_ASSERT
#include "macros.h"
#include <OIS/OISInputManager.h>
#include "NxOgre.h"
#include "NxOgreVec.h"
#include "Level.h"
#include "BulletController.h"
#include "EventCollector.h"
#include "Weapon.h"
#include "NxScene.h"
#include "NxActor.h"
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
	m_fGameTime = 0;

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




	//m_pBulletControllerList = GAME_FACTORY->m_pBulletControllerList;
	//HumanController* hc = new HumanController();
	//m_GameUnitControllers.push_back(hc);
	//m_GameUnitControllerMap[hc->getName()] = hc;
	//
	//UnitAIController* aic = new UnitAIController();
	//m_GameUnitControllers.push_back(aic);
	//m_GameUnitControllerMap[aic->getName()] = aic;
	loadLevel("level-1");

	
	m_pNxScene->getScene()->setActorGroupPairFlags(1,2, NxOgre::Enums::ContactPairFlags_All);
/*

	DummyBulletController* pDBC = new DummyBulletController();
	pDBC->m_pBulletControllerProperty = GAME_FACTORY->getBulletControllerProperty("dummy");
	m_BulletControllers.push_back(pDBC);
	m_BulletControllerMap["dummy"] = pDBC;
*/

	//loadLevel("level-1"); 

	//m_pNxScene->getScene()->setGroupCollisionFlag(0, 1, false);
	//m_pNxScene->getScene()->setGroupCollisionFlag(1, 1, false);

	
	
}



//void GameController::deletePhyicsObject(PhysicsObject* pPO)
//{
//	m_pRenderSystem->destroyBody((pPO));
//}
//void GameController::deleteBullet(Bullet* pBullet)
//{
//	//pBullet->m_pBulletController->unregisterGameObject(pBullet);
//	deletePhyicsObject(pBullet->m_pPhysicsObject);
//	GAME_FACTORY->m_pBulletPool->recycle(pBullet);
//}

void GameController::loadLevel(const std::string &levelName)
{
	m_pCurrentLevel = GAME_FACTORY->getLevel(levelName);
	if (m_pCurrentLevel == NULL)
	{
		REPORT_ERROR_AND_STOP(levelName+" level not found");
	}

	

	std::list<MapGameObject*>::iterator it = m_pCurrentLevel->m_pGameMap->m_pGameObjectList->begin();
	const std::list<MapGameObject*>::iterator endit = m_pCurrentLevel->m_pGameMap->m_pGameObjectList->end(); 
	m_pCurrentLevel->load(m_pRenderSystem->getSceneManager(), m_pRenderWindow,m_pCamera, m_pCamera->getParentSceneNode());
	while(it != endit)
	{
		GameUnit* gu = GAME_FACTORY->m_pGameUnitPool->get();
		GameUnit* gameunit = createGameUnit((*it));
		*(gu) = *(gameunit);
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
	m_fGameTime += evt.timeSinceLastFrame;
	//m_LastFrameEvent.timeSinceLastFrame /= 5.0f;
	//m_LastFrameEvent.timeSinceLastEvent /= 5.0f;
	m_pNxTimeController->advance(m_LastFrameEvent.timeSinceLastFrame);
	m_pMouse->capture();
	m_pKeyboard->capture();
	if(m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		return false;
	}
//	runControllers();

	return true;
}

bool GameController::frameEnded(const Ogre::FrameEvent& evt)
{
//	processEventQueue();
	return true;
}

int i=0;
//void GameController::shoot(GameUnit *pGameUnit, int iWeaponIndex)
//{
//	if (pGameUnit->m_Weapons.size() < iWeaponIndex)
//	{
//		REPORT_WARNING(std::string("weapon out of bounds for ")+pGameUnit->m_pName->c_str());
//		return;
//	}
//	Weapon *pWeapon = pGameUnit->m_Weapons[iWeaponIndex];
//	Bullet *pBullet = GAME_FACTORY->getBullet(pWeapon->m_BulletProperty);
//
//	BulletController *pBC = pWeapon->m_BulletProperty.m_pBulletController;
//	if( pBC == NULL )
//	{
//		REPORT_WARNING(std::string("cannot find controller:")+ pWeapon->m_BulletProperty.m_Controller);
//		return;
//	}
//	pBullet->m_pBulletController = pBC;
//	NxOgre::RigidBodyDescription desc;
//	desc.mBodyFlags |= Enums::BodyFlags_FreezePositionY ;//| Enums::BodyFlags_FreezeRotation;
//	NxOgre::Vec3 objectPos(pGameUnit->m_pBody->getGlobalPosition());
// 
//	NxOgre::Box *box = new NxOgre::Box(.5,.5,1) ;
//	pBullet->m_pPhysicsObject = (PhysicsObject*)(m_pRenderSystem->createBody(box , objectPos, pWeapon->m_pMeshFileName->c_str(),desc));
//
//	pBullet->m_pPhysicsObject->getNxActor()->getShapes()[0]->setGroup(1);
//	pBullet->m_pPhysicsObject->setGroup(1);
//	pBullet->m_pPhysicsObject->setLinearVelocity(NxOgre::Vec3(0,0,pBullet->m_InitialSpeed+ pGameUnit->m_pBody->getLinearVelocity().z/10.0f) ); 
//	NxOgre::Vec3 localTorque = NxOgre::Vec3(0,(rand()%(40) - 20)*(1.0f - pBC->m_fAccuracy),0) ;
//
//	pBullet->m_Force = NxOgre::Vec3((rand()%(100) - 50)/1.0f*(1.0f - pBC->m_fAccuracy),0,-.50f ); //NxOgre::Vec3(pBullet->m_pPhysicsObject->getLinearVelocity().magnitude()/10.0f*(rand()%(10) - 5)*(1.0f-pBC->m_fAccuracy),0,-1) * 3.0f; 
//	desc.mLinearDamping = 2;
//
//	pBullet->m_pPhysicsObject->setContactCallback(EventCollector::getSingleton());
//	float radius = 0.004f;
//
//
//	pBullet->m_pPhysicsObject->getEntity()->getParentNode()->setScale(radius,radius,radius*2);
//	pBullet->m_pPhysicsObject->getEntity()->setMaterialName("Examples/10PointBlock");
//	//pBC->registerGameObject(pBullet);
//
//	if(pWeapon->m_BulletProperty.m_Particles.compare("none") != 0)
//	{
//		Ogre::ParticleSystem* pSys3 = m_pRenderSystem->getSceneManager()->createParticleSystem(Ogre::StringConverter::toString(i++) + Ogre::String("fountain2"),
//			pWeapon->m_BulletProperty.m_Particles.c_str());
//		pBullet->m_pPhysicsObject->getEntity()->getParentSceneNode()->attachObject(pSys3);
//	}
//	m_pNxScene->setActorFlags(pGameUnit->m_pBody, pBullet->m_pPhysicsObject, NxOgre::Enums::ActorFlags_DisableCollision);
//	
////	m_GameUnits.push_back(pBullet);
//
//}

GameUnit* GameController::createGameUnit(const MapGameObject* pUnitMapInfo)
{
	GameUnit* pGameUnit = GAME_FACTORY->getUnit(pUnitMapInfo->m_GameUnitName);

	

	if(!pGameUnit)
	{
		REPORT_WARNING(std::string("cannot find unit:")+ (pUnitMapInfo->m_GameUnitName));
		return NULL;
	}

	NxOgre::RigidBodyDescription desc;
	desc.mBodyFlags |= Enums::BodyFlags_FreezePositionY | Enums::BodyFlags_FreezeRotation;
	desc.mLinearDamping = 40.0f;
	NxOgre::Vec3 objectPos(pUnitMapInfo->m_Position);
	

	NxOgre::Box *box = new NxOgre::Box(3,.5,3) ;
	pGameUnit->m_pBody = static_cast<PhysicsObject*>(m_pRenderSystem->createBody(box , objectPos, pGameUnit->m_pMesh->c_str(),desc));
	//	pGameUnit->m_pBody->m_pGameObject = pGameUnit;
	//pGameUnit->m_pBody->setContactReportFlags(Enums::ContactPairFlags_All);
	
//	pGameUnit->m_pBody->

	pGameUnit->m_pBody->getNxActor()->getShapes()[0]->setGroup(2);
	pGameUnit->m_pBody->setGroup(2);
	pGameUnit->m_pBody->setContactCallback(EventCollector::getSingleton());
	float radius = 0.01f;//pGameUnit->m_pBody->getEntity()->getMesh()->getBoundingSphereRadius() / 10000.0f; 
		
	pGameUnit->m_pBody->getEntity()->getParentNode()->setScale(radius*3,radius*.8,radius*3);
	pGameUnit->m_pBody->getEntity()->setMaterialName("Examples/10PointBlock");
//	UnitController* pUnitController =  m_GameUnitControllerMap[*(pGameUnit->m_pController)];
	pGameUnit->m_pBody->setContactCallback(EventCollector::getSingleton());

	//if(pUnitController == NULL)
	//{
	//	REPORT_WARNING(std::string("cannot find controller:")+ *(pGameUnit->m_pController));
	//	m_pRenderSystem->destroyBody(pGameUnit->m_pBody);
	//	SAFE_DELETE(pGameUnit);
	//	return NULL;
	//}
	//else
	//{
	//	//pUnitController->registerGameObject(pGameUnit);
	//}


//	m_GameUnits.push_back

	std::map<std::string,UnitController*>::iterator i =  GAME_FACTORY->m_UnitControllers.find(*(pGameUnit->m_pController));
	if(i != GAME_FACTORY->m_UnitControllers.end ()){
		pGameUnit->m_UnitController = i->second;
	}

	m_controllerGameObjectMap[pGameUnit->m_UnitController].push_back (pGameUnit);

	return pGameUnit;
}


int counter = 0;
//void GameController::runControllers()
//{
//	int iMod = counter % 5;
//	{
//		list<UnitController*>::iterator it = m_GameUnitControllers.begin();	
//		const list<UnitController*>::iterator endit = m_GameUnitControllers.end();	
//		while(it != endit)
//		{
//			(*it)->run();
//			it++;
//		}
//	}
//
//	if(iMod == 2)
//	{
//		list<BulletController*>::iterator it = m_pBulletControllerList->begin();	
//		const list<BulletController*>::iterator endit = m_pBulletControllerList->end();	
//		while(it != endit)
//		{
//			(*it)->run();
//			it++;
//		}
//	}
//	counter++;
//}
//void GameController::processEventQueue()
//{
//}

OIS::Mouse* GameController::getMouse()
{
	return m_pMouse;
}
OIS::Keyboard* GameController::getKeyboard()
{
	return m_pKeyboard;
}

//added by emre for new controller structure

void GameController::updateEventList(){}

void GameController::executeEventList(){}

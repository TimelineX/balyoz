#include "GameController.h"
#define USE_SAFE
#define USE_REPORT
#define USE_ASSERT
#include "macros.h"
#include <OIS/OISInputManager.h>


using namespace Balyoz;

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

}

GameController::~GameController(void)
{
}


bool GameController::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	return true;
}

bool GameController::frameStarted(const Ogre::FrameEvent& evt)
{
	runControllers();

	return true;
}

bool GameController::frameEnded(const Ogre::FrameEvent& evt)
{
	processEventQueue();
	return true;
}





void GameController::runControllers()
{
}
void GameController::processEventQueue()
{
}
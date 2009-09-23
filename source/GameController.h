#pragma once
#include <OgreMath.h>
#include <OgreFrameListener.h>
#include <OgreWindowEventUtilities.h>
#define OIS_DYNAMIC_LIB
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>
#include <OIS/OISJoyStick.h>
#include <OgreException.h>
#include <OgreCamera.h>
#include <OgreRenderWindow.h>
#include <NxOgreScene.h>
#include <NxOgreWorld.h>
#include <NxOgreTimeController.h>
#include <Ogre3DRenderSystem.h>

#include "UnitController.h"
#include "BulletController.h"
#include "MapProperty.h"
#include <list>
#include <map>


namespace Balyoz
{
	class GameplayInfoProvider
	{
	public:
		GameplayInfoProvider(){}
		~GameplayInfoProvider(){}

		virtual OIS::Mouse* getMouse() = 0;
		virtual OIS::Keyboard* getKeyboard() = 0;
	};
	
	
	class GameController :
		public Ogre::FrameListener, public Ogre::WindowEventListener, public GameplayInfoProvider
	{
	public:
		GameController(	
			NxOgre::World		*pNxWorld,
			NxOgre::Scene		*pNxScene,
			OGRE3DRenderSystem	*pRenderSystem,
			NxOgre::TimeController *pNxTimeController,
			Ogre::RenderWindow	*pRenderWindow, 
			Ogre::Camera		*pCamera
		);
		~GameController(void);
		
		bool frameEnded(const Ogre::FrameEvent& evt);
		bool frameStarted(const Ogre::FrameEvent& evt);
		bool frameRenderingQueued(const Ogre::FrameEvent& evt);

		void loadLevel(const std::string &levelName);


		void runControllers();
		void processEventQueue();	
		
		OIS::Mouse*			getMouse();
		OIS::Keyboard*		getKeyboard();

		static GameplayInfoProvider* getInfoProvider();

		GameUnit* createGameUnit(const UnitData* pUnitData);

		

		bool					m_bBufferedKeys;
		bool					m_bBufferedMouse;
		bool					m_bBufferedJoy;
		NxOgre::World			*m_pNxWorld;
		NxOgre::Scene			*m_pNxScene;
		OGRE3DRenderSystem		*m_pRenderSystem;
		NxOgre::TimeController	*m_pNxTimeController;
		Ogre::RenderWindow		*m_pRenderWindow;
		Ogre::Camera			*m_pCamera;
		OIS::InputManager		*m_pInputManager;
		OIS::Mouse				*m_pMouse;
		OIS::Keyboard			*m_pKeyboard;
		OIS::JoyStick			*m_pJoy;
		
		std::map<std::string,UnitController*>	m_GameUnitControllerMap;
		std::list<UnitController*>				m_GameUnitControllers;

		std::map<std::string,BulletController*>	m_BulletControllerMap;
		std::list<BulletController*>			m_BulletControllers;
	};

}
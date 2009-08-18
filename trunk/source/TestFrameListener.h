/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2006 Torus Knot Software Ltd
Also see acknowledgements in Readme.html

You may use this sample code for anything you like, it is not covered by the
LGPL like the rest of the engine.
-----------------------------------------------------------------------------
*/
/*
-----------------------------------------------------------------------------
Filename:    TestFrameListener.h
Description: Defines an example frame listener which responds to frame events.
This frame listener just moves a specified camera around based on
keyboard and mouse movements.
Mouse:    Freelook
W or Up:  Forward
S or Down:Backward
A:        Step left
D:        Step right
             PgUp:     Move upwards
             PgDown:   Move downwards
             F:        Toggle frame rate stats on/off
			 R:        Render mode
             T:        Cycle texture filtering
                       Bilinear, Trilinear, Anisotropic(8)
             P:        Toggle on/off display of camera position / orientation
-----------------------------------------------------------------------------
*/

#ifndef __ExampleFrameListener_H__
#define __ExampleFrameListener_H__

#include "Ogre.h"
#include "OgreStringConverter.h"
#include "OgreException.h"

//Use this define to signify OIS will be used as a DLL
//(so that dll import/export macros are in effect)
#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

using namespace Ogre;

class TestFrameListener: public FrameListener, public WindowEventListener
{
protected:
	virtual void updateStats(void)
	{
		static String currFps = "Current FPS: ";
		static String avgFps = "Average FPS: ";
		static String bestFps = "Best FPS: ";
		static String worstFps = "Worst FPS: ";
		static String tris = "Triangle Count: ";
		static String batches = "Batch Count: ";

		// update stats when necessary
		try {
			OverlayElement* guiAvg = OverlayManager::getSingleton().getOverlayElement("Core/AverageFps");
			OverlayElement* guiCurr = OverlayManager::getSingleton().getOverlayElement("Core/CurrFps");
			OverlayElement* guiBest = OverlayManager::getSingleton().getOverlayElement("Core/BestFps");
			OverlayElement* guiWorst = OverlayManager::getSingleton().getOverlayElement("Core/WorstFps");

			const RenderTarget::FrameStats& stats = m_pWindow->getStatistics();
			guiAvg->setCaption(avgFps + StringConverter::toString(stats.avgFPS));
			guiCurr->setCaption(currFps + StringConverter::toString(stats.lastFPS));
			guiBest->setCaption(bestFps + StringConverter::toString(stats.bestFPS)
				+" "+StringConverter::toString(stats.bestFrameTime)+" ms");
			guiWorst->setCaption(worstFps + StringConverter::toString(stats.worstFPS)
				+" "+StringConverter::toString(stats.worstFrameTime)+" ms");

			OverlayElement* guiTris = OverlayManager::getSingleton().getOverlayElement("Core/NumTris");
			guiTris->setCaption(tris + StringConverter::toString(stats.triangleCount));

			OverlayElement* guiBatches = OverlayManager::getSingleton().getOverlayElement("Core/NumBatches");
			guiBatches->setCaption(batches + StringConverter::toString(stats.batchCount));

			OverlayElement* guiDbg = OverlayManager::getSingleton().getOverlayElement("Core/DebugText");
			guiDbg->setCaption(mDebugText);
		}
		catch(...) { /* ignore */ }
	}

public:
	// Constructor takes a RenderWindow because it uses that to determine input context
	TestFrameListener(RenderWindow* win, Camera* cam, bool bufferedKeys = false, bool bufferedMouse = false,
			     bool bufferedJoy = false ) :
		m_pCamera(cam), m_TranslateVector(Vector3::ZERO), m_rCurrentSpeed(0), m_pWindow(win), m_bStatsOn(true), m_uiNumScreenShots(0),
		m_fMoveScale(0.0f), m_deRotScale(0.0f), m_rTimeUntilNextToggle(0), m_Filtering(TFO_BILINEAR),
		m_iAniso(1), m_iSceneDetailIndex(0), m_rMoveSpeed(100), m_dRotateSpeed(36), m_DebugOverlay(0),
		m_InputManager(0), m_pMouse(0), m_pKeyboard(0), m_pJoy(0)
	{

		m_DebugOverlay = OverlayManager::getSingleton().getByName("Core/DebugOverlay");

		LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
		OIS::ParamList pl;
		size_t windowHnd = 0;
		std::ostringstream windowHndStr;

		win->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr << windowHnd;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

		m_InputManager = OIS::InputManager::createInputSystem( pl );

		//Create all devices (We only catch joystick exceptions here, as, most people have Key/Mouse)
		m_pKeyboard = static_cast<OIS::Keyboard*>(m_InputManager->createInputObject( OIS::OISKeyboard, bufferedKeys ));
		m_pMouse = static_cast<OIS::Mouse*>(m_InputManager->createInputObject( OIS::OISMouse, bufferedMouse ));
		try {
			m_pJoy = static_cast<OIS::JoyStick*>(m_InputManager->createInputObject( OIS::OISJoyStick, bufferedJoy ));
		}
		catch(...) {
			m_pJoy = 0;
		}

		//Set initial mouse clipping size
		windowResized(m_pWindow);

		showDebugOverlay(true);

		//Register as a Window listener
		WindowEventUtilities::addWindowEventListener(m_pWindow, this);
	}

	//Adjust mouse clipping area
	virtual void windowResized(RenderWindow* rw)
	{
		unsigned int width, height, depth;
		int left, top;
		rw->getMetrics(width, height, depth, left, top);

		const OIS::MouseState &ms = m_pMouse->getMouseState();
		ms.width = width;
		ms.height = height;
	}

	//Unattach OIS before window shutdown (very important under Linux)
	virtual void windowClosed(RenderWindow* rw)
	{
		//Only close for window that created OIS (the main window in these demos)
		if( rw == m_pWindow )
		{
			if( m_InputManager )
			{
				m_InputManager->destroyInputObject( m_pMouse );
				m_InputManager->destroyInputObject( m_pKeyboard );
				m_InputManager->destroyInputObject( m_pJoy );

				OIS::InputManager::destroyInputSystem(m_InputManager);
				m_InputManager = 0;
			}
		}
	}

	virtual ~TestFrameListener()
	{
		//Remove ourself as a Window listener
		WindowEventUtilities::removeWindowEventListener(m_pWindow, this);
		windowClosed(m_pWindow);
	}

	virtual bool processUnbufferedKeyInput(const FrameEvent& evt)
	{

		if(m_pKeyboard->isKeyDown(OIS::KC_A))
			m_TranslateVector.x = -m_fMoveScale;	// Move camera left

		if(m_pKeyboard->isKeyDown(OIS::KC_D))
			m_TranslateVector.x = m_fMoveScale;	// Move camera RIGHT

		if(m_pKeyboard->isKeyDown(OIS::KC_UP) || m_pKeyboard->isKeyDown(OIS::KC_W) )
			m_TranslateVector.z = -m_fMoveScale;	// Move camera forward

		if(m_pKeyboard->isKeyDown(OIS::KC_DOWN) || m_pKeyboard->isKeyDown(OIS::KC_S) )
			m_TranslateVector.z = m_fMoveScale;	// Move camera backward

		if(m_pKeyboard->isKeyDown(OIS::KC_PGUP))
			m_TranslateVector.y = m_fMoveScale;	// Move camera up

		if(m_pKeyboard->isKeyDown(OIS::KC_PGDOWN))
			m_TranslateVector.y = -m_fMoveScale;	// Move camera down

		if(m_pKeyboard->isKeyDown(OIS::KC_RIGHT))
			m_pCamera->yaw(-m_deRotScale);

		if(m_pKeyboard->isKeyDown(OIS::KC_LEFT))
			m_pCamera->yaw(m_deRotScale);

		if( m_pKeyboard->isKeyDown(OIS::KC_ESCAPE) || m_pKeyboard->isKeyDown(OIS::KC_Q) )
			return false;

       	if( m_pKeyboard->isKeyDown(OIS::KC_F) && m_rTimeUntilNextToggle <= 0 )
		{
			m_bStatsOn = !m_bStatsOn;
			showDebugOverlay(m_bStatsOn);
			m_rTimeUntilNextToggle = 1;
		}

		if( m_pKeyboard->isKeyDown(OIS::KC_T) && m_rTimeUntilNextToggle <= 0 )
		{
			switch(m_Filtering)
			{
			case TFO_BILINEAR:
				m_Filtering = TFO_TRILINEAR;
				m_iAniso = 1;
				break;
			case TFO_TRILINEAR:
				m_Filtering = TFO_ANISOTROPIC;
				m_iAniso = 8;
				break;
			case TFO_ANISOTROPIC:
				m_Filtering = TFO_BILINEAR;
				m_iAniso = 1;
				break;
			default: break;
			}
			MaterialManager::getSingleton().setDefaultTextureFiltering(m_Filtering);
			MaterialManager::getSingleton().setDefaultAnisotropy(m_iAniso);

			showDebugOverlay(m_bStatsOn);
			m_rTimeUntilNextToggle = 1;
		}

		if(m_pKeyboard->isKeyDown(OIS::KC_SYSRQ) && m_rTimeUntilNextToggle <= 0)
		{
			std::ostringstream ss;
			ss << "screenshot_" << ++m_uiNumScreenShots << ".png";
			m_pWindow->writeContentsToFile(ss.str());
			m_rTimeUntilNextToggle = 0.5;
			mDebugText = "Saved: " + ss.str();
		}

		if(m_pKeyboard->isKeyDown(OIS::KC_R) && m_rTimeUntilNextToggle <=0)
		{
			m_iSceneDetailIndex = (m_iSceneDetailIndex+1)%3 ;
			switch(m_iSceneDetailIndex) {
				case 0 : m_pCamera->setPolygonMode(PM_SOLID); break;
				case 1 : m_pCamera->setPolygonMode(PM_WIREFRAME); break;
				case 2 : m_pCamera->setPolygonMode(PM_POINTS); break;
			}
			m_rTimeUntilNextToggle = 0.5;
		}

		static bool displayCameraDetails = false;
		if(m_pKeyboard->isKeyDown(OIS::KC_P) && m_rTimeUntilNextToggle <= 0)
		{
			displayCameraDetails = !displayCameraDetails;
			m_rTimeUntilNextToggle = 0.5;
			if (!displayCameraDetails)
				mDebugText = "";
		}

		// Print camera details
		if(displayCameraDetails)
			mDebugText = "P: " + StringConverter::toString(m_pCamera->getDerivedPosition()) +
						 " " + "O: " + StringConverter::toString(m_pCamera->getDerivedOrientation());

		// Return true to continue rendering
		return true;
	}

	virtual bool processUnbufferedMouseInput(const FrameEvent& evt)
	{

		// Rotation factors, may not be used if the second mouse button is pressed
		// 2nd mouse button - slide, otherwise rotate
		const OIS::MouseState &ms = m_pMouse->getMouseState();
		if( ms.buttonDown( OIS::MB_Right ) )
		{
			m_TranslateVector.x += ms.X.rel * 0.13;
			m_TranslateVector.y -= ms.Y.rel * 0.13;
		}
		else
		{
			m_raRotX = Degree(-ms.X.rel * 0.13);
			m_raRotY = Degree(-ms.Y.rel * 0.13);
		}

		return true;
	}

	virtual void moveCamera()
	{
		// Make all the changes to the camera
		// Note that YAW direction is around a fixed axis (freelook style) rather than a natural YAW
		//(e.g. airplane)
		m_pCamera->yaw(m_raRotX);
		m_pCamera->pitch(m_raRotY);
		m_pCamera->move(m_TranslateVector);
	}

	virtual void showDebugOverlay(bool show)
	{
		if (m_DebugOverlay)
		{
			if (show)
				m_DebugOverlay->show();
			else
				m_DebugOverlay->hide();
		}
	}

	// Override frameRenderingQueued event to process that (don't care about frameEnded)
	bool frameRenderingQueued(const FrameEvent& evt)
	{

		if(m_pWindow->isClosed())	return false;

		m_fSpeedLimit = m_fMoveScale * evt.timeSinceLastFrame;

		//Need to capture/update each device
		m_pKeyboard->capture();
		m_pMouse->capture();
		if( m_pJoy ) m_pJoy->capture();

		bool buffJ = (m_pJoy) ? m_pJoy->buffered() : true;

    	Ogre::Vector3 lastMotion = m_TranslateVector;

		//Check if one of the devices is not buffered
		if( !m_pMouse->buffered() || !m_pKeyboard->buffered() || !buffJ )
		{
			// one of the input modes is immediate, so setup what is needed for immediate movement
			if (m_rTimeUntilNextToggle >= 0)
				m_rTimeUntilNextToggle -= evt.timeSinceLastFrame;

			// Move about 100 units per second
			m_fMoveScale = m_rMoveSpeed * evt.timeSinceLastFrame;
			// Take about 10 seconds for full rotation
			m_deRotScale = m_dRotateSpeed * evt.timeSinceLastFrame;

			m_raRotX = 0;
			m_raRotY = 0;
			m_TranslateVector = Ogre::Vector3::ZERO;

		}

		//Check to see which device is not buffered, and handle it
		if( !m_pKeyboard->buffered() )
			if( processUnbufferedKeyInput(evt) == false )
				return false;
		if( !m_pMouse->buffered() )
			if( processUnbufferedMouseInput(evt) == false )
				return false;

		// ramp up / ramp down speed
    	if (m_TranslateVector == Ogre::Vector3::ZERO)
		{
			// decay (one third speed)
			m_rCurrentSpeed -= evt.timeSinceLastFrame * 0.3;
			m_TranslateVector = lastMotion;
		}
		else
		{
			// ramp up
			m_rCurrentSpeed += evt.timeSinceLastFrame;

		}
		// Limit motion speed
		if (m_rCurrentSpeed > 1.0)
			m_rCurrentSpeed = 1.0;
		if (m_rCurrentSpeed < 0.0)
			m_rCurrentSpeed = 0.0;

		m_TranslateVector *= m_rCurrentSpeed;


		if( !m_pMouse->buffered() || !m_pKeyboard->buffered() || !buffJ )
			moveCamera();

		return true;
	}

	bool frameEnded(const FrameEvent& evt)
	{
		updateStats();
		return true;
	}

protected:
	Camera* m_pCamera;

	Vector3 m_TranslateVector;
	Real m_rCurrentSpeed;
	RenderWindow* m_pWindow;
	bool m_bStatsOn;

	std::string mDebugText;

	unsigned int m_uiNumScreenShots;
	float m_fMoveScale;
	float m_fSpeedLimit;
	Degree m_deRotScale;
	// just to stop toggles flipping too fast
	Real m_rTimeUntilNextToggle ;
	Radian m_raRotX, m_raRotY;
	TextureFilterOptions m_Filtering;
	int m_iAniso;

	int m_iSceneDetailIndex ;
	Real m_rMoveSpeed;
	Degree m_dRotateSpeed;
	Overlay* m_DebugOverlay;

	//OIS Input devices
	OIS::InputManager* m_InputManager;
	OIS::Mouse*    m_pMouse;
	OIS::Keyboard* m_pKeyboard;
	OIS::JoyStick* m_pJoy;
};

#endif

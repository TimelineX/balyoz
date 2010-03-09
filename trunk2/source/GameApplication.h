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
Filename:    GameApplication.h
Description: Base class for all the OGRE examples
-----------------------------------------------------------------------------
*/

#pragma once

#include "Ogre.h"
#include "OgreConfigFile.h"
#include "TestFrameListener.h"




using namespace Ogre;

/** Base class which manages the standard startup of an Ogre application.
    Designed to be subclassed for specific examples if required.
*/
class GameApplication
{
public:
    /// Standard constructor
    GameApplication()
    {
        m_pFrameListener = 0;
        m_pRoot = 0;
		// Provide a nice cross platform solution for locating the configuration files
		// On windows files are searched for in the current working directory, on OS X however
		// you must provide the full path, the helper function macBundlePath does this for us.

		m_ResourcePath = "";
    }
    /// Standard destructor
    virtual ~GameApplication()
    {
        if (m_pFrameListener)
            delete m_pFrameListener;
        if (m_pRoot)
            OGRE_DELETE m_pRoot;
    }

    /// Start the example
    virtual void go(void)
    {
        if (!setup())
            return;

        m_pRoot->startRendering();

        // clean up
        destroyScene();
    }

protected:
    Root *m_pRoot;
    Camera* m_pCamera;
    SceneManager* m_pSceneMgr;
    TestFrameListener* m_pFrameListener;
    RenderWindow* m_pWindow;
	Ogre::String m_ResourcePath;

	virtual void init() = 0;
    // These internal methods package up the stages in the startup process
    /** Sets up the application - returns false if the user chooses to abandon configuration. */
    virtual bool setup(void)
    {

		String pluginsPath;
		// only use plugins.cfg if not static
#ifndef OGRE_STATIC_LIB
		pluginsPath = m_ResourcePath + "plugins.cfg";
#endif
		
        m_pRoot = OGRE_NEW Root(pluginsPath, 
            m_ResourcePath + "ogre.cfg", m_ResourcePath + "Ogre.log");

        setupResources();

        bool carryOn = configure();
        if (!carryOn) return false;

        chooseSceneManager();
        createCamera();
        createViewports();

        // Set default mipmap level (NB some APIs ignore this)
        TextureManager::getSingleton().setDefaultNumMipmaps(5);

		// Create any resource listeners (for loading screens)
		createResourceListener();
		// Load resources
		loadResources();

		init();
		// Create the scene
        createScene();

        createFrameListener();

        return true;

    }
    /** Configures the application - returns false if the user chooses to abandon configuration. */
    virtual bool configure(void)
    {
        // Show the configuration dialog and initialise the system
        // You can skip this and use root.restoreConfig() to load configuration
        // settings if you were sure there are valid ones saved in ogre.cfg
        if(m_pRoot->showConfigDialog())
        {
            // If returned true, user clicked OK so initialise
            // Here we choose to let the system create a default rendering window by passing 'true'
		    m_pWindow = m_pRoot->initialise(true);
            return true;
        }
        else
        {
            return false;
        }
    }

    virtual void chooseSceneManager(void)
    {
        // Create the SceneManager, in this case a generic one
        m_pSceneMgr = m_pRoot->createSceneManager(ST_GENERIC, "GAME BALYOZ");
    }
    virtual void createCamera(void)
    {
        // Create the camera
        m_pCamera = m_pSceneMgr->createCamera("PlayerCam");

        // Position it at 500 in Z direction
        m_pCamera->setPosition(Vector3(0,0,500));
        // Look back along -Z
        m_pCamera->lookAt(Vector3(0,0,-300));
        m_pCamera->setNearClipDistance(5);

    }
    virtual void createFrameListener(void)
    {
        m_pFrameListener= new TestFrameListener(m_pWindow, m_pCamera);
        m_pFrameListener->showDebugOverlay(true);
        m_pRoot->addFrameListener(m_pFrameListener);
    }

    virtual void createScene(void) = 0;    // pure virtual - this has to be overridden

    virtual void destroyScene(void){}    // Optional to override this

    virtual void createViewports(void)
    {
        // Create one viewport, entire window
        Viewport* vp = m_pWindow->addViewport(m_pCamera);
        vp->setBackgroundColour(ColourValue(0,0,0));

        // Alter the camera aspect ratio to match the viewport
        m_pCamera->setAspectRatio(
            Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
    }

    /// Method which will define the source of resources (other than current folder)
    virtual void setupResources(void)
    {
        // Load resource paths from config file
        ConfigFile cf;
        cf.load(m_ResourcePath + "resources.cfg");

        // Go through all sections & settings in the file
        ConfigFile::SectionIterator seci = cf.getSectionIterator();

        String secName, typeName, archName;
        while (seci.hasMoreElements())
        {
            secName = seci.peekNextKey();
            ConfigFile::SettingsMultiMap *settings = seci.getNext();
            ConfigFile::SettingsMultiMap::iterator i;
            for (i = settings->begin(); i != settings->end(); ++i)
            {
                typeName = i->first;
                archName = i->second;

                ResourceGroupManager::getSingleton().addResourceLocation(
                    archName, typeName, secName);
            }
        }
    }

	/// Optional override method where you can create resource listeners (e.g. for loading screens)
	virtual void createResourceListener(void)
	{

	}

	/// Optional override method where you can perform resource group loading
	/// Must at least do ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	virtual void loadResources(void)
	{
		// Initialise, parse scripts etc
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	}



};


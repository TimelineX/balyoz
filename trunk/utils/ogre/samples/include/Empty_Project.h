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

/**
    \file 
        Terrain.h
    \brief
        Specialisation of OGRE's framework application to show the
        terrain rendering plugin 
*/

#include "ExampleApplication.h"

RaySceneQuery* raySceneQuery = 0;

// Event handler to add ability to alter curvature
class EmptyApplicationFrameListener : public ExampleFrameListener
{
public:
	EmptyApplicationFrameListener(RenderWindow* win, Camera* cam, SceneNode* pSceneNode)
        : ExampleFrameListener(win, cam)
    {
        // Reduce move speed
        mMoveSpeed = 500;
		m_pSceneNode = pSceneNode;

    }
	bool frameRenderingQueued(const FrameEvent& evt)
	{
		if( ExampleFrameListener::frameRenderingQueued(evt) == false )
			return false;

		// clamp to terrain
		//static Ray updateRay;
		//updateRay.setOrigin(mCamera->getPosition());
		//updateRay.setDirection(Vector3::NEGATIVE_UNIT_Y);
		//raySceneQuery->setRay(updateRay);
		//RaySceneQueryResult& qryResult = raySceneQuery->execute();
		//RaySceneQueryResult::iterator i = qryResult.begin();
		//if (i != qryResult.end() && i->worldFragment)
		//{
		//	//mCamera->setPosition(mCamera->getPosition().x, 
		//	//	i->worldFragment->singleIntersection.y + 10, 
		//	//	mCamera->getPosition().z);
		//}
		;
		float fMultip = 1;
		Vector3 v = m_pSceneNode->getPosition();
		Vector3 translate = Vector3::ZERO;
		if (mKeyboard->isKeyDown(OIS::KC_RSHIFT))
		{
			fMultip = -1;
		} 

		if(mKeyboard->isKeyDown(OIS::KC_X))
		{
			translate.x = 10 * fMultip;
		}
		if(mKeyboard->isKeyDown(OIS::KC_Y))
		{
			translate.y = 10 * fMultip;
		}
		if(mKeyboard->isKeyDown(OIS::KC_Z))
		{
			translate.z = 10 * fMultip;
		}
		m_pSceneNode->translate(translate);

		return true;

	}

	SceneNode * m_pSceneNode;
};



class EmptyApplication : public ExampleApplication
{
public:
	EmptyApplication():ExampleApplication() {}

    ~EmptyApplication()
    {
        delete raySceneQuery;
    }

	Entity *m_pOceanSurfaceEntity;
protected:


    virtual void chooseSceneManager(void)
    {
        // Get the SceneManager, in this case a generic one
        mSceneMgr = mRoot->createSceneManager("TerrainSceneManager");
    }

    virtual void createCamera(void)
    {
        // Create the camera
        mCamera = mSceneMgr->createCamera("PlayerCam");

        // Position it at 500 in Z direction
        mCamera->setPosition(Vector3(128,25,128));
        // Look back along -Z
        mCamera->lookAt(Vector3(0,0,-300));
        mCamera->setNearClipDistance( 1 );
        mCamera->setFarClipDistance( 1000 );

    }
   
    // Just override the mandatory create scene method
    void createScene(void)
    {
        Plane waterPlane;

        // Set ambient light
        mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

        // Create a light
        Light* l = mSceneMgr->createLight("MainLight");
        // Accept default settings: point light, white diffuse, just set position
        // NB I could attach the light to a SceneNode if I wanted it to move automatically with
        //  other objects, but I don't
        l->setPosition(20,80,50);

        // Fog
        // NB it's VERY important to set this before calling setWorldGeometry 
        // because the vertex program picked will be different
        //ColourValue fadeColour(0.93, 0.86, 0.76);
        //mSceneMgr->setFog( FOG_LINEAR, fadeColour, .001, 500, 1000);
        //mWindow->getViewport(0)->setBackgroundColour(fadeColour);

        std::string terrain_cfg("terrain.cfg");
        mSceneMgr -> setWorldGeometry( terrain_cfg );
		mSceneMgr->getStaticGeometry("terrain");
        // Infinite far plane?
        if (mRoot->getRenderSystem()->getCapabilities()->hasCapability(RSC_INFINITE_FAR_PLANE))
        {
            mCamera->setFarClipDistance(0);
        }

        // Define the required skyplane
        Plane plane;
        // 5000 world units from the camera
        plane.d = 5000;
        // Above the camera, facing down
        plane.normal = -Vector3::UNIT_Y;

        // Set a nice viewpoint
        mCamera->setPosition(707,2500,528);
		mCamera->lookAt(Vector3::ZERO);
        //mRoot -> showDebugOverlay( true );

        raySceneQuery = mSceneMgr->createRayQuery(
            Ray(mCamera->getPosition(), Vector3::NEGATIVE_UNIT_Y));

		Ogre::Plane oceanSurface;
		oceanSurface.normal = Ogre::Vector3::UNIT_Y;
		oceanSurface.d = -10;
		Ogre::MeshManager::getSingleton().createPlane("OceanSurface",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			oceanSurface,
			1500, 1500, 150, 150, true, 1, 1, 1, Ogre::Vector3::UNIT_Z);
		m_pOceanSurfaceEntity = mSceneMgr->createEntity( "OceanSurface", "OceanSurface" );
		m_pOceanSurfaceEntity->setMaterialName("Ocean2_Cg");
		SceneNode *pNode;
		pNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		pNode->translate(750,0,750);
		pNode->attachObject(m_pOceanSurfaceEntity);

		mFrameListener= new EmptyApplicationFrameListener(mWindow, mCamera,pNode);
		mRoot->addFrameListener(mFrameListener);
		


    }
    // Create new frame listener
    void createFrameListener(void)
    {
    }

};

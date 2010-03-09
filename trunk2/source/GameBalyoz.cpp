#include "GameBalyoz.h"
#include "GameFactory.h"
//#include "WeaponXMLMap.h"
using namespace Balyoz;

GameBalyoz::GameBalyoz()
{
}
GameBalyoz::~GameBalyoz()
{

}

void GameBalyoz::createFrameListener(void)
{

//#ifdef _DEBUG
	m_pTestFrameListener = new GameController(m_pNxWorld,m_pNxScene,m_pRenderSystem,m_pNxTimeController, m_pWindow, m_pCamera);
	m_pRoot->addFrameListener(m_pTestFrameListener);
//#endif // _DEBUG
}



void GameBalyoz::init()
{
	REPORT_INFO("game init is starting");
	GAME_FACTORY->init();
}



void GameBalyoz::createScene(void)
{


	//Ogre::ColourValue fadeColour(0.7,0.7,.15);
	//m_pSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
	//// Create a light
	//Light* l = m_pSceneMgr->createLight("MainLight");
	//// Accept default settings: point light, white diffuse, just set position
	//// NB I could attach the light to a SceneNode if I wanted it to move automatically with
	////  other objects, but I don't
	//l->setPosition(20,80,50);

	//m_pWindow->getViewport(0)->setBackgroundColour(fadeColour);
	//m_pSceneMgr->setSkyBox(true, "SkyBox", 200);

	//	[OGRE] set up camera
	m_pCamera->setPosition(Vector3(0,35,35));
	m_pCamera->lookAt(Vector3(0,0,-100));
	m_pCamera->setNearClipDistance(1);
//	m_pSceneMgr->setFog( FOG_LINEAR, fadeColour, .04, 20, 210);
//	Ogre::Plane oceanSurface;
//	oceanSurface.normal = Ogre::Vector3::UNIT_Y;
//	oceanSurface.d = 10;
//	Ogre::MeshManager::getSingleton().createPlane("OceanSurface",
//		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
//		oceanSurface,
//		1500, 1500, 150, 150, true, 1, 1, 1, Ogre::Vector3::UNIT_Z);
//	Ogre::Entity *pOceanSurfaceEntity= m_pSceneMgr->createEntity( "OceanSurface", "OceanSurface" );
//	pOceanSurfaceEntity->setMaterialName("Ocean2_Cg");
//	SceneNode *pNode;
//	pNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
////	pNode->translate(750,0,750);
//	pNode->attachObject(pOceanSurfaceEntity);



    	//	[OGRE] create a skybox
    	//m_pSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");

	//	create NxWorld, a main physic object
	//	log: yes/no
	//	ogre time controller means rhat ogre will care about it	
		m_pNxWorld = NxOgre::World::createWorld();
		NxOgre::SceneDescription sceneDesc;
		sceneDesc.mGravity =NxOgre::Real3(0,-9.8f,0);
		sceneDesc.mName = "Hello world";
		m_pNxScene = m_pNxWorld->createScene(sceneDesc);
		NxOgre::Material *mat = m_pNxScene->getMaterial(0);
		mat->setStaticFriction(0.1);
		mat->setDynamicFriction(0.2);
		mat->setRestitution(0.5);
		
		m_pRenderSystem = new OGRE3DRenderSystem(m_pNxScene);

		m_pNxTimeController = NxOgre::TimeController::getSingleton();

		PhysicsObject* mCube;
	NxOgre::RigidBodyDescription desc;
	desc.mMass = 10;
//	mCube = m_pRenderSystem->createBody(new NxOgre::Box(10, 10, 10), NxOgre::Real3(8, 17, 0), "cube.mesh", desc);
//	mCube->getEntity()->getParentNode()->setScale(0.1,0.1,0.1);
//	m_Bodies->push_back(mCube);
//	mCube = m_pRenderSystem->createBody(new NxOgre::Box(10, 10, 10), NxOgre::Real3(8, 10, 0), "cube.mesh");
//	mBodies->push_back(mCube);
//	mCube->getEntity()->getParentNode()->setScale(0.1,0.1,0.1);
//	m_pNxScene->createSceneGeometry(new NxOgre::PlaneGeometry(0, NxOgre::Real3(0, 1, 0)), NxOgre::Matrix44(NxOgre::Matrix44::IDENTITY));
//"time-controller:ogre, log:yes"
	//	create scene, you can have maximum 32 scenes, object from one scene can't
	//	collide with objects from another (maybe in another versions :D )
	//	gravity: yes/no/0 -9.788 0
	//	floor: create infinity floor, yes/no
	//	ogre will be used as debug renderer
//"NxOgreScene", m_pSceneMgr,"gravity:yes, floor:yes, renderer:ogre"
	//	create some boxes
	//createBox(Vector3(0,10,0));
	//createBox(Vector3(1,15,0));
	////	create small box
	//createBox(Vector3(2,30,0),0.5);

//	//m_pNxScene->createActor(new Terrain(
}

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
	m_pTestFrameListener = new TestFrameListener(m_pWindow,m_pCamera);
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

	//	[OGRE] set up camera
	m_pCamera->setPosition(Vector3(0,10,20));
	m_pCamera->lookAt(Vector3(0,0,0));
	m_pCamera->setNearClipDistance(1);

	//	[OGRE] build floor
	int i = 0;
	//m_pSceneMgr->setWorldGeometry("terrain.cfg");
	StaticGeometry* s;
	s = m_pSceneMgr->createStaticGeometry("StaticFloor");
	s->setRegionDimensions(Vector3(1600.0, 1000.0, 1600.0));
	s->setOrigin(Vector3::ZERO);
	for (NxOgre::Real z = -300.0;z <= 300.0;z += 20.0)
	{
		for (NxOgre::Real x = -40.0;x <= 40.0;x += 20.0)
		{
			String name = String("Plane_") + StringConverter::toString(i++);
		
			Entity* entity = m_pSceneMgr->createEntity(name, "plane.mesh");
			entity->setQueryFlags (0);
			entity->setCastShadows(false);
			s->addEntity(entity, Vector3(x,0,z));
		}
	}
	s->build();
	//m_pSceneMgr->setWorldGeometryRenderQueue(8);


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

	OGRE3DBody* mCube;
	NxOgre::RigidBodyDescription desc;
	desc.mMass = 10;
	mCube = m_pRenderSystem->createBody(new NxOgre::Box(10, 10, 10), NxOgre::Real3(0, 50, 0), "cube.mesh", desc);
	mCube->getEntity()->getParentNode()->setScale(0.1,0.1,0.1);
//	m_Bodies->push_back(mCube);
	mCube = m_pRenderSystem->createBody(new NxOgre::Box(10, 10, 10), NxOgre::Real3(5, 80, 0), "cube.mesh");
//	mBodies->push_back(mCube);
	mCube->getEntity()->getParentNode()->setScale(0.1,0.1,0.1);
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

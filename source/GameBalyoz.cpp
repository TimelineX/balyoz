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



	m_pCamera->setPosition(Vector3(0,35,35));
	m_pCamera->lookAt(Vector3(0,0,-100));
	m_pCamera->setNearClipDistance(1);

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


}

#include "BulletController.h"
#include "GameController.h"
#include "Bullet.h"

using namespace Balyoz;
BulletController::BulletController(void)
{
}

BulletController::~BulletController(void)
{
}

void BulletController::run() 
{
	
}





DummyBulletController::DummyBulletController(void)
{
}

DummyBulletController::~DummyBulletController(void)
{
}

void DummyBulletController::run() 
{
	std::list<Bullet*>::iterator it = m_GameObjectList.begin();
	const std::list<Bullet*>::iterator endIt = m_GameObjectList.end();
	float fTime = GameController::getInfoProvider()->getFrameTime();

	while(it != endIt)
	{
		Bullet *pBullet = *it;
		if(pBullet->m_CreationTime + pBullet->m_LifeTime > fTime)
		{
			// TODO: delete bullet
		}
//		pBullet->m_pPhysicsObject->addForce(NxOgre::Vec3(0,9.8*pBullet->m_pPhysicsObject->getMass(),0));
		pBullet->m_pPhysicsObject->addLocalForce(NxOgre::Vec3(0,0,-9.8*pBullet->m_pPhysicsObject->getMass()));
		it++;
	}

}

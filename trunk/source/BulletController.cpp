#include "BulletController.h"
#include "GameController.h"
#include "Bullet.h"
#define USE_SAFE
#include "macros.h"
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
		pBullet->m_LifeTime -= fTime;
		if(pBullet->m_LifeTime < 0)
		{
			// TODO: delete bullet
			std::list<Bullet*>::iterator deleteit = it;
			it++;
			m_GameObjectList.erase(deleteit);
			GameController::getInfoProvider()->deletePhyicsObject(pBullet->m_pPhysicsObject);
			SAFE_DELETE(pBullet);
			continue;

		}
//		pBullet->m_pPhysicsObject->addForce(NxOgre::Vec3(0,9.8*pBullet->m_pPhysicsObject->getMass(),0));
//		if(pBullet->m_pPhysicsObject->getLinearVelocity().magnitudeSquared() < pBullet->m_MaximumSpeed)
			pBullet->m_pPhysicsObject->addLocalForce(pBullet->m_Force);
		it++;
	}

}

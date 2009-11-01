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
	std::list<Bullet*>::iterator it = m_GameObjectList.begin();
	const std::list<Bullet*>::iterator endIt = m_GameObjectList.end();
	float fCureentGameTime = GameController::getInfoProvider()->getGameTime();
	float fElapsedTime = fCureentGameTime - m_fLastGameTime;

	while(it != endIt)
	{
		Bullet *pBullet = *it;
		pBullet->m_fLifeTime -= fElapsedTime;
		if(pBullet->m_fLifeTime < 0)
		{
			// TODO: delete bullet
			it = m_GameObjectList.erase(it);
			GameController::getInfoProvider()->deleteBullet(pBullet);
			continue;

		}
		//		pBullet->m_pPhysicsObject->addForce(NxOgre::Vec3(0,9.8*pBullet->m_pPhysicsObject->getMass(),0));
		//		if(pBullet->m_pPhysicsObject->getLinearVelocity().magnitudeSquared() < pBullet->m_MaximumSpeed)
		//pBullet->m_pPhysicsObject->addLocalForceAtLocalPos(pBullet->m_Force,NxOgre::Vec3(0,0,-.010f));
		it++;
	}
	m_fLastGameTime = fCureentGameTime;
}




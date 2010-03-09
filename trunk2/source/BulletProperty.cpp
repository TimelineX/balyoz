#include "BulletProperty.h"
using namespace Balyoz;
BulletProperty::BulletProperty(
				float InitialSpeed, 
				float MaximumSpeed,
				float Power, 
				float Radius,
				float LifeTime,
				const std::string& Explosion, 
				const std::string& Particles, 
				const std::string& Controller,
				ENUM_EFFECT		Effect,
				BulletController* pBulletController,
				float fRocketForce
				)
{
	m_fInitialSpeed = InitialSpeed;
	m_fMaximumSpeed = MaximumSpeed;
	m_fPower = Power;
	m_fRadius = Radius;
	m_fLifeTime = LifeTime;
	m_Explosion = Explosion;
	m_Particles = Particles;
	m_Controller = Controller;
	m_Effect = Effect;
	m_pBulletController = pBulletController;
	m_fRocketForce = fRocketForce;

}

BulletProperty::BulletProperty()
{
	m_fPower = 0;
	m_fRadius = 0;
	m_fLifeTime = 0;
	m_Explosion = "";
	m_Particles = "";
	m_Controller = "";
	m_Effect = EFFECT_NONE;
	m_pBulletController = 0;
	m_fRocketForce = 0;

}
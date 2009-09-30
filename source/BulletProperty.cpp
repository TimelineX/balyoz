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
				EFFECT		Effect
				)
{
	m_InitialSpeed = InitialSpeed;
	m_MaximumSpeed = MaximumSpeed;
	m_Power = Power;
	m_Radius = Radius;
	m_LifeTime = LifeTime;
	m_Explosion = Explosion;
	m_Particles = Particles;
	m_Controller = Controller;
	m_Effect = Effect;

}

BulletProperty::BulletProperty()
{
	m_Power = 0;
	m_Radius = 0;
	m_LifeTime = 0;
	m_Explosion = "";
	m_Particles = "";
	m_Controller = "";
	m_Effect = EFFECT::NONE;

}
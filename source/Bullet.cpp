#include "Bullet.h"
#define USE_SAFE
#include "macros.h"
using namespace Balyoz;

Bullet::Bullet()
{
}
Bullet::Bullet(const std::string& name)
:GameObject(name)
{
	setBulletProperty(BulletProperty());
}
Bullet::Bullet(	const std::string& name,
		const BulletProperty &bulletProperty
		):GameObject(name)
{
	setBulletProperty(bulletProperty);
}

Bullet::Bullet(	const BulletProperty &bulletProperty )
{
	setBulletProperty(bulletProperty);
}
Bullet::~Bullet(void)
{
	//SAFE_DELETE(m_pPhysicsObject);
}
void Bullet::setBulletProperty(const BulletProperty &bulletProperty )
{
	m_MaximumSpeed = bulletProperty.m_MaximumSpeed;
	m_InitialSpeed = bulletProperty.m_InitialSpeed;
	m_Effect = bulletProperty.m_Effect;
	m_LifeTime = bulletProperty.m_LifeTime;
	m_Power = bulletProperty.m_Power;
	m_Radius = bulletProperty.m_Radius;
}
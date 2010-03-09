#include "Bullet.h"
#define USE_SAFE
#include "macros.h"
using namespace Balyoz;

Bullet::Bullet()
{
}
Bullet::Bullet( std::string* name)
:GameObject(name)
{
	setBulletProperty(BulletProperty());
}
Bullet::Bullet( std::string* name,
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

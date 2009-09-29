#include "Bullet.h"
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
}
void Bullet::setBulletProperty(const BulletProperty &bulletProperty )
{
}
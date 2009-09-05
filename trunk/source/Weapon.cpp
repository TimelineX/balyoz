#include "Weapon.h"

Balyoz::Weapon::Weapon(void)
{
	bullet = new Bullet();
}

Balyoz::Weapon::~Weapon(void)
{
	
}

Balyoz::Weapon::Weapon(const std::string& name) : GameObject(name){

	bullet  = new Bullet();
}

Balyoz::Weapon::Weapon(const std::string& Name, 
					   const std::string& MeshFileName, 
					   unsigned int ReloadTime, 
					   unsigned int Capacity, 
					   unsigned int Initial, 
					   unsigned int Maximum, 
					   unsigned int Minimum, 
					   unsigned int Angle, 
					   unsigned int Power, 
					   float		Radius, 
					   unsigned int LifeTime, 
					   const std::string& Explosion, 
					   const std::string& Particles, 
					   const std::string& Controller, 
					   EFFECT Effect) : GameObject(Name){

						   
					   m_MeshFileName	= MeshFileName;
					   m_ReloadTime		= ReloadTime;
					   m_capacity		= Capacity;
					   m_Initial		= Initial;
					   m_Maximum		= Maximum;
					   m_Minimum		= Minimum;
					   m_BulletAngle	= Angle;
					   bullet = new Bullet(Power,Radius,Effect,LifeTime,Explosion,Particles,Controller);
}
#include "Weapon.h"

Balyoz::Weapon::Weapon(void)
{
	bullet = new Bullet();
}

Balyoz::Weapon::~Weapon(void)
{
	
}

Balyoz::Weapon::Weapon(std::string name){
	m_Name	= name;
	bullet  = new Bullet();
}

Balyoz::Weapon::Weapon(std::string Name, 
					   std::string MeshFileName, 
					   unsigned int ReloadTime, 
					   unsigned int Capacity, 
					   unsigned int Initial, 
					   unsigned int Maximum, 
					   unsigned int Minimum, 
					   unsigned int Angle, 
					   unsigned int Power, 
					   unsigned int Radius, 
					   unsigned int LifeTime, 
					   std::string Explosion, 
					   std::string Particles, 
					   std::string Controller, 
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
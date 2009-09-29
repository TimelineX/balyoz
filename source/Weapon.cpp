#include "Weapon.h"
using namespace Balyoz;




Weapon::Weapon(void)
{
	   m_LastShootTime	= 0;

}

Weapon::~Weapon(void)
{
	
}

Weapon::Weapon(const std::string& name) : GameObject(name){

}

Weapon::Weapon(const std::string& Name, 
					   const std::string& MeshFileName, 
					   float		ReloadTime, 
					   unsigned int Capacity, 
					   unsigned int Initial, 
					   unsigned int Maximum, 
					   unsigned int Minimum, 
					   unsigned int Angle, 
					   float		Power, 
					   float		Radius, 
					   float		LifeTime, 
					   const std::string& Explosion, 
					   const std::string& Particles, 
					   const std::string& Controller, 
					   EFFECT Effect) 
					   : GameObject(Name), 
					   m_BulletProperty(Power,Radius,LifeTime,Explosion,Particles,Controller,Effect){

						   
					   m_MeshFileName	= MeshFileName;
					   m_ReloadTime		= ReloadTime;
					   m_LastShootTime	= 0;
					   m_capacity		= Capacity;
					   m_Initial		= Initial;
					   m_Maximum		= Maximum;
					   m_Minimum		= Minimum;
					   m_BulletAngle	= Angle;
}
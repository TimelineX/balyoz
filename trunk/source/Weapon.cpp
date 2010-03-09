#include "Weapon.h"
using namespace Balyoz;




Weapon::Weapon(void)
{
	   m_LastShootTime	= 0;

}

Weapon::~Weapon(void)
{
	
}

Weapon::Weapon( std::string* pName) : GameObject(pName){

}

Weapon::Weapon( std::string* pName, 
				std::string* pMeshFileName, 
				float		ReloadTime, 
				unsigned int Capacity, 
				unsigned int Initial, 
				unsigned int Maximum, 
				unsigned int Minimum, 
				unsigned int Angle, 
				float		InitialSpeed, 
				float		MaximumSpeed,
				float		Power, 
				float		Radius, 
				float		LifeTime, 
				const std::string& Explosion, 
				const std::string& Particles, 
				const std::string& Controller, 
				ENUM_EFFECT Effect) 
				: GameObject(pName), 
				m_BulletProperty(InitialSpeed, MaximumSpeed, Power,Radius,LifeTime,Explosion,Particles,Controller,Effect){

						   
					   m_pMeshFileName	= pMeshFileName;
					   m_ReloadTime		= ReloadTime;
					   m_LastShootTime	= 0;
					   m_Capacity		= Capacity;
					   m_Initial		= Initial;
					   m_Maximum		= Maximum;
					   m_Minimum		= Minimum;
					   m_BulletAngle	= Angle;
}
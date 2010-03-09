#include "Weapon.h"
using namespace Balyoz;




Weapon::Weapon(void)
{
	m_pMeshFileName	= 0;
	m_fReloadTime		= 0;
	m_fLastShootTime	= 0;
	m_uiCapacity		= 0;
	m_uiInitial		= 0;
	m_uiMaximum		= 0;
	m_uiMinimum		= 0;
	m_uiBulletAngle	= 0;
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
					   m_fReloadTime		= ReloadTime;
					   m_fLastShootTime	= 0;
					   m_uiCapacity		= Capacity;
					   m_uiInitial		= Initial;
					   m_uiMaximum		= Maximum;
					   m_uiMinimum		= Minimum;
					   m_uiBulletAngle	= Angle;
}
#pragma once
#include "GameObject.h"
#include <string>
#include "Bullet.h"
namespace Balyoz{



class Weapon : public GameObject
{
public:
	Weapon(void);
	Weapon( std::string* pName);
	Weapon(		std::string* pName, 
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
				ENUM_EFFECT Effect) ;

	~Weapon(void);

	BulletProperty	m_BulletProperty;
	std::string*	m_pMeshFileName;
	float			m_fLastShootTime;
	float			m_fReloadTime;
	unsigned int	m_uiCapacity;
	unsigned int	m_uiInitial;
	unsigned int	m_uiMaximum;
	unsigned int	m_uiMinimum;
	unsigned int	m_uiBulletAngle;


};
}
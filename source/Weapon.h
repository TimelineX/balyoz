#pragma once
#include "GameObject.h"
#include <string>
#include "Bullet.h"
namespace Balyoz{



class Weapon : public GameObject
{
public:
	Weapon(void);
	Weapon(const std::string& name);
	Weapon(		const std::string& Name, 
				const std::string& MeshFileName, 
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
				EFFECT Effect) ;

	~Weapon(void);

	BulletProperty	m_BulletProperty;
	std::string		m_MeshFileName;
	float			m_LastShootTime;
	float			m_ReloadTime;
	unsigned int	m_capacity;
	unsigned int	m_Initial;
	unsigned int	m_Maximum;
	unsigned int	m_Minimum;
	unsigned int	m_BulletAngle;


};
}
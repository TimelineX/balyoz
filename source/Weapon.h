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
	Weapon(		const std::string&		Name,
				const std::string&		MeshFileName,
				unsigned int	ReloadTime,
				unsigned int	Capacity,
				unsigned int	Initial,
				unsigned int	Maximum,
				unsigned int	Minimum,
				unsigned int	Angle,
				unsigned int	Power,
				float			Radius,
				unsigned int	LifeTime,
				const std::string&		Explosion,
				const std::string&		Particles,
				const std::string&		Controller,
				EFFECT			Effect);

	~Weapon(void);

	Bullet* bullet;	
	std::string		m_MeshFileName;
	unsigned int	m_ReloadTime;
	unsigned int	m_capacity;
	unsigned int	m_Initial;
	unsigned int	m_Maximum;
	unsigned int	m_Minimum;
	unsigned int	m_BulletAngle;

};
}
#pragma once
#include "GameObject.h"
#include <string>
#include "Bullet.h"
namespace Balyoz{


class Weapon : public GameObject
{
public:
	Weapon(void);
	Weapon(std::string name);
	Weapon(		std::string		Name,
				std::string		MeshFileName,
				unsigned int	ReloadTime,
				unsigned int	Capacity,
				unsigned int	Initial,
				unsigned int	Maximum,
				unsigned int	Minimum,
				unsigned int	Angle,
				unsigned int	Power,
				unsigned int	Radius,
				unsigned int	LifeTime,
				std::string		Explosion,
				std::string		Particles,
				std::string		Controller,
				EFFECT			Effect);

	~Weapon(void);

	Bullet* bullet;
	std::string		m_Name;
	std::string		m_MeshFileName;
	unsigned int	m_ReloadTime;
	unsigned int	m_capacity;
	unsigned int	m_Initial;
	unsigned int	m_Maximum;
	unsigned int	m_Minimum;
	unsigned int	m_BulletAngle;

};
}
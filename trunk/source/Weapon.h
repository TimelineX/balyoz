#pragma once
#include "GameObject.h"
#include <string>

namespace Balyoz{

	enum EFFECT{
		LINEER,
		EXPONENTIAL,
		NONE
	};

class Weapon : public GameObject
{
public:
	Weapon(void);
	Weapon(std::string name);
	Weapon(		std::string		Name,
				std::string		MeshFileName,
				unsigned int	Power,
				unsigned int	Radius,
				unsigned int	LifeTime,
				std::string		Explosion,
				std::string		Particles,
				std::string		Controller,
				EFFECT			Effect);
	~Weapon(void);

	std::string		m_Name;
	std::string		m_MeshFileName;
	unsigned int	m_Power;
	unsigned int	m_Radius;
	unsigned int	m_LifeTime;
	std::string		m_Explosion;
	std::string		m_Particles;
	std::string		m_Controller;
	EFFECT			m_Effect;


};
}
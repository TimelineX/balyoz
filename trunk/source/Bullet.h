#pragma once
#include "gameobject.h"

enum EFFECT{
	LINEER,
	EXPONENTIAL,
	NONE
};
class Bullet :
	public GameObject
{
public:
	Bullet(void);
	Bullet(std::string name);
	Bullet(	unsigned int	Power,
			unsigned int	m_Radius,
			EFFECT			m_Effect,	
			unsigned int	m_LifeTime,
			std::string		m_Explosion,
			std::string		m_Particles,
			std::string		m_Controller
			);
	~Bullet(void);

	unsigned int	m_Power;
	unsigned int	m_Radius;
	EFFECT			m_Effect;	
	unsigned int	m_LifeTime;
	std::string		m_Explosion;
	std::string		m_Particles;
	std::string		m_Controller;
};

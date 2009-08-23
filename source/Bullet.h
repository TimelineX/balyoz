#pragma once
#include "GameObject.h"

enum EFFECT{
	LINEER,
	EXPONENTIAL,
	NONE
};
class Bullet :
	public GameObject
{
public:
	Bullet();
	Bullet(std::string name);
	Bullet(	std::string name,
			unsigned int Power, 
			unsigned int Radius,
			unsigned int LifeTime,
			std::string Explosion, 
			std::string Particles, 
			std::string Controller,
			EFFECT		Effect
			);
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

private:
	void setBulletAttributes(unsigned int pow, unsigned int radius,unsigned int lifetime,
		std::string explosion, std::string particles, std::string controller, EFFECT effect);
};

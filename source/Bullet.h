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
	Bullet(const std::string& name);
	Bullet(	std::string name,
			unsigned int Power, 
			float Radius,
			unsigned int LifeTime,
			const std::string& Explosion, 
			const std::string& Particles, 
			const std::string& Controller,
			EFFECT		Effect
			);
	Bullet(	unsigned int	Power,
		float				m_Radius,
		EFFECT				m_Effect,	
		unsigned int		m_LifeTime,
		const std::string&	m_Explosion,
		const std::string&	m_Particles,
		const std::string&	m_Controller
		);
	~Bullet(void);

	unsigned int	m_Power;
	float			m_Radius;
	EFFECT			m_Effect;	
	unsigned int	m_LifeTime;
	std::string		m_Explosion;
	std::string		m_Particles;
	std::string		m_Controller;

private:
	void setBulletAttributes(unsigned int pow, float radius,unsigned int lifetime,
		const std::string& explosion, const std::string& particles, const std::string& controller, EFFECT effect);
};

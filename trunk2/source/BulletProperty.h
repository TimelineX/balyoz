#pragma once
#include <string>


/**
*	this class holds all the information
*	for creating a bullet including static
*	attributes including explosion or particles.
*	Objects of this class should be owned by weapon
*	so that bullets can be created in the game controller
**/
namespace Balyoz
{
	class BulletController;
	enum ENUM_EFFECT{
		EFFECT_NONE = 0,
		EFFECT_LINEER,
		EFFECT_EXPONENTIAL
	}; 
	class BulletProperty 
	{
	public:
		BulletProperty();
		BulletProperty(
				float InitialSpeed, 
				float MaximumSpeed,
				float Power, 
				float Radius,
				float LifeTime,
				const std::string& Explosion, 
				const std::string& Particles, 
				const std::string& Controller,
				ENUM_EFFECT		Effect,
				BulletController* pBulletController = 0,
				float fRocketForce = 0 
				);

		~BulletProperty(void){};

		BulletController*	m_pBulletController;

		float			m_fRocketForce;
		float			m_fMaximumSpeed;
		float			m_fInitialSpeed;
		float			m_fPower;
		float			m_fRadius;
		ENUM_EFFECT		m_Effect;	
		float			m_fLifeTime;
		std::string		m_Explosion;
		std::string		m_Particles;
		std::string		m_Controller;

	};
};
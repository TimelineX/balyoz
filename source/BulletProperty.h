#pragma once
#include <string>
namespace Balyoz
{
	enum EFFECT{
		LINEER,
		EXPONENTIAL,
		NONE
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
				EFFECT		Effect
				);

		~BulletProperty(void){};

		float			m_MaximumSpeed;
		float			m_InitialSpeed;
		float			m_Power;
		float			m_Radius;
		EFFECT			m_Effect;	
		float			m_LifeTime;
		std::string		m_Explosion;
		std::string		m_Particles;
		std::string		m_Controller;

	};
};
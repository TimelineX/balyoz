#pragma once

#include "BulletProperty.h"
#include "NxOgreVec.h"
#include "GameObject.h"
#include "PhysicsObject.h"
namespace Balyoz
{

	class BulletController;
	class Bullet :
		public GameObject
	{
	public:
		Bullet();
		Bullet( std::string* name);
		Bullet(	std::string* name,
				const BulletProperty &bulletProperty
				);
		Bullet(	const BulletProperty &bulletProperty );
		~Bullet(void);
		void setBulletProperty(const BulletProperty &bulletProperty )
		{
			m_fMaximumSpeed = bulletProperty.m_fMaximumSpeed;
			m_fInitialSpeed = bulletProperty.m_fInitialSpeed;
			m_Effect = bulletProperty.m_Effect;
			m_fLifeTime = bulletProperty.m_fLifeTime;
			m_fPower = bulletProperty.m_fPower;
			m_fRadius = bulletProperty.m_fRadius;
		};
		
		float			m_fInitialSpeed;
		float			m_fMaximumSpeed;
		float			m_fPower;
		float			m_fRadius;
		float			m_fLifeTime;
		float			m_fCreationTime;
		ENUM_EFFECT		m_Effect;
		NxOgre::Vec3	m_Force;

		PhysicsObject*	m_pPhysicsObject;

		BulletController	*m_pBulletController;

		



	};

}
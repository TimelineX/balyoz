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
			m_MaximumSpeed = bulletProperty.m_MaximumSpeed;
			m_InitialSpeed = bulletProperty.m_InitialSpeed;
			m_Effect = bulletProperty.m_Effect;
			m_LifeTime = bulletProperty.m_LifeTime;
			m_Power = bulletProperty.m_Power;
			m_Radius = bulletProperty.m_Radius;
		};
		
		float			m_InitialSpeed;
		float			m_MaximumSpeed;
		float			m_Power;
		float			m_Radius;
		float			m_LifeTime;
		float			m_CreationTime;
		ENUM_EFFECT		m_Effect;
		NxOgre::Vec3	m_Force;

		PhysicsObject*	m_pPhysicsObject;

		BulletController	*m_pBulletController;

		



	};

}
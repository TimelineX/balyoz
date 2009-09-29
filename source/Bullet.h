#pragma once

#include "PhysicsObject.h"
#include "BulletProperty.h"
#include "NxOgreVec.h"
#include "GameObject.h"
namespace Balyoz
{

	class Bullet :
		public GameObject
	{
	public:
		Bullet();
		Bullet(const std::string& name);
		Bullet(	const std::string& name,
				const BulletProperty &bulletProperty
				);
		Bullet(	const BulletProperty &bulletProperty );
		~Bullet(void);
		void setBulletProperty(const BulletProperty &bulletProperty );
		
		float			m_Power;
		float			m_Radius;
		float			m_LifeTime;
		float			m_CreationTime;
		EFFECT			m_Effect;
		NxOgre::Vec3	m_Force;

		PhysicsObject*	m_pPhysicsObject;

		



	};

}
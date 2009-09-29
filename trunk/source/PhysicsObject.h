#pragma once
#include "ogre3dbody.h"

namespace Balyoz
{
	class GameObject;

	class PhysicsObject :
		public OGRE3DBody
	{
	public:
		~PhysicsObject(void);

		GameObject		*m_pGameObject;
	};
};
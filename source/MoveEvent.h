#pragma once

#include "IEvent.h"
#include "GameUnit.h"
//#include "NxOgreVec.h"



namespace Balyoz{

	class MoveEvent
		: public IEvent{

	public:

		MoveEvent(GameUnit* g, NxOgre_Namespace::Vec3 gp);
		~MoveEvent();

		GameUnit* m_unit;
		NxOgre::Vec3 m_position;
	};
}
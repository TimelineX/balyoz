#pragma once


namespace Balyoz{

	class IEvent{

	public:
		enum EVENT_TYPE{
			ILLEGAL_EVENT = 0,
			MOVE_EVENT,
			SHOOT_EVENT,
			AIM_EVENT
		};

		EVENT_TYPE m_type;
	};

}
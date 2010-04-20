#pragma once

#include <vector>
#include "GameObject.h"

namespace Balyoz
{
	enum ControllerType
	{
		CONTROLLER_NONE = 0,
		CONTROLLER_HUMAN = 1<<8,
		CONTROLLER_AI = 1<<16
	};

	enum CONTROLLER_PRIORITY{
		HIGH = 100,
		MEDIUM = 1000,
		LOW = 10000
	};
	
	class Controller
	{
	public:

		Controller(void){
			m_ControllerType = CONTROLLER_NONE; 
			m_ControllerPriority = MEDIUM; 
		};
		Controller(ControllerType ctype, CONTROLLER_PRIORITY priority){ 
			m_ControllerType = ctype; 
			m_ControllerPriority = priority;
		};
		~Controller(void){};
		
		virtual void run(std::vector<GameObject*>& eventList, GameObject* gameObj) = 0;		
		
		ControllerType				m_ControllerType;
		CONTROLLER_PRIORITY			m_ControllerPriority;
	};
}
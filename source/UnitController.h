#pragma once
#include "Controller.h"
#include "GameUnit.h"
#include <list>

#define OIS_DYNAMIC_LIB
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>


namespace Balyoz
{
	class UnitController : public Controller
	{
	public:
		UnitController(void){}
		UnitController(ControllerType ctype, CONTROLLER_PRIORITY p):Controller(ctype,p){}
		~UnitController(void){}
		std::string& getName(){return m_Name;};

		std::string m_Name;

	};


	class HumanController
		: public UnitController
	{
	public:
		HumanController();
		~HumanController();
		void run(std::vector<GameObject*>& eventList, GameObject* gameObj) ;


		OIS::Mouse*			m_pMouse;
		OIS::Keyboard*		m_pKeyboard;

		NxOgre::Vec3		m_TranslateVec;

	};



	class UnitAIController
		: public UnitController
	{
	public:
		UnitAIController();
		~UnitAIController();
		void run(std::vector<GameObject*>& eventList, GameObject* gameObj) ;

	};
};
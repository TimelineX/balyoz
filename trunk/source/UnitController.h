#pragma once
#include "Controller.h"
#include "GameUnit.h"
#include <list>

#define OIS_DYNAMIC_LIB
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>


namespace Balyoz
{
	class UnitController : public Controller<GameUnit>
	{
	public:
		UnitController(void){}
		UnitController(ControllerType ctype):Controller<GameUnit>(ctype){}
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
		void run() ;


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
		void run() ;

	};
};
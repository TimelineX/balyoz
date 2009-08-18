#pragma once
#include "Controller.h"
#include "GameUnit.h"
#include <list>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>


namespace Balyoz
{
	template<typename RunInfo>
	class UnitController : public Controller<GameUnit,RunInfo>
	{
	public:
		UnitController(void){}
		~UnitController(void){}

	};

	typedef struct
	{
		OIS::Keyboard	*m_pKeyboard;
		OIS::Mouse		*m_pMouse;
	}RunInfoDevices;

	class UnitMouseKeyboardController
		: public UnitController<RunInfoDevices>
	{
	public:
		UnitMouseKeyboardController(RunInfoDevices * runInfo);
		~UnitMouseKeyboardController();
		void run() ;

	};



	class UnitAIController
		: public UnitController<std::list<GameUnit*>>
	{
	public:
		UnitAIController();
		~UnitAIController();
		void run() ;

	};
};
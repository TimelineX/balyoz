#include "UnitController.h"
using namespace Balyoz;



UnitMouseKeyboardController::UnitMouseKeyboardController(RunInfoDevices * runInfo)
{
	setRunInfo(runInfo);
}

UnitMouseKeyboardController::~UnitMouseKeyboardController()
{
}


void UnitMouseKeyboardController::run()
{
//	const OIS::MouseState &ms = m_pRunInfoParameter->m_pMouse->getMouseState();
	std::list<GameUnit*>::iterator it = m_GameObjectList.begin();
	const std::list<GameUnit*>::iterator endIt = m_GameObjectList.end();
	
	while(it != endIt)
	{
		it++;
	}

}

UnitAIController::UnitAIController()
{
}
UnitAIController::~UnitAIController()
{
}


void UnitAIController::run()
{
	
}
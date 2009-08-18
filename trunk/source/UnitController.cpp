#include "UnitController.h"
using namespace Balyoz;

UnitController::UnitController(void)
{
}

UnitController::~UnitController(void)
{
}

void UnitController::registerUnit(GameUnit* pGameUnit)
{
	m_GameUnits.push_back(pGameUnit);
}
void UnitController::unregisterUnit(GameUnit* pGameUnit)
{
	m_GameUnits.remove(pGameUnit);
}
void UnitController::unregisterUnit(std::string &gameUnitName)
{
	std::list<GameUnit*>::iterator it = m_GameUnits.begin();
	std::list<GameUnit*>::iterator endIt = m_GameUnits.end();
	while(it != endIt)
	{
	if( (*it)->m_Name.compare(gameUnitName) == 0 )
		{
			
			m_GameUnits.erase(it);
			return;
		}
		it++;
	}

}

void UnitController::run()
{

}
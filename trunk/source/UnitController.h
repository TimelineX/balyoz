#pragma once
#include "GameUnit.h"
#include <list>

namespace Balyoz
{
	class UnitController
	{
	public:
		UnitController(void);
		~UnitController(void);

		void registerUnit(GameUnit* pGameUnit);
		void unregisterUnit(GameUnit* pGameUnit);
		void unregisterUnit(std::string &gameUnitName);

		void run();

		std::list<GameUnit*> m_GameUnits;	
	};
}
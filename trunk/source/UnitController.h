#pragma once
#include "Controller.h"
#include "GameUnit.h"
#include <list>

namespace Balyoz
{
	class UnitController : public Controller<GameUnit>
	{
	public:
		UnitController(void);
		~UnitController(void);

		void run();
	};
}
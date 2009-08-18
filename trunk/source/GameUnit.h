#pragma once
#include "gameobject.h"
#include <string>

namespace Balyoz{

class GameUnit :
	public GameObject
{
public:
	GameUnit(void);
	~GameUnit(void);

	std::string m_Name;
	
};
}
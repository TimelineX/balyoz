#pragma once
#include <string>
#include "GameUnit.h"

namespace Balyoz{

class Terrain
	: GameObject
{
public:
	Terrain(void);
	Terrain(std::string name);
	~Terrain(void);


	std::string m_Name;
};

}


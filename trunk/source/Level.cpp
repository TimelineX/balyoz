#include "Level.h"
#include "GameMap.h"
#define USE_SAFE
#include "macros.h"

using namespace Balyoz;
Level::Level(const std::string name )
{
	m_Name = name;
}

Level::~Level(void)
{
	SAFE_DELETE(m_pGameMap);
}

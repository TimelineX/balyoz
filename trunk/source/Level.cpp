#include "Level.h"

using namespace Balyoz;
Level::Level(LevelProperty *pLevelProperty, MapProperty *pMapProperty)
{
	m_pLevelProperty = pLevelProperty;
	m_pMapProperty = pMapProperty;
}

Level::~Level(void)
{
}

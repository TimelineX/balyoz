#pragma once

#include "LevelProperty.h"
#include "MapProperty.h"

namespace Balyoz{


class Level
{
public:
	Level(LevelProperty *pLevelProperty, MapProperty *pMapProperty);
	~Level(void);

	LevelProperty *m_pLevelProperty;
	MapProperty *m_pMapProperty;
};
}

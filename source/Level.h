#pragma once
#include <string>
namespace Balyoz{

class GameMap;
class Level
{
public:
	Level(const std::string name = std::string(""));
	~Level(void);
	std::string m_Name;
	std::string m_Terrain;
	std::string m_MapName;
	GameMap *m_pGameMap;
	std::string m_SkyBox;

};
}

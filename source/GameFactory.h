#pragma once
#include "XMLMapRepostory.h"

#include "WeaponProperty.h"
#include "LevelProperty.h"
#include "UnitProperty.h"
#include "TerrainProperty.h"
#include "MapProperty.h"
#include "GameProperty.h"



#include <map>
#include <string>

#define GAME_FACTORY GameFactory::getSingleton()

namespace Balyoz
{
class Level;
class GameMap;
class Terrain;
class GameUnit;
class Weapon;
};
class GameFactory
{
public:
	~GameFactory(void);

	bool init();
	
	void createXmlMapRepostories();

	static GameFactory* getSingleton();

	Balyoz::Level*		getLevel	(const std::string& levelName);
	Balyoz::GameMap*	getMap	    (const std::string& mapName);
	Balyoz::Terrain*	getTerrain	(const std::string& terrainName);
	Balyoz::GameUnit*   getUnit		(const std::string& unitName);
	Balyoz::Weapon*		getWeapon	(const std::string& weaponName);

protected:
	GameFactory(void);

	XMLMapRepostory<WeaponProperty>*	m_pWeaponXMLMap;
	XMLMapRepostory<UnitProperty>*		m_pUnitXMLMap;
	XMLMapRepostory<TerrainProperty>*	m_pTerrainXMLMap;
	XMLMapRepostory<MapProperty>*		m_pMapXMLMap;
	XMLMapRepostory<LevelProperty>*		m_pLevelXMLMap;
	XMLMapRepostory<GameProperty>*		m_pGameXMLMap;
};

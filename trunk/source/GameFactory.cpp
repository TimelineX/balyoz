#include "GameFactory.h"

GameFactory::GameFactory(void)
{
}

GameFactory::~GameFactory(void)
{
}

bool GameFactory::init()
{
	REPORT_INFO("init game factory is starting");

	createXmlMapRepostories();
	return true;

}
void GameFactory::createXmlMapRepostories()
{


	m_pWeaponXMLMap = (new XMLMapRepostory<WeaponProperty>("weapon bean"));
	m_pWeaponXMLMap->initFromXml( "weapons.xml" ,"weapons", "weapon" );

	m_pUnitXMLMap = (new XMLMapRepostory<UnitProperty>("unit bean"));
	m_pUnitXMLMap->initFromXml( "units.xml" ,"units", "unit" );
	
	m_pTerrainXMLMap = (new XMLMapRepostory<TerrainProperty>("terrain bean"));
	m_pTerrainXMLMap->initFromXml("terrains.xml","terrains","terrain");
	
	m_pMapXMLMap =  (new XMLMapRepostory<MapProperty>("map bean"));
	m_pMapXMLMap->initFromXml("maps.xml","maps","map");

	m_pLevelXMLMap = (new XMLMapRepostory<LevelProperty>("level bean"));
	m_pLevelXMLMap->initFromXml( "levels.xml" ,"levels", "level" );

	m_pGameXMLMap = (new XMLMapRepostory<GameProperty>("game bean"));
	m_pGameXMLMap->initFromXml( "game.xml" ,"games", "game" );

}
static GameFactory *sg_pGameFactory = 0;

GameFactory* GameFactory::getSingleton()
{
	if(sg_pGameFactory == 0 )
	{
		sg_pGameFactory = new GameFactory();
	}
	return sg_pGameFactory;
}

Level* GameFactory::getLevel(std::string levelName){
return NULL;
}
Map* GameFactory::getMap(std::string mapName){
return NULL;
}
Terrain* GameFactory::getTerrain(std::string terrainName){
return NULL;
}
GameUnit* GameFactory::getUnit(std::string unitName){
return NULL;
}
Weapon* GameFactory::getWeapon(std::string weaponName){
return NULL;
}


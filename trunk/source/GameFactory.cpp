#include "GameFactory.h"
#include "Weapon.h"
#include <map>
using namespace Balyoz;
using std::map;

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

	Weapon* weapon = new Weapon();
	
	map<std::string,WeaponProperty*>::iterator it;

////	m_pWeaponXMLMap->m_Propertys->find(weaponName);
//	if(it != m_pWeaponXMLMap->m_Propertys.end()){
//
//		weapon->m_Controller	= it->second->m_Controller;
//		weapon->m_Effect		= it->second->m_Effect;
//		weapon->m_Explosion		= it->second->m_Explosion;
//		weapon->m_LifeTime		= it->second->m_iLifeTime;
//		weapon->m_MeshFileName	= it->second->m_Mesh;
//		weapon->m_Name			= it->second->m_Name;
//		weapon->m_Particles		= it->second->m_Particles;
//		weapon->m_Power			= it->second->m_iPower;
//		weapon->m_Radius		= it->second->m_fRadius;
//	}

	return weapon;

}


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

	
	Weapon* weapon = 0;

	map<std::string,WeaponProperty*>::iterator it;

	it = m_pWeaponXMLMap->m_Propertys.find(weaponName);

	if(it != m_pWeaponXMLMap->m_Propertys.end()){
		
		weapon = new Weapon();
		weapon->m_BulletAngle			= it->second->m_iAngle;
		weapon->m_capacity				= it->second->m_iCapacity;
		weapon->m_Initial				= it->second->m_iInitial;
		weapon->m_Maximum				= it->second->m_iMaximum;
		weapon->m_Minimum				= it->second->m_iMinimum;
		weapon->m_Name 					= it->second->m_Name;
		weapon->m_ReloadTime			= it->second->m_iReloadTime;
		weapon->m_MeshFileName			= it->second->m_Mesh;
		weapon->bullet->m_Controller	= it->second->m_Controller;
		weapon->bullet->m_Explosion		= it->second->m_Explosion;
		weapon->bullet->m_LifeTime		= it->second->m_iLifeTime;
		weapon->bullet->m_Particles		= it->second->m_Particles;
		weapon->bullet->m_Power			= it->second->m_iPower;
		weapon->bullet->m_Radius		= it->second->m_fRadius;
		
		if(it->second->m_Effect == std::string("lineer")){
			weapon->bullet->m_Effect = LINEER;
		}else if(it->second->m_Effect == std::string("exponential")){
			weapon->bullet->m_Effect = EXPONENTIAL;
		}else{
			weapon->bullet->m_Effect  = NONE;
		}	
		
	}

	return weapon;

}


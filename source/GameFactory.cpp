#include "GameFactory.h"
#include "Weapon.h"
#include "macros.h"
#include "AirGameUnit.h"
#include "NavyGameUnit.h"
#include <map>
#define USE_REPORT

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

Balyoz::Level* GameFactory::getLevel(const std::string& levelName){
return NULL;
}
Balyoz::GameMap* GameFactory::getMap(const std::string& mapName){
return NULL;
}
Balyoz::Terrain* GameFactory::getTerrain(const std::string& terrainName){
return NULL;
}

Balyoz::GameUnit* GameFactory::getUnit(const std::string& unitName){

	Balyoz::GameUnit* unit = 0;

	map<std::string,UnitProperty*>::iterator it;

	it = m_pUnitXMLMap->m_Propertys.find(unitName);
	if(it != m_pUnitXMLMap->m_Propertys.end()){

		if(it->second->m_Type == "air"){
			unit = new Balyoz::AirGameUnit();
			unit->m_Type = ENUM_UNIT_TYPE::AIR;
		}else if(it->second->m_Type == "navy"){
			unit = new Balyoz::NavyGameUnit();
			unit->m_Type = ENUM_UNIT_TYPE::NAVY;
		}else
			REPORT_WARNING("Unknown game unit type!");

		unit->m_Armour		= it->second->m_iArmour;
		unit->m_Controller	= it->second->m_Controller;
		unit->m_Health		= it->second->m_iHealth;
		unit->m_Mesh		= it->second->m_Mesh;
		unit->m_Name		= it->second->m_Name;
		unit->m_Speed		= it->second->m_Speed;

		std::vector<Weapon*>::iterator weaponIt = it->second->m_Weapons.begin();
		for(; weaponIt != it->second->m_Weapons.end() ; ++weaponIt){
			unit->m_Weapons.push_back(getSingleton()->getWeapon(weaponIt->m_Name));
		}
	}

	return unit;
}
Balyoz::Weapon* GameFactory::getWeapon(const std::string& weaponName){

	
	Balyoz::Weapon* weapon = 0;

	map<std::string,WeaponProperty*>::iterator it;

	it = m_pWeaponXMLMap->m_Propertys.find(weaponName);

	if(it != m_pWeaponXMLMap->m_Propertys.end()){
		
		weapon = new Balyoz::Weapon(weaponName);
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


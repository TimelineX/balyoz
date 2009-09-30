#include "GameFactory.h"
#include "Weapon.h"
#define USE_REPORT
#include "macros.h"
#include "AirGameUnit.h"
#include "NavyGameUnit.h"
#include "Level.h"
#include "BulletControllerProperty.h"
#include <map>

using std::map;
using namespace Balyoz;

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

	m_pBulletControllerXMLMap = (new XMLMapRepostory<BulletControllerProperty>("bullet controller bean"));
	m_pBulletControllerXMLMap->initFromXml( "bulletcontroller.xml" ,"bulletcontrollers", "bulletcontroller" );

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

Level* GameFactory::getLevel(const std::string& levelName){
	LevelProperty *pLevelProp = m_pLevelXMLMap->m_Propertys[levelName];
	ASSERT_AND_STOP_IF_NULL(pLevelProp);
	MapProperty *pMapProp = m_pMapXMLMap->m_Propertys[pLevelProp->m_Map];
	ASSERT_AND_STOP_IF_NULL(pMapProp);

	return new Level( pLevelProp, pMapProp) ;
}
GameMap* GameFactory::getMap(const std::string& mapName){
return NULL;
}
Terrain* GameFactory::getTerrain(const std::string& terrainName){
return NULL;
}

BulletControllerProperty*		GameFactory::getBulletControllerProperty	(const std::string& controllerName)
{
	BulletControllerProperty *bcp = m_pBulletControllerXMLMap->m_Propertys[controllerName];
	if(bcp == NULL)
	{
		REPORT_ERROR(controllerName+ std::string(" named controller not found"));
		bcp = new BulletControllerProperty();
		m_pBulletControllerXMLMap->m_Propertys[controllerName] = bcp;
	}

	return bcp;

}

GameUnit* GameFactory::getUnit(const std::string& unitName){

	GameUnit* unit = 0;

	map<std::string,UnitProperty*>::iterator it;

	it = m_pUnitXMLMap->m_Propertys.find(unitName);
	if(it != m_pUnitXMLMap->m_Propertys.end()){

		if(it->second->m_Type == "air"){
			unit = new AirGameUnit();
			unit->m_Type = ENUM_UNIT_TYPE::AIR;
		}else if(it->second->m_Type == "navy"){
			unit = new NavyGameUnit();
			unit->m_Type = ENUM_UNIT_TYPE::NAVY;
		}else
			REPORT_WARNING("Unknown game unit type!");

		unit->m_Armour		= it->second->m_iArmour;
		unit->m_Controller	= it->second->m_Controller;
		unit->m_Health		= it->second->m_iHealth;
		unit->m_Mesh		= it->second->m_Mesh;
		unit->m_Name		= it->second->m_Name;
		unit->m_Speed		= it->second->m_Speed;
		unit->m_pBody		= NULL;

		std::vector<std::string>::iterator weaponIt = it->second->m_Weapons.begin();
		for(; weaponIt != it->second->m_Weapons.end() ; ++weaponIt){
			unit->m_Weapons.push_back(getSingleton()->getWeapon((*weaponIt)));
		}
	}

	return unit;
}
Weapon* GameFactory::getWeapon(const std::string& weaponName){

	
	Weapon* weapon = 0;

	map<std::string,WeaponProperty*>::iterator it;

	it = m_pWeaponXMLMap->m_Propertys.find(weaponName);

	if(it != m_pWeaponXMLMap->m_Propertys.end()){
		
		weapon = new Weapon(weaponName);
		weapon->m_BulletAngle			= it->second->m_iAngle;
		weapon->m_capacity				= it->second->m_iCapacity;
		weapon->m_Initial				= it->second->m_iInitial;
		weapon->m_Maximum				= it->second->m_iMaximum;
		weapon->m_Minimum				= it->second->m_iMinimum;
		weapon->m_Name 					= it->second->m_Name;
		weapon->m_ReloadTime			= it->second->m_fReloadTime;
		weapon->m_MeshFileName			= it->second->m_Mesh;
		weapon->m_BulletProperty.m_Controller	= it->second->m_Controller;
		weapon->m_BulletProperty.m_Explosion		= it->second->m_Explosion;
		weapon->m_BulletProperty.m_LifeTime		= it->second->m_fLifeTime;
		weapon->m_BulletProperty.m_Particles		= it->second->m_Particles;
		weapon->m_BulletProperty.m_Power			= it->second->m_fPower;
		weapon->m_BulletProperty.m_Radius		= it->second->m_fRadius;
		weapon->m_BulletProperty.m_MaximumSpeed			= it->second->m_fMaximumSpeed;
		weapon->m_BulletProperty.m_InitialSpeed		= it->second->m_fInitialSpeed;
		
		if(it->second->m_Effect.compare(std::string("lineer")) == 0){
			weapon->m_BulletProperty.m_Effect = LINEER;
		}else if(it->second->m_Effect.compare(std::string("exponential")) == 0){
			weapon->m_BulletProperty.m_Effect = EXPONENTIAL;
		}else{
			weapon->m_BulletProperty.m_Effect  = NONE;
		}
		
		
	}

	return weapon;



}
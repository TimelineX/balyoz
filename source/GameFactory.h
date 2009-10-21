#pragma once
#include "XMLMapRepostory.h"
#include "DataPool.h"

//#include "BulletControllerProperty.h"
//#include "WeaponProperty.h"
//#include "LevelProperty.h"
//#include "UnitProperty.h"
//#include "TerrainProperty.h"
//#include "MapProperty.h"
//#include "GameProperty.h"



#include <map>
#include <string>
#include "Bullet.h"
#include "Weapon.h"
#include "GameUnit.h"
#include "GameMap.h"
#include "Terrain.h"
#include "Level.h"
#include "BulletController.h"
#include "UnitController.h"
#include "BulletProperty.h"
#include "GenericXmlMapProperty.h"
#define GAME_FACTORY GameFactory::getSingleton()

namespace Balyoz
{
	using namespace Utils;

	class GameFactory
	{
	public:
		~GameFactory(void);

		bool init();
		
		void createXmlMapRepostories();

		static GameFactory* getSingleton();

		BulletController*		getBulletController	(const std::string& controllerName);
		//UnitController*			getUnitController	(const std::string& controllerName);

		Level*		getLevel	(const std::string& levelName);
		GameMap*	getMap	    (const std::string& mapName);
		Terrain*	getTerrain	(const std::string& terrainName);
		GameUnit*   getUnit		(const std::string& unitName);

		Bullet*		getBullet	(const BulletProperty& bulletProperty );
		Weapon*		getWeapon	(const std::string& weaponName);

		GameFactory(void);



		std::map<std::string,BulletController*>		m_BulletControllers;
		std::list<BulletController*>*				m_pBulletControllerList;
		std::map<std::string,GameMap*>				m_GameMaps;
		std::map<std::string,Level*>				m_GameLevels;

		std::map<std::string,GameUnit*>				m_GameUnitPrototypes;
		std::map<std::string,BulletProperty*>		m_BulletPrototypes;
		std::map<std::string,Weapon*>				m_WeaponPrototypes;
		//XMLMapRepostory<GenericXmlMapProperty>*		m_pBulletControllerXMLMap;
		//XMLMapRepostory<GenericXmlMapProperty>*		m_pWeaponXMLMap;
		//XMLMapRepostory<GenericXmlMapProperty>*		m_pUnitXMLMap;
		//XMLMapRepostory<GenericXmlMapProperty>*		m_pTerrainXMLMap;
		//XMLMapRepostory<GenericXmlMapProperty>*		m_pMapXMLMap;
		//XMLMapRepostory<GenericXmlMapProperty>*		m_pLevelXMLMap;
		//XMLMapRepostory<GenericXmlMapProperty>*		m_pGameXMLMap;


		DataPool<GameUnit>*				m_pGameUnitPool;
		DataPool<Bullet>*				m_pBulletPool;
		DataPool<Weapon>*				m_pWeaponPool;
	};
};
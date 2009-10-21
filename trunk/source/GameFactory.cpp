#include "GameFactory.h"
#define USE_REPORT
#include "macros.h"
#include "AirGameUnit.h"
#include "NavyGameUnit.h"

#include <map>

using std::map;
using namespace Balyoz;



GameFactory::GameFactory(void)
{
	m_pWeaponPool = new DataPool<Weapon>(true, 128);
	m_pBulletPool = new DataPool<Bullet>();
	m_pGameUnitPool = new DataPool<GameUnit>(true, 128);
	m_pBulletControllerList = new std::list<BulletController*>();

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
	XMLMapRepostory<GenericXmlMapProperty> *pFileMap = (new XMLMapRepostory<GenericXmlMapProperty>("filemap"));
	pFileMap->initFromXml( "xmlfilemap.xml" ,"xmlfilemaps", "xmlfilemap" ); 
	if( pFileMap == NULL || pFileMap->m_Propertys.empty() )
	{
		REPORT_ERROR("xmlfilemap loading failed");
	}
	//std::map<std::string,GenericXmlMapProperty*> files;

	std::map<std::string, GenericXmlMapProperty*>::iterator it = pFileMap->m_Propertys.begin();
	const std::map<std::string, GenericXmlMapProperty*>::iterator endit = pFileMap->m_Propertys.end();
	XMLMapRepostory<GenericXmlMapProperty> *tmp;
	std::string roottag;
	std::string maintag;
	std::string filename;
	while( it != endit)
	{
		tmp = new XMLMapRepostory<GenericXmlMapProperty>(it->first); 
		if	(
			it->second->get<std::string>("/roottag",roottag) &&
			it->second->get<std::string>("/maintag",maintag) &&
			it->second->get<std::string>("/file",filename) 
			)
		{
				tmp->initFromXml(filename,roottag,maintag);
		}
		else
		{
				REPORT_ERROR("xmlfilemap loading failed");
		}

		std::map<std::string, GenericXmlMapProperty*>::iterator itPropertys = tmp->m_Propertys.begin();
		const std::map<std::string, GenericXmlMapProperty*>::iterator enditPropertys = tmp->m_Propertys.end();
		while( itPropertys != enditPropertys )
		{
			GenericXmlMapProperty *pSecond = itPropertys->second;

			bool bSuccess = false;

			if( tmp->m_Name.compare("bullet controller") == 0 )
			{
				BulletController *pBulletController = new BulletController();
				std::string sTmp = pSecond->getString("/behaviour");
				if (sTmp.compare("forward") == 0)
				{
					pBulletController->m_Behavoiur = BULLET_BEHAVIOUR_HORIZONTAL;
				}
				else if (sTmp.compare("freefall") == 0)
				{
					pBulletController->m_Behavoiur = BULLET_BEHAVIOUR_VERTICAL;
				}
				else if (sTmp.compare("guided") == 0)
				{
					pBulletController->m_Behavoiur = BULLET_BEHAVIOUR_GUIDED;
				}

				else
				{

					REPORT_WARNING("nothing set for bullet controller behaviour field. default forward will be set");
					pBulletController->m_Behavoiur = BULLET_BEHAVIOUR_HORIZONTAL;
				}

				sTmp = pSecond->getString("/aiming");
				if (sTmp.compare("weakest") == 0)
				{
					pBulletController->m_Aiming = BULLET_AIMING_WEAKEST;
				}
				else if (sTmp.compare("strongest") == 0)
				{
					pBulletController->m_Aiming = BULLET_AIMING_STRONGEST;
				}
				else if (sTmp.compare("none") == 0)
				{
					pBulletController->m_Aiming = BULLET_AIMING_NONE;
				}

				else
				{

					REPORT_WARNING("nothing set for bullet controller aiming field. default none will be set");
					pBulletController->m_Aiming = BULLET_AIMING_NONE;
				}

				pBulletController->m_fAccuracy = pSecond->getNumber("/accuracy");

				m_BulletControllers[itPropertys->first] = pBulletController;
				m_pBulletControllerList->push_back(pBulletController);

			}
			else if( tmp->m_Name.compare("game") == 0 )
			{
			}
			else if( tmp->m_Name.compare("levels") == 0 )
			{
				Level *pLevel = new Level(itPropertys->first);
				pLevel->m_Terrain = pSecond->getString("/terrain");
				pLevel->m_MapName = pSecond->getString("/map");
				pLevel->m_pGameMap = getMap(pLevel->m_MapName);
				pLevel->m_SkyBox = pSecond->getString("/skybox");

				m_GameLevels[itPropertys->first] = pLevel;
			}
			else if( tmp->m_Name.compare("maps") == 0 )
			{
				GameMap* pGameMap = new GameMap(itPropertys->first);

				std::vector<GenericXmlMapProperty*>* pUnitsOnMap ;
				itPropertys->second->getChildrenOf("/unit", pUnitsOnMap);
				for(int i =0; i < pUnitsOnMap->size(); i++)
				{
					MapGameObject *pGamemapobject = new  MapGameObject(pUnitsOnMap->at(i)->m_Name,
						pUnitsOnMap->at(i)->getVector3("/orientation"),
						pUnitsOnMap->at(i)->getVector3("/position"));
					pGameMap->m_pGameObjectList->push_back(pGamemapobject);
				}
				pGameMap->m_pGameObjectList->sort();
				m_GameMaps[itPropertys->first] = pGameMap;
			}
			else if( tmp->m_Name.compare("terrains") == 0 )
			{
			}
			else if( tmp->m_Name.compare("units") == 0 )
			{
				GameUnit *pGameUnit		= new GameUnit();
				
				pGameUnit->m_pMesh			= new std::string(pSecond->getString("/mesh", bSuccess));
				pGameUnit->m_pController	= new std::string(pSecond->getString("/controller", bSuccess));
				pGameUnit->m_Health = pSecond->getNumber("/health", bSuccess);
				pGameUnit->m_Armour = pSecond->getNumber("/armour", bSuccess);
				pGameUnit->m_Speed = pSecond->getNumber("/speed", bSuccess);

				std::string sTmp = pSecond->getString("/primaryweapon", bSuccess);
				pGameUnit->m_WeaponNames.push_back(sTmp) ;
				sTmp = pSecond->getString("/secondaryweapon", bSuccess);
				pGameUnit->m_WeaponNames.push_back(sTmp) ;

				sTmp = pSecond->getString("/type",bSuccess);
				if( sTmp.compare("navy") == 0 )
				{
					pGameUnit->m_Type = UNIT_TYPE_NAVY;
				}
				else if( sTmp.compare("air") == 0 )
				{
					pGameUnit->m_Type = UNIT_TYPE_AIR;
				}

				m_GameUnitPrototypes[itPropertys->first] = pGameUnit;
			}
			else if( tmp->m_Name.compare("weapons") == 0 )
			{
				Weapon *pWeapon = new Weapon(new std::string(itPropertys->first));
				pWeapon->m_pMeshFileName = new std::string(pSecond->getString("/mesh"));
				pWeapon->m_ReloadTime = pSecond->getNumber("/reloadtime");
				pWeapon->m_Capacity = pSecond->getNumber("/capacity");
				pWeapon->m_Initial = pSecond->getNumber("/initial");
				pWeapon->m_Maximum = pSecond->getNumber("/maximum");
				pWeapon->m_Minimum = pSecond->getNumber("/minimum");
				pWeapon->m_BulletAngle = pSecond->getNumber("/anglebetweenbullets");
				
				pWeapon->m_BulletProperty.m_InitialSpeed = pSecond->getNumber("/bullet/initialspeed");
				pWeapon->m_BulletProperty.m_MaximumSpeed = pSecond->getNumber("/bullet/maximumspeed");
				pWeapon->m_BulletProperty.m_Power = pSecond->getNumber("/bullet/power");
				pWeapon->m_BulletProperty.m_Radius = pSecond->getNumber("/bullet/radius");
				pWeapon->m_BulletProperty.m_Effect = EFFECT_LINEER; // TODO :  pSecond->getNumber("/bullet/effect");
				REPORT_WARNING("TODO : incomplete code for effect!");
				pWeapon->m_BulletProperty.m_LifeTime = pSecond->getNumber("/bullet/lifetime");
				pWeapon->m_BulletProperty.m_Particles = pSecond->getString("/bullet/particles");
				pWeapon->m_BulletProperty.m_Explosion = pSecond->getString("/bullet/explosion");
				pWeapon->m_BulletProperty.m_Controller = pSecond->getString("/bullet/controller");
				pWeapon->m_BulletProperty.m_pBulletController = getBulletController(pSecond->getString("/controller"));
				m_WeaponPrototypes[itPropertys->first] = pWeapon;


			}
			itPropertys++;
		}
		
		//files[it->first] = tmp;
		it++;
	}

	//m_pBulletControllerXMLMap = files["bullet controller"];
	//m_pGameXMLMap = files["game"];
	//m_pLevelXMLMap = files["levels"];
	//m_pMapXMLMap = files["maps"];
	//m_pTerrainXMLMap = files["terrains"];
	//m_pUnitXMLMap = files["units"];
	//m_pWeaponXMLMap= files["weapons"];

	
	



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

Level* GameFactory::getLevel(const std::string& levelName)
{
	Level *pLevel = m_GameLevels[levelName];
	if (pLevel != NULL)
	{
		pLevel->m_pGameMap = getMap(pLevel->m_MapName);
	}

	return pLevel;
}
GameMap* GameFactory::getMap(const std::string& mapName){
	return m_GameMaps[mapName];
}
Terrain* GameFactory::getTerrain(const std::string& terrainName){
return NULL;
}

BulletController*		GameFactory::getBulletController	(const std::string& controllerName)
{
	BulletController *pBulletController = m_BulletControllers[controllerName];
	
	return pBulletController;

}

GameUnit* GameFactory::getUnit(const std::string& unitName){

	GameUnit* pUnit = m_pGameUnitPool->get();
	*pUnit = *(m_GameUnitPrototypes[unitName]);
	for(int i = 0 ; i < pUnit->m_WeaponNames.size(); i++)
	{
		pUnit->m_Weapons.push_back(getWeapon(pUnit->m_WeaponNames[i]));
	}

	return pUnit;
}

Bullet*		GameFactory::getBullet	(const BulletProperty& bulletProperty )
{
	Bullet *pBullet = m_pBulletPool->get();
	pBullet->setBulletProperty(bulletProperty);
	return pBullet;
}


Weapon* GameFactory::getWeapon(const std::string& weaponName){

	
	Weapon* pWeapon = m_pWeaponPool->get();
	*pWeapon = *(m_WeaponPrototypes[weaponName]);
	pWeapon->m_BulletProperty.m_pBulletController = m_BulletControllers[pWeapon->m_BulletProperty.m_Controller];


	return pWeapon;



}


//UnitController*	GameFactory::getUnitController	(const std::string& controllerName)
//{
//	return m_UnitControllers[controllerName];
//}

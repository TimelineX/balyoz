#include "GameFactory.h"
#define USE_REPORT
#include "macros.h"

#include <map>
#include <OgreCommon.h>
#include "Level.h"
#include "GameMap.h"
#include "Terrain.h"
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

	std::vector<GenericXmlMapProperty*>::iterator it = pFileMap->m_PropertyVector.begin();
	const std::vector<GenericXmlMapProperty*>::iterator endit = pFileMap->m_PropertyVector.end();
	XMLMapRepostory<GenericXmlMapProperty> *tmp;
	std::string roottag;
	std::string maintag;
	std::string filename;
	while( it != endit)
	{
		tmp = new XMLMapRepostory<GenericXmlMapProperty>((*it)->getString("/name")); 
		if	(
			(*it)->get<std::string>("/roottag",roottag) &&
			(*it)->get<std::string>("/maintag",maintag) &&
			(*it)->get<std::string>("/file",filename) 
			)
		{
				tmp->initFromXml(filename,roottag,maintag);
		}
		else
		{
			REPORT_ERROR_AND_STOP( filename + ": xmlfilemap loading failed" );
		}

		std::vector<GenericXmlMapProperty*>::iterator itPropertys = tmp->m_PropertyVector.begin();
		const std::vector<GenericXmlMapProperty*>::iterator enditPropertys = tmp->m_PropertyVector.end();
		while( itPropertys != enditPropertys )
		{
			GenericXmlMapProperty *pCurrentGXMP = *itPropertys;

			bool bSuccess = false;

			if( tmp->m_Name.compare("bullet controller") == 0 )
			{
				BulletController *pBulletController = new BulletController();
				std::string sTmp = pCurrentGXMP->getString("/behaviour");
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

				sTmp = pCurrentGXMP->getString("/aiming");
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

				pBulletController->m_fAccuracy = pCurrentGXMP->getNumber("/accuracy");

				m_BulletControllers[pCurrentGXMP->getString("/name")] = pBulletController;
				m_pBulletControllerList->push_back(pBulletController);

			}
			else if( tmp->m_Name.compare("game") == 0 )
			{
			}
			else if( tmp->m_Name.compare("levels") == 0 )
			{
				Level *pLevel = new Level(pCurrentGXMP->getString("/name"));
				pCurrentGXMP->getAll<std::string>("/terrain",pLevel->m_TerrainNames);
				for (int i = 0 ; i < pLevel->m_TerrainNames.size(); i++)
				{
					pLevel->m_Terrains.push_back(new Terrain(*(m_TerrainPrototypes[pLevel->m_TerrainNames[i]])));
				}
				pLevel->m_MapName = pCurrentGXMP->getString("/map");
				pLevel->m_pGameMap = getMap(pLevel->m_MapName);

				pLevel->m_SkyBoxName = pCurrentGXMP->getString("/skybox/resourcename",pLevel->m_bSetupSkyBox);
				pLevel->m_fSkyBoxDistance = pCurrentGXMP->getNumber("/skybox/distance");

				pLevel->m_FogColour = pCurrentGXMP->getColourValue("/fog/colour",bSuccess);
				pLevel->m_bSetupFog |= bSuccess;
				std::string tmpStr = pCurrentGXMP->getString("/fog/mode",bSuccess);
				pLevel->m_bSetupFog |= bSuccess;
				if (tmpStr.compare("linear") == 0)
				{
					pLevel->m_FogMode = Ogre::FOG_LINEAR;
				} 
				else if (tmpStr.compare("exp") == 0)
				{
					pLevel->m_FogMode = Ogre::FOG_EXP;
				}

				else if (tmpStr.compare("exp2") == 0)
				{
					pLevel->m_FogMode = Ogre::FOG_EXP2;
				}
				else
				{
					pLevel->m_FogMode = Ogre::FOG_NONE;
				}
				pLevel->m_fFogDensity = pCurrentGXMP->getNumber("/fog/density",bSuccess);
				pLevel->m_bSetupFog |= bSuccess;
				pLevel->m_fFogStart = pCurrentGXMP->getNumber("/fog/start",bSuccess);
				pLevel->m_bSetupFog |= bSuccess;
				pLevel->m_fFogEnd = pCurrentGXMP->getNumber("/fog/end",bSuccess);
				pLevel->m_bSetupFog |= bSuccess;

				pLevel->m_LightName = pCurrentGXMP->getString("/light/lightname", pLevel->m_bSetupLight);
				pLevel->m_AmbientColour = pCurrentGXMP->getColourValue("/light/ambientcolour");
				pLevel->m_DiffuseLightColour = pCurrentGXMP->getColourValue("/light/diffusecolour");
				pLevel->m_SpecularLightColour = pCurrentGXMP->getColourValue("/light/specularcolour");
				pLevel->m_LightPosition = pCurrentGXMP->getVector3("/light/position");

				pLevel->m_CameraPosition = pCurrentGXMP->getVector3("/camera/position");
				pLevel->m_CameraLookAt = pCurrentGXMP->getVector3("/camera/lookat");




				m_GameLevels[pLevel->m_Name] = pLevel;
			}
			else if( tmp->m_Name.compare("maps") == 0 )
			{
				GameMap* pGameMap = new GameMap(pCurrentGXMP->getString("/name"));

				std::vector<GenericXmlMapProperty*>* pUnitsOnMap ;
				pCurrentGXMP->getChildrenOf("/unit", pUnitsOnMap);
				for(int i =0; i < pUnitsOnMap->size(); i++)
				{
					//MapGameObject *pGamemapobject = new  MapGameObject(pUnitsOnMap->at(i)->m_Name,
					//	pUnitsOnMap->at(i)->getVector3("/orientation"),
					//	pUnitsOnMap->at(i)->getVector3("/position"));
					pGameMap->m_pGameObjectList->push_back(MapGameObject(pUnitsOnMap->at(i)->m_Name,
							pUnitsOnMap->at(i)->getVector3("/orientation"),
							pUnitsOnMap->at(i)->getVector3("/position")));
				}
//				sort(pGameMap->m_pGameObjectList->begin(),pGameMap->m_pGameObjectList->end(),)
				pGameMap->m_pGameObjectList->sort();
				m_GameMaps[pGameMap->m_MapName] = pGameMap;
			}
			else if( tmp->m_Name.compare("terrains") == 0 )
			{
				Terrain *pTerrain = new Terrain();

				pTerrain->m_Name = pCurrentGXMP->getString("/name");
				
				std::string tmpStr = pCurrentGXMP->getString("/type");
				if ( tmpStr.compare("flat") == 0)
				{
					pTerrain->m_TerrainType = TERRAIN_TYPE_FLAT;
				} 
				else if ( tmpStr.compare("heightmap") == 0)
				{
					pTerrain->m_TerrainType = TERRAIN_TYPE_HEIGT_MAP;
				}
				else if ( tmpStr.compare("ocean") == 0)
				{
					pTerrain->m_TerrainType = TERRAIN_TYPE_OCEAN;
				}
				else
				{
					pTerrain->m_TerrainType = TERRAIN_TYPE_NONE;
					REPORT_WARNING(tmpStr + std::string(": this terrain type cannot be recognised for terrain ") + pTerrain->m_Name );
				}

				pTerrain->m_ResourceName = pCurrentGXMP->getString("/resourcename");
				pTerrain->m_fWidth		= pCurrentGXMP->getNumber("/width");
				pTerrain->m_fHeight		= pCurrentGXMP->getNumber("/height");
				pTerrain->m_fLength		= pCurrentGXMP->getNumber("/length");
				pTerrain->m_iLengthSegments = (int)pCurrentGXMP->getNumber("/lengthsegments");
				pTerrain->m_iWidthSegnemts = (int)pCurrentGXMP->getNumber("/widthsegments");
				
				pTerrain->m_bStatic = Ogre::StringConverter::parseBool(pCurrentGXMP->getString("/static"));
				m_TerrainPrototypes[pTerrain->m_Name] = pTerrain;

			}
			else if( tmp->m_Name.compare("units") == 0 )
			{
				GameUnit *pGameUnit		= new GameUnit( new std::string(pCurrentGXMP->getString("/name")));
				
				pGameUnit->m_pMesh			= new std::string(pCurrentGXMP->getString("/mesh", bSuccess));
				pGameUnit->m_pController	= new std::string(pCurrentGXMP->getString("/controller", bSuccess));
				pGameUnit->m_Health = pCurrentGXMP->getNumber("/health", bSuccess);
				pGameUnit->m_Armour = pCurrentGXMP->getNumber("/armour", bSuccess);
				pGameUnit->m_Speed = pCurrentGXMP->getNumber("/speed", bSuccess);

				std::string sTmp = pCurrentGXMP->getString("/primaryweapon", bSuccess);
				pGameUnit->m_WeaponNames.push_back(sTmp) ;
				sTmp = pCurrentGXMP->getString("/secondaryweapon", bSuccess);
				pGameUnit->m_WeaponNames.push_back(sTmp) ;

				sTmp = pCurrentGXMP->getString("/type",bSuccess);
				if( sTmp.compare("navy") == 0 )
				{
					pGameUnit->m_Type = UNIT_TYPE_NAVY;
				}
				else if( sTmp.compare("air") == 0 )
				{
					pGameUnit->m_Type = UNIT_TYPE_AIR;
				}

				m_GameUnitPrototypes[std::string(pGameUnit->m_pName->c_str())] = pGameUnit;
			}
			else if( tmp->m_Name.compare("weapons") == 0 )
			{
				Weapon *pWeapon = new Weapon(new std::string(pCurrentGXMP->getString("/name")));
				pWeapon->m_pMeshFileName = new std::string(pCurrentGXMP->getString("/mesh"));
				pWeapon->m_fReloadTime = pCurrentGXMP->getNumber("/reloadtime");
				pWeapon->m_uiCapacity = pCurrentGXMP->getNumber("/capacity");
				pWeapon->m_uiInitial = pCurrentGXMP->getNumber("/initial");
				pWeapon->m_uiMaximum = pCurrentGXMP->getNumber("/maximum");
				pWeapon->m_uiMinimum = pCurrentGXMP->getNumber("/minimum");
				pWeapon->m_uiBulletAngle = pCurrentGXMP->getNumber("/anglebetweenbullets");
				
				pWeapon->m_BulletProperty.m_fRocketForce = pCurrentGXMP->getNumber("/bullet/rocketforce");
				pWeapon->m_BulletProperty.m_fInitialSpeed = pCurrentGXMP->getNumber("/bullet/initialspeed");
				pWeapon->m_BulletProperty.m_fMaximumSpeed = pCurrentGXMP->getNumber("/bullet/maximumspeed");
				pWeapon->m_BulletProperty.m_fPower = pCurrentGXMP->getNumber("/bullet/power");
				pWeapon->m_BulletProperty.m_fRadius = pCurrentGXMP->getNumber("/bullet/radius");
				pWeapon->m_BulletProperty.m_Effect = EFFECT_LINEER; // TODO :  pCurrentGXMP->getNumber("/bullet/effect");
				REPORT_WARNING("TODO : incomplete code for effect!");
				pWeapon->m_BulletProperty.m_fLifeTime = pCurrentGXMP->getNumber("/bullet/lifetime");
				pWeapon->m_BulletProperty.m_Particles = pCurrentGXMP->getString("/bullet/particles");
				pWeapon->m_BulletProperty.m_Explosion = pCurrentGXMP->getString("/bullet/explosion");
				pWeapon->m_BulletProperty.m_Controller = pCurrentGXMP->getString("/bullet/controller");
				pWeapon->m_BulletProperty.m_pBulletController = getBulletController(pCurrentGXMP->getString("/bullet/controller"));
				m_WeaponPrototypes[std::string(pWeapon->m_pName->c_str())] = pWeapon;


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

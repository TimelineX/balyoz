#include "GameMap.h"
#include "GameObject.h"
#define USE_SAFE
#include "macros.h"

using namespace Balyoz;

GameMap::GameMap(const std::string &name){

	m_MapName = name;
	m_pGameObjectList = new std::list<MapGameObject>();
}

GameMap::~GameMap()
{
	//std::list<MapGameObject*>::iterator it = m_pGameObjectList->begin();
	//const std::list<MapGameObject*>::iterator endit = m_pGameObjectList->end();
	//while (it != endit)
	//{
	//	MapGameObject *pGameMapObject = *it;
	//	it = m_pGameObjectList->erase(it);
	//	SAFE_DELETE(pGameMapObject);
	//	it++;
	//}
	SAFE_DELETE(m_pGameObjectList);

}


//MapGameObject* GameMap::getMapObjectByName(const std::string &objName) {
//	std::list<MapGameObject>::iterator it = m_pGameObjectList->begin();
//	for( ; it != m_pGameObjectList->end() ; it++){
//		MapGameObject * pGO = (*it);
//		if( pGO->m_GameUnitName.compare(objName) == 0 )
//			return pGO;
//	}
//	return NULL;
//}
//
//MapGameObject* GameMap::getMapObjectByPosition(const Ogre::Vector3 &position){
//	std::list<MapGameObject>::iterator it = m_pGameObjectList->begin();
//	for( ; it != m_pGameObjectList->end() ; it++){
//		if((*it).m_Position == position)
//			return *it;
//	}
//	return NULL;
//}


std::list<MapGameObject>* GameMap::getAllMapObjects(){
	return m_pGameObjectList;
}
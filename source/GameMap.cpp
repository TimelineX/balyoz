//#include "GameMap.h"
//#include "GameObject.h"
//
//
//using namespace Balyoz;
//
//GameMap::GameMap(void){
//
//}
//
//GameMap::~GameMap(){}
//
//GameMap::GameMap(const std::string &name){
//	m_MapName = name;
//}
//
//GameMap::MapGameObject* GameMap::getMapObjectByName(const std::string &objName) {
//	std::vector<MapGameObject*>::iterator it = m_GameObjectList.begin();
//	for( ; it != m_GameObjectList.end() ; it++){
//		MapGameObject * pGO = (*it);
//		if( pGO->gameObject->m_Name.compare(objName) == 0 )
//			return *it;
//	}
//	return NULL;
//}
//
//GameMap::MapGameObject* GameMap::getMapObjectByPosition(const Ogre::Vector3 &position){
//	std::vector<MapGameObject*>::iterator it = m_GameObjectList.begin();
//	for( ; it != m_GameObjectList.end() ; it++){
//		if((*it)->position == position)
//			return *it;
//	}
//	return NULL;
//}
//
//std::vector<GameMap::MapGameObject*>* GameMap::getAllMapObjects(){
//	return NULL;
//}
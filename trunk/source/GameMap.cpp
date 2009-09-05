#include "GameMap.h"

Balyoz::GameMap::GameMap(void){

}

Balyoz::GameMap::~GameMap(){}

Balyoz::GameMap::GameMap(const std::string &name){
	m_MapName = name;
}

Balyoz::GameMap::MapGameObject* Balyoz::GameMap::getMapObjectByName(const std::string &objName) {
	std::vector<MapGameObject*>::iterator it = m_GameObjectList.begin();
	for( ; it != m_GameObjectList.end() ; it++){
		if((*it)->gameObject->m_Name == objName)
			return *it;
	}
	return NULL;
}

Balyoz::GameMap::MapGameObject* Balyoz::GameMap::getMapObjectByPosition(const Ogre::Vector3 &position){
	std::vector<MapGameObject*>::iterator it = m_GameObjectList.begin();
	for( ; it != m_GameObjectList.end() ; it++){
		if((*it)->position == position)
			return *it;
	}
	return NULL;
}

std::vector<Balyoz::GameMap::MapGameObject*>* Balyoz::GameMap::getAllMapObjects(){
	return NULL;
}
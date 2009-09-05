#pragma once
#include <OgreVector3.h>

class GameObject;

namespace Balyoz
{	

	class GameMap{

		typedef struct _MapGameObject{
			GameObject*		gameObject;
			Ogre::Vector3	orientation;
			Ogre::Vector3	position;

		}MapGameObject;

		GameMap(void);
		GameMap(const std::string& name);
		~GameMap();

		std::string m_MapName;

		MapGameObject* getMapObjectByName		(const std::string& objName) const ;
		MapGameObject* getMapObjectByPosition	(const Ogre::Vector3& position) const;
		std::vector<MapGameObject*>* getAllMapObjects();

	private:
		std::vector<MapGameObject*> m_GameObjectList;

		
	};
}
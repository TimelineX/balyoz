//#pragma once
//#include <OgreVector3.h>
//
//
//namespace Balyoz
//{	
//	class GameObject;
//	typedef struct _MapGameObject{
//	public:
//		GameObject*		gameObject;
//		Ogre::Vector3	orientation;
//		Ogre::Vector3	position;
//
//	}MapGameObject;
//	class GameMap{
//	public:
//
//
//		GameMap(void);
//		GameMap(const std::string& name);
//		~GameMap();
//
//		std::string m_MapName;
//
//		MapGameObject* getMapObjectByName		(const std::string& objName)  ;
//		MapGameObject* getMapObjectByPosition	(const Ogre::Vector3& position) ;
//		std::vector<MapGameObject*>* getAllMapObjects();
//
//	public:
//		std::vector<MapGameObject*> m_GameObjectList;
//
//		
//	};
//}
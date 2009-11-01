#pragma once
#include <OgreVector3.h>
#include <list>

namespace Balyoz
{	
	class GameObject;
	typedef struct _MapGameObject{
	public:
		_MapGameObject(const std::string &name, const Ogre::Vector3& orient, const Ogre::Vector3& pos )
		{
			m_GameUnitName = name;
			m_Orientation = orient;
			m_Position = pos;
		}
		std::string m_GameUnitName;
		Ogre::Vector3	m_Orientation;
		Ogre::Vector3	m_Position;

		bool operator < (const _MapGameObject& rhs)
		{
			return m_Position.z < rhs.m_Position.z;
		}

	}MapGameObject;
	class GameMap{
	public:


		GameMap(const std::string& name = std::string(""));
		~GameMap();

		std::string m_MapName;

		//MapGameObject* getMapObjectByName		(const std::string& objName)  ;
		//MapGameObject* getMapObjectByPosition	(const Ogre::Vector3& position) ;
		std::list<MapGameObject>* getAllMapObjects();

	public:
		std::list<MapGameObject> *m_pGameObjectList;

		
	};
}
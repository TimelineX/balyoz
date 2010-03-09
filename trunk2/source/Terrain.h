#pragma once
#include <string>
#include "GameUnit.h"

namespace Balyoz{

	class Ogre::SceneManager;
	class Ogre::RenderWindow;
	class Ogre::Entity;

	enum ENUM_TERRAIN_TYPE
	{
		TERRAIN_TYPE_NONE = 0,
		TERRAIN_TYPE_FLAT = 1,
		TERRAIN_TYPE_HEIGT_MAP,
		TERRAIN_TYPE_OCEAN
	};

	class Terrain
	{
	public:
		Terrain(const std::string& name = std::string(""));
		~Terrain(void);

		void load( Ogre::SceneManager * pSceneManager, Ogre::RenderWindow * pRendenWindow, Ogre::SceneNode *pSceneNodeToAttach = 0 );




		std::string				m_Name;
		std::string				m_ResourceName;
		ENUM_TERRAIN_TYPE		m_TerrainType;

		float					m_fWidth;
		float					m_fLength;
		float					m_fHeight;
		int						m_iWidthSegnemts;
		int						m_iLengthSegments;
		bool					m_bStatic;

		Ogre::Entity*			m_pEntity;
		Ogre::SceneNode*		m_pSceneNode;
	};

}


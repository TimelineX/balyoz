#include "Terrain.h"
#define USE_REPORT
#include "macros.h"

using namespace Balyoz;

Terrain::Terrain(const std::string& name)
{
	m_Name = name;
	m_pEntity = 0;
	m_pSceneNode = 0;
}

Terrain::~Terrain(void)
{
}

void Terrain::load( Ogre::SceneManager * pSceneManager, Ogre::RenderWindow * pRendenWindow, Ogre::SceneNode *pSceneNodeToAttach )
{
	switch (m_TerrainType)
	{
	case TERRAIN_TYPE_FLAT:
		break;

	case TERRAIN_TYPE_HEIGT_MAP:
		pSceneManager->setWorldGeometry(m_ResourceName);
		break;

	case TERRAIN_TYPE_OCEAN:
		Ogre::Plane oceanSurface;
		oceanSurface.normal = Ogre::Vector3::UNIT_Y;
		oceanSurface.d = -m_fHeight;

		Ogre::MeshManager::getSingleton().createPlane("OceanSurface",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			oceanSurface,
			m_fWidth, m_fLength, m_iWidthSegnemts, m_iLengthSegments, 
			true, 1, 1, 1, Ogre::Vector3::UNIT_Z);

		m_pEntity = pSceneManager->createEntity( "OceanSurface", "OceanSurface" );
		m_pEntity->setMaterialName(m_ResourceName);
		
		if( !m_bStatic )
		{
			if ( pSceneNodeToAttach )
			{
				m_pSceneNode = pSceneNodeToAttach->createChildSceneNode();
				m_pSceneNode->attachObject(m_pEntity);

			} 
			else
			{
				REPORT_WARNING(m_Name + " terrain is not static however no scenenode is given; terrain will be loaded as static ");
				
				m_pSceneNode = pSceneManager->getRootSceneNode()->createChildSceneNode();
				m_pSceneNode->attachObject(m_pEntity);

			}
		}

		break;
	}
}

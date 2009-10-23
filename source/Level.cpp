#include <OgreLight.h>
#include <OgreColourValue.h>
#include "Level.h"
#include "GameMap.h"
#include "Terrain.h"
#define USE_SAFE
#define USE_REPORT
#include "macros.h"

using namespace Balyoz;

#define NOT_SET_WARNING(not_set_value)	REPORT_WARNING(not_set_value" is not set for level:" + m_Name)

Level::Level(const std::string& name )
{
	m_Name = name;
	m_bSetupSkyBox = false;
	m_bSetupFog = false;
	m_bSetupLight = false;

	m_fSkyBoxDistance = 5000;

	m_FogMode = Ogre::FOG_NONE;
	m_FogColour = Ogre::ColourValue();
	m_fFogDensity = 0.001;
	m_fFogStart = 0;
	m_fFogEnd = 1.0;

	m_AmbientColour = m_SpecularLightColour = m_DiffuseLightColour = Ogre::ColourValue();
	m_LightPosition = Ogre::Vector3(0,0,0);
}


Level::~Level(void)
{
	SAFE_DELETE(m_pGameMap);
	
}

void Level::load(Ogre::SceneManager *pSceneManager, Ogre::RenderWindow *pRenderWindow, Ogre::Camera *pCamera ,Ogre::SceneNode *pSceneNodeToAttach)
{

	pSceneManager->setAmbientLight(m_AmbientColour);

	pCamera->setPosition(m_CameraPosition);
	pCamera->lookAt(m_CameraLookAt);

	if (m_bSetupSkyBox)
	{
		if ( !m_SkyBoxName.empty() )
		{
			pSceneManager->setSkyBox(true, m_SkyBoxName, m_fSkyBoxDistance);
		} 
		else
		{
			NOT_SET_WARNING("Skybox name ");
		}
	}
	if (m_bSetupFog)
	{
		if ( m_FogMode != Ogre::FOG_NONE )
		{
			pSceneManager->setFog(m_FogMode,m_FogColour, m_fFogDensity, m_fFogStart, m_fFogEnd);
		} 
		else
		{
			NOT_SET_WARNING("fog mode ");
		}
	}

	if (m_bSetupLight)
	{
		if ( !m_LightName.empty() )
		{
			Ogre::Light *pLight = pSceneManager->createLight(m_LightName);
			if (pLight)
			{
				pLight->setPosition(m_LightPosition);
				pLight->setDiffuseColour(m_DiffuseLightColour);
				pLight->setSpecularColour(m_SpecularLightColour);
			}
		} 
		else
		{
			NOT_SET_WARNING("light name");
		}
	}
	for (int i = 0 ; i < m_Terrains.size(); i++)
	{
		m_Terrains[i]->load(pSceneManager,pRenderWindow,pSceneNodeToAttach);
	}
}

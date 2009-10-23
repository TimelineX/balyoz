#pragma once
#include <string>
#include <vector>
#include <OgreCommon.h>
#include <OgreColourValue.h>
#include <OgreVector3.h>
namespace Balyoz{

class GameMap;
class Ogre::SceneManager;
class Ogre::RenderWindow;
class Ogre::Camera;
class Terrain;
class Level
{
public:


	Level(const std::string& name = std::string(""));
	~Level(void);

	void load(Ogre::SceneManager *pSceneManager, Ogre::RenderWindow *pRenderWindow, Ogre::Camera *pCamera, Ogre::SceneNode *pSceneNodeToAttach = 0);
	

	std::string			m_Name;
	std::vector<std::string>	m_TerrainNames;
	std::vector<Terrain*>		m_Terrains;
	std::string			m_MapName;
	GameMap				*m_pGameMap;
	Ogre::ColourValue	m_AmbientColour;
	

	bool				m_bSetupSkyBox;
	std::string			m_SkyBoxName;
	float				m_fSkyBoxDistance;
	
	bool				m_bSetupFog;
	Ogre::ColourValue	m_FogColour;
	Ogre::FogMode		m_FogMode;
	float				m_fFogDensity;
	float				m_fFogStart;
	float				m_fFogEnd;

	bool				m_bSetupLight;
	std::string			m_LightName;
	Ogre::ColourValue	m_SpecularLightColour;
	Ogre::ColourValue	m_DiffuseLightColour;
	Ogre::Vector3		m_LightPosition;

	Ogre::Vector3		m_CameraPosition;
	Ogre::Vector3		m_CameraLookAt;
	

};
}

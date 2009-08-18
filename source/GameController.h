#pragma once
#include "OgreFrameListener.h"
#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

class GameController :
	public Ogre::FrameListener
{
public:
	GameController(void);
	~GameController(void);
};

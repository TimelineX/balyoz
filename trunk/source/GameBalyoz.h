//	NxOgre tutorials is using ogre example application framework
#include "GameApplication.h"

//	only file you need to include to use NxOgre
#include "NxOgre.h"
#include "NxOgreOGRE3D.h"
#include "TestFrameListener.h"
#include "OGRE3DCommon.h"

class GameBalyoz : public GameApplication
{
public:

	GameBalyoz();
	~GameBalyoz();
	void createScene(void);
	void createFrameListener(void);
	void init();

protected:
	NxOgre::World	*m_pNxWorld;
	NxOgre::Scene	*m_pNxScene;
	OGRE3DRenderSystem *m_pRenderSystem;
	NxOgre::TimeController *m_pNxTimeController;
	TestFrameListener *m_pTestFrameListener;
};

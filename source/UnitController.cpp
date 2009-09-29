#include "UnitController.h"
#include "GameController.h"
#include "EventCollector.h"
#include "GameUnit.h"
#include "Weapon.h"

using namespace Balyoz;



HumanController::HumanController()
:UnitController(CONTROLLER_HUMAN)
{
	m_pMouse = GameController::getInfoProvider()->getMouse();
	m_pKeyboard = GameController::getInfoProvider()->getKeyboard();
	m_Name = "human";
}

HumanController::~HumanController()
{
}


void HumanController::run()
{
	std::list<GameUnit*>::iterator it = m_GameObjectList.begin();
	const std::list<GameUnit*>::iterator endIt = m_GameObjectList.end();
	float fTime = GameController::getInfoProvider()->getFrameTime();

	const OIS::MouseState &mouseState =  m_pMouse->getMouseState();

	if(mouseState.X.rel != 0 )
	{
		m_TranslateVec[0] += mouseState.X.rel / 1000.0f;
	}
	if( mouseState.Y.rel != 0 )
	{
		m_TranslateVec[2] += mouseState.Y.rel / 1000.0f;
	}


	float fRoll = 0;
	float fPitch = 0;
	while(it != endIt)
	{
		GameUnit *pGU = (*it);
		PhysicsObject *kb  = pGU->m_pBody;
		NxOgre::Vec3 tmpV = ( m_TranslateVec * ( pGU->m_Speed * fTime  ));
		kb->setGlobalPosition( kb->getGlobalPosition() + tmpV );

		fRoll = -m_TranslateVec[0] * 30.0f ;
		if(fRoll > 90)
		{
			fRoll = 90;
		}
		else if (fRoll < -90)
		{
			fRoll = -90;
		}
		
		fPitch = m_TranslateVec[2] * 30.0f ;
		if(fPitch > 90)
		{
			fPitch = 90;
		}
		else if (fPitch < -90)
		{
			fPitch = -90;
		}

		kb->getSceneNode()->roll(Ogre::Radian(Ogre::Angle(fRoll)));
		kb->getSceneNode()->pitch(Ogre::Radian(Ogre::Angle(fPitch)));

		if(mouseState.buttonDown(OIS::MB_Left))
		{
			if( pGU->m_Weapons[0]->m_LastShootTime  < 0 )
			{
				GameController::getInfoProvider()->shoot(pGU,0);
				pGU->m_Weapons[0]->m_LastShootTime = pGU->m_Weapons[0]->m_ReloadTime;
			}
			pGU->m_Weapons[0]->m_LastShootTime -= fTime * 1000.0f;
		}
		it++;
	}
		
	m_TranslateVec *= .985  ;
}

UnitAIController::UnitAIController()
:UnitController(CONTROLLER_AI)
{
	m_Name = "dummy";
}
UnitAIController::~UnitAIController()
{
}


void UnitAIController::run()
{
	
}
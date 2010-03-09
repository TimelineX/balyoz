#include "UnitController.h"
#include "GameController.h"
#include "EventCollector.h"
#include "GameUnit.h"
#include "Weapon.h"
#include <OgreMath.h>
#include <OIS/OISKeyboard.h>

using namespace Balyoz;



HumanController::HumanController()
:UnitController(CONTROLLER_TYPE_HUMAN)
{
	m_pMouse = GameController::getInfoProvider()->getMouse();
	m_pKeyboard = GameController::getInfoProvider()->getKeyboard();
	m_pCamera = GameController::getInfoProvider()->getActiveCamera();
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
	bool bMoveCamera = false;
	NxOgre::Vec3 translateVec;

	if(mouseState.X.rel != 0 )
	{
		translateVec[0] -= mouseState.X.rel / 10.0f;
		bMoveCamera = true;
	}
	if( mouseState.Y.rel != 0 )
	{
		translateVec[2] -= mouseState.Y.rel / 10.0f;
		bMoveCamera = true;
	}

	const float translateAmount = 1.f;

	if(m_pKeyboard->isKeyDown(OIS::KC_W))
	{
		translateVec[2] += translateAmount;
		bMoveCamera = true;
	}

	if(m_pKeyboard->isKeyDown(OIS::KC_S))
	{
		translateVec[2] -= translateAmount/2.0f;
		bMoveCamera = true;
	}

	if(m_pKeyboard->isKeyDown(OIS::KC_A))
	{
		translateVec[0] += translateAmount;
		bMoveCamera = true;
	}

	if(m_pKeyboard->isKeyDown(OIS::KC_D))
	{
		translateVec[0] -= translateAmount;
		bMoveCamera = true;
	}


	float fRoll = 0;
	float fPitch = 0;
	NxOgre::Vec3 speed;
//	float fSqrtTime = Ogre::Math::Sqrt(fTime);
	while(it != endIt)
	{
		GameUnit *pGU = (*it);
		PhysicsObject *kb  = pGU->m_pBody;
		NxOgre::Vec3 tmpV = ( translateVec * ( pGU->m_Speed   ));
		kb->addForce(tmpV);//->setGlobalPosition( kb->getGlobalPosition() + tmpV );

		speed = kb->getLinearVelocity();
		fRoll = -100 * speed.x / pGU->m_Speed ;
		if(fRoll > 45)
		{
			fRoll = 45;
		}
		else if (fRoll < -45)
		{
			fRoll = -45;
		}
		
		fPitch = 100 * speed.z / pGU->m_Speed;
		if(fPitch > 45)
		{
			fPitch = 45;
		}
		else if (fPitch < -45)
		{
			fPitch = -45;
		}

		kb->getSceneNode()->roll(Ogre::Radian(Ogre::Angle(fRoll)));
		kb->getSceneNode()->pitch(Ogre::Radian(Ogre::Angle(fPitch)));

		if((m_pKeyboard->isKeyDown(OIS::KC_LCONTROL) || mouseState.buttonDown(OIS::MB_Left)) && pGU->m_Weapons.size() > 0)
		{			
			if( pGU->m_Weapons[0]->m_fLastShootTime  < 0 )
			{
				GameController::getInfoProvider()->shoot(pGU,0);
				pGU->m_Weapons[0]->m_fLastShootTime = pGU->m_Weapons[0]->m_fReloadTime;
			}
		}


		if((m_pKeyboard->isKeyDown(OIS::KC_SPACE) || mouseState.buttonDown(OIS::MB_Right)) && pGU->m_Weapons.size() > 1)
		{
			if( pGU->m_Weapons[1]->m_fLastShootTime  < 0 )
			{
				GameController::getInfoProvider()->shoot(pGU,1);
				pGU->m_Weapons[1]->m_fLastShootTime = pGU->m_Weapons[1]->m_fReloadTime;
			}
		}


		pGU->m_Weapons[0]->m_fLastShootTime -= fTime * 1000.0f;
		pGU->m_Weapons[1]->m_fLastShootTime -= fTime * 1000.0f;
		it++;
	}
	m_pCamera->move(Ogre::Vector3(speed.x* fTime/2.0f,0,speed.z* fTime));
		
//	translateVec *= 0  ;
}

UnitAIController::UnitAIController()
:UnitController(CONTROLLER_TYPE_AI)
{
	m_Name = "ai";
}
UnitAIController::~UnitAIController()
{
}


void UnitAIController::run()
{
	
}
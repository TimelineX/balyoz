#include "UnitController.h"
#include "GameController.h"
#include "EventCollector.h"
#include "GameUnit.h"

using namespace Balyoz;



HumanController::HumanController()
:UnitController(CONTROLLER_HUMAN)
{
	m_pMouse = GameController::getInfoProvider()->getMouse();
	m_pKeyboard = GameController::getInfoProvider()->getKeyboard();
}

HumanController::~HumanController()
{
}


void HumanController::run()
{
	std::list<GameUnit*>::iterator it = m_GameObjectList.begin();
	const std::list<GameUnit*>::iterator endIt = m_GameObjectList.end();

	const OIS::MouseState &mouseState =  m_pMouse->getMouseState();

	if(mouseState.X.rel != 0 )
	{
		m_TranslateVec[0] += mouseState.X.rel / 1000.0f;
	}
	if( mouseState.Y.rel != 0 )
	{
		m_TranslateVec[2] += mouseState.Y.rel / 1000.0f;
	}


	NxOgre::Vec3 currentPos;
	while(it != endIt)
	{
		currentPos = (*it)->m_pBody->getGlobalPosition();
		(*it)->m_pBody->setGlobalPosition( currentPos + m_TranslateVec * ( (*it)->m_Speed / 100.0f ) );
		it++;
	}

	m_TranslateVec *= .985f ;
}

UnitAIController::UnitAIController()
:UnitController(CONTROLLER_AI)
{
}
UnitAIController::~UnitAIController()
{
}


void UnitAIController::run()
{
	
}
#include "GameUnit.h"
#include "Weapon.h"
using namespace Balyoz;

GameUnit::GameUnit(void) : GameObject(NULL)
{
	setAttributes(NULL,NULL,0,0,0,UNIT_TYPE_NONE);
}

GameUnit::GameUnit( std::string* pName,  std::string* pMesh,  std::string* pController, 
						   float health, float armour, float speed,ENUM_UNIT_TYPE type) : GameObject(pName){

	setAttributes(pMesh,pController,health,armour,speed,type);
}
GameUnit::GameUnit( std::string* pName, std::string* pMesh, std::string* pController,float health, float armour,float speed,ENUM_UNIT_TYPE type, std::vector<Weapon*>& weapons) : GameObject(pName){

   m_Weapons = weapons;
   setAttributes(pMesh,pController,health,armour,speed,type);
	
}
void GameUnit::setAttributes( std::string* pMesh, std::string* controller,float health, float armour,float speed,ENUM_UNIT_TYPE type){

									m_pController = controller;
									m_pMesh			= pMesh;
									m_Health		= health;
									m_Armour		= armour;
									m_Speed			= speed;
									m_Type			= type;
									m_GameObjectType = GAME_OBJECT_TYPE_UNIT;


}
GameUnit::~GameUnit(void)
{
}
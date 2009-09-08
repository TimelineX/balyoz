#include "GameUnit.h"
#include "Weapon.h"
using namespace Balyoz;

GameUnit::GameUnit(void) : GameObject("")
{
	setAttributes("","",0,0,0,ENUM_UNIT_TYPE::NONE);
}

GameUnit::GameUnit(const std::string& name, const std::string& mesh, const std::string& controller, 
						   int health, int armour, int speed,ENUM_UNIT_TYPE::TYPE type) : GameObject(name){

	setAttributes(mesh,controller,health,armour,speed,type);
}
GameUnit::GameUnit(const std::string& name,const std::string& mesh,const std::string& controller,int health, int armour,int speed,ENUM_UNIT_TYPE::TYPE type, std::vector<Weapon*>& weapons) : GameObject(name){

   m_Weapons = weapons;
   setAttributes(mesh,controller,health,armour,speed,type);
	
}
void GameUnit::setAttributes(const std::string& mesh,const std::string& controller,int health, int armour,int speed,ENUM_UNIT_TYPE::TYPE type){

									m_Controller	= controller;
									m_Mesh			= mesh;
									m_Health		= health;
									m_Armour		= armour;
									m_Speed			= speed;
									m_Type			= type;

}
GameUnit::~GameUnit(void)
{
}
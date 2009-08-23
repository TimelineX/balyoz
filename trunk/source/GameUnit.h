
#pragma once
#include "gameobject.h"
#include <string>
#include <vector>

class Weapon;

namespace ENUM_UNIT_TYPE{
	enum TYPE{
		AIR,
		NAVY,
		NONE
	};
}

namespace Balyoz{

class GameUnit :
	public GameObject
{
public:
	GameUnit(void);
	GameUnit(std::string name,std::string mesh,std::string controller,int health, int armour,int speed,ENUM_UNIT_TYPE::TYPE type);
	GameUnit(std::string name,std::string mesh,std::string controller,int health, int armour,int speed,ENUM_UNIT_TYPE::TYPE type, std::vector<Weapon*>& weapons);
	~GameUnit(void);

	
	std::string m_Mesh;
	int m_Health;
	int m_Armour;
	int m_Speed;
	std::string m_Controller;
	ENUM_UNIT_TYPE::TYPE m_Type;
	std::vector<Weapon*> m_Weapons;

private:
	void setAttributes(std::string mesh,std::string controller,int health, int armour,int speed,ENUM_UNIT_TYPE::TYPE type);
	
};
}
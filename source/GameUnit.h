
#pragma once
#include "gameobject.h"

#include <string>
#include <vector>
#include "NxOgreOGRE3D.h"
#include "OGRE3DCommon.h"


namespace ENUM_UNIT_TYPE{
	enum TYPE{
		AIR,
		NAVY,
		NONE
	};
}

namespace Balyoz{
class Weapon;

class GameUnit :
	public GameObject
{
public:
	GameUnit(void);
	GameUnit(const std::string& name,const std::string& mesh,const std::string& controller,int health, int armour,int speed,ENUM_UNIT_TYPE::TYPE type);
	GameUnit(const std::string& name,const std::string& mesh,const std::string& controller,int health, int armour,int speed,ENUM_UNIT_TYPE::TYPE type, std::vector<Weapon*>& weapons);
	~GameUnit();

	
	std::string m_Mesh;
	int m_Health;
	int m_Armour;
	int m_Speed;
	std::string m_Controller;
	ENUM_UNIT_TYPE::TYPE m_Type;
	std::vector<Weapon*> m_Weapons;

	OGRE3DBody		*m_pBody;


private:
	void setAttributes(const std::string& mesh,const std::string& controller,int health, int armour,int speed,ENUM_UNIT_TYPE::TYPE type);

};
}
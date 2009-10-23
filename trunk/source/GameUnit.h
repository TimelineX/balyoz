
#pragma once
#include "gameobject.h"

#include <string>
#include <vector>
//#include "NxOgreOGRE3D.h"
#include "OGRE3DCommon.h"
#include "PhysicsObject.h"



namespace Balyoz{
class Weapon;

	enum ENUM_UNIT_TYPE{
		UNIT_TYPE_NONE = 0,
		UNIT_TYPE_AIR,
		UNIT_TYPE_NAVY
	};

class GameUnit :
	public GameObject
{
public:
	GameUnit(std::string* pName = NULL);
	GameUnit( std::string* pName, std::string* pMesh, std::string* pController,float health, float armour,float speed,ENUM_UNIT_TYPE type);
	GameUnit( std::string* pName, std::string* pMesh, std::string* pController,float health, float armour,float speed,ENUM_UNIT_TYPE type, std::vector<Weapon*>& weapons);
	~GameUnit();

	
	float m_Health;
	float m_Armour;
	float m_Speed;
	ENUM_UNIT_TYPE m_Type;
	std::vector<Weapon*> m_Weapons;
	std::vector<std::string> m_WeaponNames;

	PhysicsObject*		m_pBody;
	std::string*		m_pMesh;
	std::string*		m_pController;


private:
	void setAttributes( std::string* mesh, std::string* controller,float health, float armour,float speed,ENUM_UNIT_TYPE type);

};



}
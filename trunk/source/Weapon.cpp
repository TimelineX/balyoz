#include "Weapon.h"
#include "Bullet.h"


Balyoz::Weapon::Weapon(void)
{
	Weapon("");
}

Balyoz::Weapon::~Weapon(void)
{
}

Balyoz::Weapon::Weapon(std::string name){
	m_Name			= name;
	m_Controller	= "";
	m_Effect		= NONE;
	m_Explosion		= "";
	m_LifeTime		= 0;
	m_MeshFileName	= "";
	m_Radius		= 0;
	m_Particles		= "";
}

Balyoz::Weapon::Weapon(std::string Name, 
					   std::string MeshFileName, 
					   unsigned int Power, 
					   unsigned int Radius, 
					   unsigned int LifeTime, 
					   std::string  Explosion, 
					   std::string  Particles, 
					   std::string  Controller, 
					   Balyoz::EFFECT Effect){

   m_Name			= Name;
   m_MeshFileName	= MeshFileName;
   m_Power			= Power;
   m_Radius			= Radius;
   m_LifeTime		= LifeTime;
   m_Explosion		= Explosion;
   m_Particles		= Particles;
   m_Controller		= Controller;
   m_Effect			= Effect;

}

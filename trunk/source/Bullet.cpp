#include "Bullet.h"

Bullet::Bullet(void)
{

}

Bullet::~Bullet(void)
{
}

Bullet::Bullet(std::string name){

}
Bullet::Bullet(unsigned int Power, 
			   unsigned int Radius, 
			   EFFECT		Effect, 
			   unsigned int LifeTime, 
			   std::string Explosion, 
			   std::string Particles, 
			   std::string Controller){

   m_Power		= Power;
   m_Radius		= Radius;
   m_Effect		= Effect;
   m_LifeTime	= LifeTime;
   m_Explosion	= Explosion;
   m_Particles	= Particles;
   m_Controller = Controller;
}

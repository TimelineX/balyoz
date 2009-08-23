#include "Bullet.h"

Bullet::Bullet() : GameObject("")
{
	setBulletAttributes(0,0,0,"","","",NONE);

}
Bullet::Bullet(std::string name) : GameObject(name){

	setBulletAttributes(0,0,0,"","","",NONE);
}
Bullet::Bullet(std::string name,
			   unsigned int Power, 
			   unsigned int Radius,
			   unsigned int LifeTime,
			   std::string Explosion, 
			   std::string Particles, 
			   std::string Controller,
			   EFFECT		Effect) : GameObject(name){

	setBulletAttributes(Power,Radius,LifeTime,Explosion,Particles,Controller,Effect);
}
Bullet::Bullet( unsigned int Power, unsigned int Radius, EFFECT Effect, 
			   unsigned int LifeTime, std::string Explosion, 
			   std::string Particles, std::string Controller ){

	setBulletAttributes(Power,Radius,LifeTime,Explosion,Particles,Controller,Effect);
}
void Bullet::setBulletAttributes(unsigned int pow, unsigned int radius, unsigned int lifetime, 
								 std::string explosion, std::string particles, std::string controller, EFFECT effect){

									 m_Power		= pow;
									 m_Radius		= radius;
									 m_LifeTime		= lifetime;
									 m_Explosion	= explosion;
									 m_Particles	= particles;
									 m_Controller	= controller;
									 m_Effect		= effect;

}

Bullet::~Bullet(void)
{
}

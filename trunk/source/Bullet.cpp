#include "Bullet.h"

Bullet::Bullet() : GameObject("")
{
	setBulletAttributes(0,0,0,"","","",NONE);

}
Bullet::Bullet(const std::string& name) : GameObject(name){

	setBulletAttributes(0,0,0,"","","",NONE);
}
Bullet::Bullet(const std::string& name,
			   unsigned int			Power, 
			   float				Radius,
			   unsigned int			LifeTime,
			   const std::string&	Explosion, 
			   const std::string&	Particles, 
			   const std::string&	Controller,
			   EFFECT				Effect) : GameObject(name){

	setBulletAttributes(Power,Radius,LifeTime,Explosion,Particles,Controller,Effect);
}
Bullet::Bullet( unsigned int Power, float Radius, EFFECT Effect, 
			   unsigned int LifeTime, const std::string& Explosion, 
			   const std::string& Particles, const std::string& Controller ){

	setBulletAttributes(Power,Radius,LifeTime,Explosion,Particles,Controller,Effect);
}
void Bullet::setBulletAttributes(unsigned int pow, float radius, unsigned int lifetime, 
								 const std::string& explosion,const  std::string& particles,const  std::string& controller, EFFECT effect){

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

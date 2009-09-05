#include "GameObject.h"

GameObject::GameObject(void)
{
}

GameObject::~GameObject(void)
{
}
GameObject::GameObject(const std::string& name){
	m_Name = name;
}
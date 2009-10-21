#include "GameObject.h"
using namespace Balyoz;
GameObject::GameObject(void)
{
	m_pName = 0;
}

GameObject::~GameObject(void)
{
}
GameObject::GameObject(std::string* pName){
	m_pName = pName;
}
#pragma once
#include <string>

class GameObject
{
public:
	GameObject(void);
	GameObject(std::string);
	~GameObject(void);
	std::string m_Name;
};

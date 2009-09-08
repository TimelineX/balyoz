#pragma once
#include <string>

namespace Balyoz
{
	class GameObject
	{
	public:
		GameObject(void);
		GameObject(const std::string&);
		~GameObject(void);
		std::string m_Name;
	};
}
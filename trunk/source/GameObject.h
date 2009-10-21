#pragma once
#include <string>

namespace Balyoz
{
	enum ENUM_GAME_OBJECT_TYPE
	{
		GAME_OBJECT_TYPE_NONE = 0,
		GAME_OBJECT_TYPE_STATIC = 1<<4,
		GAME_OBJECT_TYPE_UNIT = 1 << 8
	};
	class GameObject
	{
	public:
		GameObject(void);
		GameObject(std::string* pName);
		~GameObject(void);
		std::string* m_pName;
		ENUM_GAME_OBJECT_TYPE	m_GameObjectType;
	};
}
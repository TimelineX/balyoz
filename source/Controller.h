#pragma once
#include <list>
#include <string>
#include "GameObject.h"

template <typename GameObjectClass>
class Controller
{
public:
	Controller(void){};
	~Controller(void){};

	template <typename GameObjectClass>
	void registerGameObject(GameObjectClass* pGameObject)
	{
		m_GameObjectList.push_back(pGameObject);
	}

	template <typename GameObjectClass>
	void unregisterGameObject(GameObjectClass* pGameObject)
	{
		m_GameObjectList.remove(pGameObject);
	}

	template <typename GameObjectClass>
	void unregisterGameObjectByName(std::string &gameUnitName)
	{
		std::list<GameObjectClass*>::iterator it = m_GameObjectList.begin();
		const std::list<GameObjectClass*>::iterator endIt = m_GameObjectList.end();
		GameObject* pGO;
		while(it != endIt)
		{
			pGO = static_cast<GameObject>(*it);
			if(  pGO->m_Name.compare(gameUnitName) == 0 )
			{
				
				m_GameObjects.erase(it);
				return;
			}
			it++;
		}

	}

	virtual void run() = 0;

	std::list<GameObjectClass*> m_GameObjectList;	
};

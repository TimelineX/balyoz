#pragma once
#include <list>
#include <string>
#include "GameObject.h"

template <typename GameObjectClass, typename RunInfo>
class Controller
{
public:
	Controller(void){ m_pRunInfoParameter = 0; };
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

	template <typename RunInfo>
	void setRunInfo( RunInfo* pRunInfoParameter){ m_pRunInfoParameter = pRunInfoParameter;};


	
	virtual void run() = 0;
	
	RunInfo *m_pRunInfoParameter;
	std::list<GameObjectClass*> m_GameObjectList;	
};

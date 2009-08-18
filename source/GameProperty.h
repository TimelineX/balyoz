#pragma once
#include "XmlMapProperty.h"
#include <vector>


class GameProperty : public XmlMapProperty
{
public:
	GameProperty(void);
	virtual ~GameProperty(void);

	virtual bool set(const std::string &parameterName, const std::string &parameterValue);
	std::vector<std::string> m_Levels;
};

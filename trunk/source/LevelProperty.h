#pragma once
#include <string>
#include "XmlMapProperty.h"

class LevelProperty 
	: public XmlMapProperty
{
public:
	LevelProperty();
	~LevelProperty();
	virtual bool set(const std::string &parameterName, const std::string &parameterValue);
	std::string m_Terrain;
	std::string m_Map;
	std::string m_SkyBox;
};
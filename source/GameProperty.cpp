#include "GameProperty.h"
#define USE_REPORT
#include "macros.h"

GameProperty::GameProperty(void)
{
}

GameProperty::~GameProperty(void)
{
}
bool GameProperty::set(const std::string &parameterName, const std::string &parameterValue)
{
	if( XmlMapProperty::set( parameterName,parameterValue ) )
	{

	}
	else if (parameterName.compare("/level") == 0)
	{
		m_Levels.push_back(parameterValue);
		return true;
	}
	else
	{
		REPORT_WARNING((std::string("cannot set property:") + parameterName + " value:" + parameterValue));
		return false;
	}
	return false;
}

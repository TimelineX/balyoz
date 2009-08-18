#include "LevelProperty.h"

#define USE_REPORT
#include "macros.h"


LevelProperty::LevelProperty()
{

}
LevelProperty::~LevelProperty()
{

}


bool LevelProperty::set(const std::string &parameterName, const std::string &parameterValue)
{
	if( XmlMapProperty::set( parameterName,parameterValue ) )
	{

	}
	else if( parameterName.compare("/terrain") == 0 )
	{
		m_Terrain = parameterValue;
	}
	else if( parameterName.compare("/map") == 0 )
	{
		m_Map = parameterValue;
	}
	else if( parameterName.compare("/skybox") == 0 )
	{
		m_SkyBox = parameterValue;
	}
	else
	{
		REPORT_WARNING((std::string("cannot set property:") + parameterName + " value:" + parameterValue));
		return false;
	}

	return true;
}
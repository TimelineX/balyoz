#include "TerrainProperty.h"

#define USE_REPORT
#include "macros.h"


bool TerrainProperty::set(const std::string &parameterName, const std::string &parameterValue)
{
	if( XmlMapProperty::set( parameterName,parameterValue ) )
	{

	}
	else if( parameterName.compare("/type") == 0 )
	{
		m_Type = parameterValue;
	}
	else if( parameterName.compare("/length") == 0 )
	{
		m_fLength = atof(parameterValue.c_str());
	}
	else
	{
		REPORT_WARNING((std::string("cannot set property:") + parameterName + " value:" + parameterValue));
		return false;
	}

	return true;
}
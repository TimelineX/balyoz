#include "WeaponProperty.h"

#define USE_REPORT
#include "macros.h"

WeaponProperty::WeaponProperty()
{
}

WeaponProperty::~WeaponProperty()
{

}

bool WeaponProperty::set(const std::string &parameterName, const std::string &parameterValue)
{
	if( XmlMapProperty::set( parameterName,parameterValue ) )
	{

	}
	else if( parameterName.compare("/power") == 0 )
	{
		m_iPower = atoi(parameterValue.c_str());
	}
	//else if( parameterName.compare("type") == 0 )
	//{
	//	m_iType = atoi(parameterValue.c_str());
	//}
	else if( parameterName.compare("/radius") == 0 )
	{
		m_fRadius = (float)atof(parameterValue.c_str());
	}
	else if( parameterName.compare("/lifetime") == 0 )
	{
		m_iLifeTime = atoi(parameterValue.c_str());
	}
	else if( parameterName.compare("/mesh") == 0 )
	{
		m_Mesh = parameterValue;
	}
	else if( parameterName.compare("/effect") == 0 )
	{
		m_Effect = parameterValue;
	}
	else if( parameterName.compare("/particles") == 0 )
	{
		m_Particles = parameterValue;
	}
	else if( parameterName.compare("/explosion") == 0 )
	{
		m_Explosion = parameterValue;
	}
	else if( parameterName.compare("/controller") == 0 )
	{
		m_Controller = parameterValue;
	}
	else
	{
		REPORT_WARNING((std::string("cannot set property:") + parameterName + " value:" + parameterValue));
		return false;
	}
	return true;
}

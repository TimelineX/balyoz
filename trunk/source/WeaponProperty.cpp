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
	else if( parameterName.compare("/bullet/power") == 0 )
	{
		m_fPower = atof(parameterValue.c_str());
	}
	else if( parameterName.compare("/reloadtime") == 0 )
	{
		m_fReloadTime = atof(parameterValue.c_str());
	}
	else if( parameterName.compare("/numofbullets/capacity") == 0 )
	{
		m_iCapacity = atoi(parameterValue.c_str());
	}
	else if( parameterName.compare("/numofbullets/initial") == 0 )
	{
		m_iInitial = atoi(parameterValue.c_str());
	}
	else if( parameterName.compare("/numofbullets/maximum") == 0 )
	{
		m_iMaximum = atoi(parameterValue.c_str());
	}
	else if( parameterName.compare("/numofbullets/minimum") == 0 )
	{
		m_iMinimum = atoi(parameterValue.c_str());
	}
	else if( parameterName.compare("/numofbullets/anglebetweenbullets") == 0 )
	{
		m_iAngle = atoi(parameterValue.c_str());
	}
	//else if( parameterName.compare("type") == 0 )
	//{
	//	m_iType = atoi(parameterValue.c_str());
	//}
	else if( parameterName.compare("/bullet/initialspeed") == 0 )
	{
		m_fInitialSpeed = (float)atof(parameterValue.c_str());
	}
	else if( parameterName.compare("/bullet/maximumspeed") == 0 )
	{
		m_fMaximumSpeed = (float)atof(parameterValue.c_str());
	}
	else if( parameterName.compare("/bullet/radius") == 0 )
	{
		m_fRadius = (float)atof(parameterValue.c_str());
	}
	else if( parameterName.compare("/bullet/lifetime") == 0 )
	{
		m_fLifeTime = atof(parameterValue.c_str());
	}
	else if( parameterName.compare("/mesh") == 0 )
	{
		m_Mesh = parameterValue;
	}
	else if( parameterName.compare("/bullet/effect") == 0 )
	{
		m_Effect = parameterValue;
	}
	else if( parameterName.compare("/bullet/particles") == 0 )
	{
		m_Particles = parameterValue;
	}
	else if( parameterName.compare("/bullet/explosion") == 0 )
	{
		m_Explosion = parameterValue;
	}
	else if( parameterName.compare("/bullet/controller") == 0 )
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

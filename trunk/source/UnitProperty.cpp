#include "UnitProperty.h"
#define USE_REPORT
#include "macros.h"



UnitProperty::UnitProperty()
{

}
UnitProperty::~UnitProperty()
{

}

bool UnitProperty::set(const std::string &parameterName, const std::string &parameterValue)
{
	if( XmlMapProperty::set(parameterName,parameterValue) )
	{
	}
	else if(parameterName.compare("/health") == 0)
	{
		m_iHealth = atoi(parameterValue.c_str());		
	}
	else if( parameterName.compare("/mesh") == 0 )
	{
		m_Mesh = parameterValue;
	}
	else if( parameterName.compare("/type") == 0 )
	{
		m_Type = parameterValue;
	}
	else if (parameterName.compare("/armour") == 0)
	{
		m_iArmour  = atoi(parameterValue.c_str());	
	}
	else if (parameterName.compare("/controller") == 0)
	{
		m_Controller = parameterValue;	
	}
	else if (parameterName.compare("/weapon") == 0)
	{
		//m_Weapon = parameterValue;	
		m_Weapons.push_back(parameterValue);
	}

	else if (parameterName.compare("/type") == 0)
	{
		m_Type = parameterValue;	
	}
	else
	{
		REPORT_WARNING((std::string("cannot set property:") + parameterName + " value:" + parameterValue));
		return false;
	}
	return true;
}
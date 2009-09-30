#include "BulletControllerProperty.h"
#define USE_REPORT
#include "macros.h"
using namespace Balyoz;
BulletControllerProperty::BulletControllerProperty(void)
{
}

BulletControllerProperty::~BulletControllerProperty(void)
{
}

bool BulletControllerProperty::set(const std::string &parameterName, const std::string &parameterValue)
{
	if( XmlMapProperty::set( parameterName,parameterValue ) )
	{

	}
	else if (parameterName.compare("/behaviour") == 0)
	{
		if (parameterValue.compare("horizontal") ==0)
		{
			m_Behavoiur = BULLET_BEHAVIOUR_HORIZONTAL;
		}
		else if (parameterValue.compare("vertical") ==0)
		{
			m_Behavoiur = BULLET_BEHAVIOUR_VERTICAL;

		}
		else if (parameterValue.compare("guided") ==0)
		{
			m_Behavoiur = BULLET_BEHAVIOUR_GUIDED;

		}
	}
	else if (parameterName.compare("/aiming") == 0)
	{
		if (parameterValue.compare("none") ==0)
		{
			m_Aiming = BULLET_AIMING_NONE;
		}
		else if (parameterValue.compare("weakest") ==0)
		{
			m_Aiming = BULLET_AIMING_WEAKEST;

		}
		else if (parameterValue.compare("strongest") ==0)
		{
			m_Aiming = BULLET_AIMING_STRONGEST;

		}
	}
	else if (parameterName.compare("/accuracy") == 0)
	{
		m_fAccuracy = atof(parameterValue.c_str());
	}
	else 
	{
		REPORT_WARNING((std::string("cannot set property:") + parameterName + " value:" + parameterValue));

		return false;
	}
	return true;
}

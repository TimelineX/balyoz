#include "XmlMapProperty.h"

XmlMapProperty::XmlMapProperty(void)
{
}

XmlMapProperty::~XmlMapProperty(void)
{
}
bool XmlMapProperty::set(const std::string &parameterName, const std::string &parameterValue)
{
	if (parameterName.compare("/name") == 0)
	{
		m_Name = parameterValue;
		return true;
	}
	return false;
}

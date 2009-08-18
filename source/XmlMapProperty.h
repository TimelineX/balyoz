#pragma once
#include <string>
class XmlMapProperty
{
public:
	XmlMapProperty(void);
	virtual ~XmlMapProperty(void);

	virtual bool set(const std::string &parameterName, const std::string &parameterValue);

	std::string m_Name;
};

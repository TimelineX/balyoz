#pragma once
#include <string>
class XmlMapProperty
{
public:
	XmlMapProperty(void);
	virtual ~XmlMapProperty(void);

	virtual bool set(const std::string &parameterName, const std::string &parameterValue);
	virtual void childTagStart( const std::string &tagName ){};
	virtual void childTagEnd( const std::string &tagName ){};
	std::string m_Name;
};

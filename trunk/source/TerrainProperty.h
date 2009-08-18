#include "XmlMapProperty.h"


class TerrainProperty 
	: public XmlMapProperty
{
public:
	TerrainProperty(){};
	virtual ~TerrainProperty(){};
	
	virtual bool set(const std::string &parameterName, const std::string &parameterValue);
	float m_fLength;
	std::string m_Type;
};

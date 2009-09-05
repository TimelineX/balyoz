#include "MapProperty.h"
#include "OgreStringConverter.h"
#define USE_ASSERT 
#define USE_REPORT
#define USE_SAFE
#include "macros.h"


MapProperty::MapProperty()
{
	m_pLastAddUnit = 0;
}

MapProperty::~MapProperty()
{
}

bool MapProperty::set(const std::string &parameterName, const std::string &parameterValue)
{
	if( XmlMapProperty::set(parameterName,parameterValue) )
	{
	}
	else if(parameterName.compare("/name") == 0)
	{
		m_Name = parameterValue;
	}
	else if(parameterName.compare("/unit/name") == 0)
	{
		m_pLastAddUnit = new UnitData();
		m_Units.push_back(m_pLastAddUnit);
		m_pLastAddUnit->m_Name = parameterValue;
	}
	else if(parameterName.compare("/unit/orientation") == 0)
	{
		m_pLastAddUnit->m_Orientation = Ogre::StringConverter::parseVector3(parameterValue);
	}
	else if(parameterName.compare("/unit/position") == 0)
	{
		m_pLastAddUnit->m_Position = Ogre::StringConverter::parseVector3(parameterValue);
	}
	else
	{
		REPORT_WARNING((std::string("cannot set property:") + parameterName + " value:" + parameterValue));
		return false;
	}
	return true;
}
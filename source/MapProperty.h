#pragma once
#include "XmlMapProperty.h"

#include <OgreVector3.h>

typedef struct __UnitData
{
	std::string m_Name;
	Ogre::Vector3 m_Position;
	Ogre::Vector3 m_Orientation;
}UnitData;

class MapProperty 
	: public XmlMapProperty
{
public:


	MapProperty();
	virtual ~MapProperty();

	virtual bool set(const std::string &parameterName, const std::string &parameterValue);
	std::list<UnitData*> m_Units;

private:
	UnitData *m_pLastAddUnit;
};

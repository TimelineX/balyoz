#include "XmlMapProperty.h"

#include <OgreVector3.h>

class MapProperty 
	: public XmlMapProperty
{
public:
	typedef struct __UnitData
	{
		std::string m_Name;
		Ogre::Vector3 m_Position;
		Ogre::Vector3 m_Orientation;
	}UnitData;

	MapProperty();
	virtual ~MapProperty();

	virtual bool set(const std::string &parameterName, const std::string &parameterValue);
	std::vector<UnitData*> m_Units;

private:
	UnitData *m_pLastAddUnit;
};

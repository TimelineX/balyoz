#include "XmlMapProperty.h"
#include <vector>

class UnitProperty 
	: public XmlMapProperty
{
public:
	UnitProperty();
	virtual ~UnitProperty();
	
	virtual bool set(const std::string &parameterName, const std::string &parameterValue);
	int m_iHealth;
	int m_iArmour;
	std::string m_Mesh;
	std::string m_Controller;
	std::vector<std::string> m_Weapons;
	//std::string m_Weapon;
	std::string m_Type;
};

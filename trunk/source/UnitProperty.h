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
	int m_Speed;
	std::string m_Mesh;
	std::string m_Controller;	
	std::string m_Name;
	std::string m_Type;
	std::vector<std::string> m_Weapons;
};

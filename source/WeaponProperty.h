#include "XmlMapProperty.h"

class WeaponProperty 
	: public XmlMapProperty
{
public:
	WeaponProperty();
	virtual ~WeaponProperty();

	virtual bool set(const std::string &parameterName, const std::string &parameterValue);
	int m_iPower;
	float m_fRadius;
	int m_iLifeTime;
	//int m_iType;
	std::string m_Mesh;
	std::string m_Effect;
	std::string m_Particles;
	std::string m_Explosion;
	std::string m_Controller;
};



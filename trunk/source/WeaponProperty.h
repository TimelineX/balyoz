#include "XmlMapProperty.h"

class WeaponProperty 
	: public XmlMapProperty
{
public:
	WeaponProperty();
	virtual ~WeaponProperty();

	virtual bool set(const std::string &parameterName, const std::string &parameterValue);
	unsigned int m_iPower;
	float m_fRadius;
	unsigned int m_iLifeTime;
	unsigned int m_iCapacity;
	unsigned int m_iMinimum;
	unsigned int m_iMaximum;
	unsigned int m_iAngle;
	unsigned int m_iReloadTime;
	unsigned int m_iInitial;

	std::string m_Mesh;
	std::string m_Effect;
	std::string m_Particles;
	std::string m_Explosion;
	std::string m_Controller;
};



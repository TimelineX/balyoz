#include "XmlMapProperty.h"

class WeaponProperty 
	: public XmlMapProperty
{
public:
	WeaponProperty();
	virtual ~WeaponProperty();

	virtual bool set(const std::string &parameterName, const std::string &parameterValue);
	float m_fPower;
	float m_fRadius;
	float m_fLifeTime;
	float m_fInitialSpeed;
	float m_fMaximumSpeed;
	unsigned int m_iCapacity;
	unsigned int m_iMinimum;
	unsigned int m_iMaximum;
	unsigned int m_iAngle;
	float m_fReloadTime;
	unsigned int m_iInitial;

	std::string m_Mesh;
	std::string m_Effect;
	std::string m_Particles;
	std::string m_Explosion;
	std::string m_Controller;
};



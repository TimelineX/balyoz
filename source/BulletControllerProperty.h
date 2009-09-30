#pragma once
#include "xmlmapproperty.h"
namespace Balyoz
{
	typedef enum BULLET_BEHAVIOUR
	{
		BULLET_BEHAVIOUR_HORIZONTAL = 1,
		BULLET_BEHAVIOUR_VERTICAL,
		BULLET_BEHAVIOUR_GUIDED
	};
	typedef enum BULLET_AIMING
	{
		BULLET_AIMING_NONE = 1,
		BULLET_AIMING_WEAKEST,
		BULLET_AIMING_STRONGEST
	};

	class BulletControllerProperty :
		public XmlMapProperty
	{
	public:
		BulletControllerProperty(void);
		~BulletControllerProperty(void);
		virtual bool set(const std::string &parameterName, const std::string &parameterValue);

		BULLET_AIMING m_Aiming;
		BULLET_BEHAVIOUR m_Behavoiur;
		float m_fAccuracy;
	};
}
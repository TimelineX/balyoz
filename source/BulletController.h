#pragma once
#include "Bullet.h"
#include "Controller.h"

namespace Balyoz
{
	class Bullet;

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

	class BulletController :
		public Controller<Bullet>
	{
	public:
		BulletController(void);
		~BulletController(void);

		void run() ;

		BULLET_AIMING m_Aiming;
		BULLET_BEHAVIOUR m_Behavoiur;
		float m_fAccuracy;

	};

};
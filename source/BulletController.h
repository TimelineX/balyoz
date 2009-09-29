#pragma once
#include "Bullet.h"
#include "Controller.h"

namespace Balyoz
{
	class BulletController :
		public Controller<Bullet>
	{
	public:
		BulletController(void);
		~BulletController(void);

		virtual void run() ;

	};


	class DummyBulletController
		: public BulletController
	{
	public:
		DummyBulletController();
		~DummyBulletController();
		void run() ;
	};

};
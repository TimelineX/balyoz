#pragma once
#include "Bullet.h"
#include <list>
#include "GameUnit.h"
#include "Controller.h"

namespace Balyoz
{
	class BulletController :
		public Controller<Bullet,std::list<GameUnit*>>
	{
	public:
		BulletController(void);
		~BulletController(void);

		void run() ;

	};



};
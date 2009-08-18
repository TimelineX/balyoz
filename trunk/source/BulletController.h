#pragma once
#include "Bullet.h"
class BulletController :
	public Controller<Bullet>
{
public:
	BulletController(void);
	~BulletController(void);
};

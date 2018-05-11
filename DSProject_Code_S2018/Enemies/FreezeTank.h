#pragma once
#include "Enemy.h"
class Battle;

class FreezeTank :
	public Enemy
{

public:
	FreezeTank(color r_c, REGION r_region, int d);
	void Attack(Battle*);
	virtual void setPow(int);
	~FreezeTank();
};


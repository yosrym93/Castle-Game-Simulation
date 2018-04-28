#pragma once
#include "Enemy.h"
class Battle;
class Tank :
	public Enemy
{

public:
	Tank(color r_c, REGION r_region, int d);
	void Attack(Battle*);
	~Tank();
};


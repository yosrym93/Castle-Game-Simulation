#pragma once
#include "Enemy.h"
class Battle;
class Fighter :
	public Enemy
{
public:
	Fighter(color r_c, REGION r_region, int d);
	void Attack(Battle*);
	~Fighter();
};


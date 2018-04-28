#pragma once
#include "Enemy.h"
class Battle;
class Paver :
	public Enemy
{
public:
	Paver(color r_c, REGION r_region,int d);
	void Attack(Battle*);
	~Paver();
};


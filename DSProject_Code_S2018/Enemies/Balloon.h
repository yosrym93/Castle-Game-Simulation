#pragma once
#include"Enemy.h"
class Battle;
class Balloon :
	public Enemy
{
public:
	Balloon(color r_c, REGION r_region, int d);
	void Attack(Battle*);
	~Balloon();
};


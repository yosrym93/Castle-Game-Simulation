#pragma once
#include "Enemy.h"
class Tank :
	public Enemy
{

public:
	Tank(color r_c, REGION r_region, int d);
	~Tank();
};


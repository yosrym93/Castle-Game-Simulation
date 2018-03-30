#pragma once
#include "Enemies\Enemy.h"
class Fighter :
	public Enemy
{
public:
	Fighter(color r_c, REGION r_region, int d);
	~Fighter();
};


#pragma once
#include "Enemy.h"
class Shielded :
	public Enemy
{
	double Priority;
public:
	Shielded(color r_c, REGION r_region, int d);
	~Shielded();
};


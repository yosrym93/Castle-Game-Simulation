#pragma once
#include "Enemy.h"
class Shielded :
	public Enemy
{
	double Periority;
public:
	Shielded(color r_c, REGION r_region, int d);
	~Shielded();
};


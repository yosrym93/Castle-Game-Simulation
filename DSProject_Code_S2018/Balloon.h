#pragma once
#include"Enemies\Enemy.h"
class Balloon :
	public Enemy
{
public:
	Balloon(color r_c, REGION r_region, int d);
	~Balloon();
};


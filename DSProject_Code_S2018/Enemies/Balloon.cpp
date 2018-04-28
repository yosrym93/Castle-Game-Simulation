#include "Balloon.h"
#include"d:\thecastle\DSProject_Code_S2018\Battle.h"


Balloon::Balloon(color r_c, REGION r_region, int d):Enemy(r_c,r_region,d)
{
}

void Balloon::Attack(Battle *b)
{
	if (canAttack(b))
	{
		b->healEnemies(getRegion());
	}
}


Balloon::~Balloon()
{
}

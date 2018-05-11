#include "Balloon.h"
#include"..\Battle.h"


Balloon::Balloon(color r_c, REGION r_region, int d):Enemy(r_c,r_region,d)
{
	K = 1;
	if (firePower > 15)
		firePower = 15;
}

void Balloon::Attack(Battle *b)
{
	int Arr[2];
	Arr[0] = Distance;
	Arr[1] = firePower;
	int*A = Arr;
	if (canAttack(b->getCurrentTime()))
	{
		b->healEnemies(getRegion(),A);
	}
}


Balloon::~Balloon()
{
}

#include "Balloon.h"
#include"..\Battle.h"


Balloon::Balloon(color r_c, REGION r_region, int d):Enemy(r_c,r_region,d)
{
	if (firePower > 20)
		firePower = 20;
}

void Balloon::Attack(Battle *b)
{
	int Arr[2];
	Arr[0] = Distance;
	Arr[1] = int(firePower);
	int*A = Arr;
	if (canAttack(b->getCurrentTime()))
	{
		b->healEnemies(getRegion(),A);
	}
}


Balloon::~Balloon()
{
}

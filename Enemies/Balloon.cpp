#include "Balloon.h"
#include"..\Battle.h"


Balloon::Balloon(color r_c, REGION r_region, int d):Enemy(r_c,r_region,d)
{
	K = 1;

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

void Balloon::setPow(int rpow)
{
	firePower = (rpow > 0) ? rpow : 10;//assuming that the default is 10
	if (firePower > 15)
		firePower = 15;
}


Balloon::~Balloon()
{
}

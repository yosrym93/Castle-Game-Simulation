#include "FreezeTank.h"
#include"..\Battle.h"


FreezeTank::FreezeTank(color r_c, REGION r_region, int d):Enemy(r_c,r_region,d)
{
	K = 2;
	if (firePower < 10)
		firePower = 10;
	else if (firePower > 50)
		firePower = 50;
	else 
		firePower = firePower;

}

void FreezeTank::Attack(Battle *b)
{
	if (canAttack(b->getCurrentTime())&&(Distance<firePower))
	{
		b->getCastle()->getTower(getRegion())->freeze(b->getCurrentTime());
		b->playFreezingSound();
	}
}


FreezeTank::~FreezeTank()
{
}

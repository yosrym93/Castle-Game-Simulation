#include "FreezeTank.h"
#include"..\Battle.h"


FreezeTank::FreezeTank(color r_c, REGION r_region, int d):Enemy(r_c,r_region,d)
{
	if (int(firePower) < 10)
		firePower = 10;
	else if (int(firePower) > 60)
		firePower = 60;
	else 
		firePower = int(firePower);

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

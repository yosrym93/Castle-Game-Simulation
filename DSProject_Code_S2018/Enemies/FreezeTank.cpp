#include "FreezeTank.h"
#include"..\Battle.h"


FreezeTank::FreezeTank(color r_c, REGION r_region, int d):Enemy(r_c,r_region,d)
{
}

void FreezeTank::Attack(Battle *b)
{
	if (canAttack(b->getCurrentTime()))
	{
		b->getCastle()->getTower(getRegion())->freeze(b->getCurrentTime());
		b->playFreezingSound();
	}
}


FreezeTank::~FreezeTank()
{
}

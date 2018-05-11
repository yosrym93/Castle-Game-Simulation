#include "Shielded.h"
#include"..\Battle.h"

Shielded::Shielded(color r_c, REGION r_region, int d):Enemy(r_c, r_region, d)
{
	K = 2;
}

void Shielded::Attack(Battle *b)
{
	if (canAttack(b->getCurrentTime()))
	{
		b->getCastle()->getTower(getRegion())->damage((float)K / (float)Distance*firePower);
	}
}


Shielded::~Shielded()
{
}

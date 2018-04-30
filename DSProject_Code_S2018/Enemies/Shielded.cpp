#include "Shielded.h"
#include"..\Battle.h"

Shielded::Shielded(color r_c, REGION r_region, int d):Enemy(r_c, r_region, d)
{
}

void Shielded::Attack(Battle *b)
{
	if (canAttack(b))
	{
		b->getCastle()->getTower(getRegion())->damage(float(K / Distance)*firePower);
	}
}


Shielded::~Shielded()
{
}

#include "Fighter.h"
#include "..\Battle.h"

Fighter::Fighter(color r_c, REGION r_region, int d):Enemy(r_c, r_region, d)
{
}

void Fighter::Attack(Battle *b)
{
	if (canAttack(b))
	{
		b->getCastle()->getTower(getRegion())->damage(float(K / Distance)*firePower);
	}
	
}






Fighter::~Fighter()
{
}

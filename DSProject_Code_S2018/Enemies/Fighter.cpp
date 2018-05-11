#include "Fighter.h"
#include "..\Battle.h"

Fighter::Fighter(color r_c, REGION r_region, int d):Enemy(r_c, r_region, d)
{
	K = 1;
}

void Fighter::Attack(Battle *b)
{
	if (canAttack(b->getCurrentTime()))
	{
		b->getCastle()->getTower(getRegion())->damage((float)K / (float)Distance*firePower);
	}
	
}






Fighter::~Fighter()
{
}

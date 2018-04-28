#include "Fighter.h"
#include "d:\thecastle\DSProject_Code_S2018\Battle.h"

Fighter::Fighter(color r_c, REGION r_region, int d):Enemy(r_c, r_region, d)
{
}

void Fighter::Attack(Battle *b)
{
	if (canAttack(b))
	{
		b->GetCastle()->getTower(getRegion())->damage(float(K / Distance)*firePower);
	}
	
}






Fighter::~Fighter()
{
}

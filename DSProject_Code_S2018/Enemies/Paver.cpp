#include "Paver.h"
#include"..\Battle.h"


Paver::Paver(color r_c, REGION r_region,int d):Enemy(r_c,r_region,d)
{
}

void Paver::Attack(Battle *b)
{
	if (canAttack(b->getCurrentTime()))
	{
		b->pave(getRegion(),getDistance(),getFirePower());
	}
}


Paver::~Paver()
{
}

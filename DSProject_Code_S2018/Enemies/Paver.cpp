#include "Paver.h"
#include"..\Battle.h"


Paver::Paver(color r_c, REGION r_region,int d):Enemy(r_c,r_region,d)
{
	K = 1;
}

void Paver::Attack(Battle *b)
{
	if (canAttack(b->getCurrentTime()))
	{
		for (int i = 0; i < firePower; i++)
			decrementDist();
		b->pave(Region,Distance);
	}
}


Paver::~Paver()
{
}

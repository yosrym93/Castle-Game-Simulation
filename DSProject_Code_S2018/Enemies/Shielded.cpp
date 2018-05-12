#include "Shielded.h"
#include"..\Battle.h"

Shielded::Shielded(color r_c, REGION r_region, int d):Enemy(r_c, r_region, d)
{
	Priority = 0;
	K = 2;
}

void Shielded::Attack(Battle *b)
{
	if (canAttack(b->getCurrentTime()))
	{
		b->getCastle()->getTower(getRegion())->damage((float)K / (float)Distance*firePower);
	}
}

void Shielded::updateEnemy(Battle *b)
{
	double Term1 = (firePower / Distance)* (b->getC1());
	double Term2 = (b->getC2()) / (getRemainingTime(b->getCurrentTime())+1);
	double Term3 = health*(b->getC3());
	Priority = (Term1 + Term2 + Term3);
}


int Shielded::getRemainingTime(int CT )
{
	int RT;
	if ((CT - arrivalTime) % (reload + 1) == 0)
		RT = 0;
	else
		RT = (reload + 1)-(CT - arrivalTime) % (reload + 1);
	return RT;
}

double Shielded::getPriority()
{
	return Priority;
}

Shielded::~Shielded()
{
}

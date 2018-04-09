#include "Tower.h"


void Tower::setHealth(double h)
{
	if(h > 0)
		health = h;
	else
		health = 0; // killed
}

double Tower::getHealth() const
{
	return health;
}

int Tower::getFirePower()const
{
	return firePower;
}
int Tower::getMaxNum()const
{
	return N;
}
void Tower::setNum(int rn)
{
	N=(rn > 0) ? rn: 5;//assuming default number is 5
}


void Tower::setFirePower(int fp)
{
	firePower = (fp>0)?fp:10;//assuming the default fire power is 10
}

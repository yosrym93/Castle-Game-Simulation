#include "Tower.h"
#include "..\Battle.h"
Tower::Tower()
{
	isKilled = false;
	canAttack = true;
}

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
void Tower::attack(Battle*b,int region)
{
	if (!isKilled)
	{
		ActiveEnemies* normal = b->getNormalEnemies();
		ActiveEnemies* tank = b->getFreezeTankEnemies();
		ShieldedEnemies* shielded = b->getShieldedEnemies();
		int num = N;
		tank[region].towerAttack(this, num);
		num -= tank[region].getCount();
		if (num > 0)
		{
			shielded[region].towerAttack(this, num);
			num -= shielded[region].getCount();
		}
		if (num > 0)
			normal[region].towerAttack(this, num);
	}
}
void Tower::attackEnemy(Enemy*enemy)
{
	double t1 = (1.0 / enemy->getDistance());
	double damage = t1*firePower*(1 / enemy->getK());
	enemy->damage(damage);
}
void Tower::damage(double x)
{
	if (!isKilled)
		health = health - x;

	if (health <= 0)
	{
		health = 0;
		isKilled = true;
	}
}
void Tower::testKill()
{
	health = 0;
	isKilled = true;
}
bool Tower::isDestroyed() const
{
	return isKilled;
}
bool Tower::getCanAttack(int currentTime) const
{
	if (currentTime == freezeTime)
		return false;
	return true;
}
void Tower::freeze(int x)
{
	freezeTime = x;
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

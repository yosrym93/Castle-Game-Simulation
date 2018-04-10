#include "Enemy.h"


Enemy::Enemy(color r_c, REGION r_region, int d)
{
	Clr = r_c;
	Region = r_region;
	SetDistance(d);
}

string Enemy::print()
{
	string printInfo;
	string type=getTypeStr();
	printInfo =  "( "+ type +" ,"+to_string(id) +" ,"+ to_string((int)health)+" ,"+ to_string(arrivalTime) +" ," +to_string((int)firePower) +" ,"+ to_string(reload)+" )";
	return printInfo;
}
Enemy::~Enemy()
{
} 

color Enemy::getColor() const
{
	return Clr;
}

REGION Enemy::getRegion() const
{
	return Region;
}

void Enemy::decrementDist()
{
	if (Distance > MinDistance)
		Distance--;
}
void Enemy::setId(int rid)
{
	id = rid;
}

int Enemy::getId() const
{
	return id;
}

void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;

}

int Enemy::getDistance() const
{
	return Distance;
}

double Enemy::getHealth() const
{
	return health;
}

void Enemy::setArrTime(int rtime)
{
	arrivalTime = (rtime >= 0) ? rtime : 1; //assuming 1 is the default
}

int Enemy::getArrTime()
{
	return arrivalTime;
}

void Enemy::setHealth(double rhealth)
{
	health = (rhealth >= 0) ? rhealth : 10;//assuming 10 is the default
}

void Enemy::setPow(int rpow)
{
	firePower = (rpow > 0) ? rpow : 10;//assuming that the default is 10
}

void Enemy::setRld(int rld)
{
	reload = (rld > 0) ? rld : 10;//assuming 10 is the default
}
//return the type as a string
string Enemy::getTypeStr () const
{
	switch (type)
	{
	case paver:
		return "Paver";
		break;
	case fighter:
		return "Fighter";
		break;
	case shielded:
		return "Shielded fighter";
		break;
	case tank:
		return "Tank";
		break;
	case balloon:
		return "Balloon";
		break;
	default:
		return"";
	}
}

void Enemy::setType(int rtype)
{
	switch (rtype)
	{
	case 0:
		type = paver;
		break;
	case 1:
		type = fighter;
		break;
	case 2:
		type = shielded;
		break;
	case 3:
		type = balloon;
		break;
	case 4:
		type = tank;
		break;
	default:
		break;
	}
}

bool Enemy::isKilled() {
	if (health == 0)
		return true;
	return false;
}
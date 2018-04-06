#include "Enemy.h"


Enemy::Enemy(color r_c, REGION r_region, int d)
{
	Clr = r_c;
	Region = r_region;
	setDistance(d);
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

void Enemy::setDistance(int d)
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

int Enemy::getArrivalTime() const {
	return ArrivalTime;
}
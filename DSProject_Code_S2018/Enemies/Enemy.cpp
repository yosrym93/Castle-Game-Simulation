#include "Enemy.h"
#include"..\Battle.h"
#include<cmath>

REGION Enemy::enuminizeRegion(int cRegion)
{
	REGION r;
	switch (cRegion)
	{
	case 0:
		r = A_REG;
		break;
	case 1:
		r = B_REG;
		break;
	case 2:
		r = C_REG;
		break;
	case 3:
		r = D_REG;
		break;
	default:
		r = A_REG;//default (this case should never happen)
		break;

	}
	return r;
}

Enemy::Enemy(color r_c, REGION r_region, int d)
{
	Clr = r_c;
	Region = r_region;
	oRegion = r_region;
	SetDistance(d);
	
	speed = 1;
	killed = false;
}

string Enemy::print()
{
	string printInfo;
	string type=getTypeStr();
	printInfo =  "( "+ type +" ,"+to_string(id) +" ,"+ to_string((int)health)+" ,"+ to_string(arrivalTime) +" ," +to_string((int)firePower) +" ,"+ to_string(reload)+" )";
	return printInfo;
}
void Enemy::heal(int*A)
{
	if (Distance > A[0] - A[1] && Distance < A[0] + A[1])
	{
		health = health + ((A[1]-abs(Distance-A[0]))/100.0)*maxHealth;
		if (health > maxHealth)
			health = maxHealth;
	}
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
void Enemy::move(Battle * B)
{
	int unp = B->getUnpavedDist(getRegion());
	
		if ((Distance - speed) > unp)
			for (int i = 0; i < speed;i++)
				decrementDist();
		else Distance = unp;


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
	maxHealth = health;
}

void Enemy::setPow(int rpow)
{
	firePower = (rpow > 0) ? rpow : 10;//assuming that the default is 10
}

void Enemy::setCRegion(int reg)
{
	if (reg >= 0 && reg < NoOfRegions)
		Region = enuminizeRegion(reg);
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
void Enemy::damage(double rdamage)
{
	if (!isKilled())
		health = health - rdamage;

	if (health <= 0)
	{
		health = 0;
		killed = true;
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

void Enemy::setSpeed(int spd)
{
	if (spd > 0)
		speed = spd;
	else speed = 1;
}

bool Enemy::isKilled() {
	if (health == 0)
		return true;
	return false;
}

bool Enemy::canAttack(int x)
{
	if (x >= arrivalTime && !isKilled() && ((x - arrivalTime) % (reload + 1) == 0))
		return true;
	else 
		return false;
}

int Enemy::getK()
{
	return K;
}
/***************Virtual FN.s**********************/
void Enemy::Attack(Battle *b)
{

}
void Enemy::updateEnemy(Battle* b)
{

}
double Enemy::getPriority()
{
	return 0;//only shielded enemies have priority
}
/****************************************/ 

//Calculates the firstShotDelay (Parameter is firstShot time step)
void Enemy::calcFD(int firstShotTime) {
	if (firstShotTime >= arrivalTime)	//Checks for valid first-shot time
		firstShotDelay = firstShotTime - arrivalTime;
	else
		firstShotDelay = -1;			//-1 indicates wrong first-shot time
}

//Calculates the killDelay (Parameter is kill time step)
void Enemy::calcKD(int killTime) {
	int firstShotTime = arrivalTime + firstShotDelay;
	if (killTime >= firstShotTime)	//Checks for valid kill time
		killDelay = killTime - firstShotTime;
	else
		killDelay = -1;				//-1 indicates wrong kill time
}

//Returns the firstShotDelay
double Enemy::getFD() {
	return firstShotDelay;
}

//Returns the killDelay
int Enemy::getKD() {
	return killDelay;
}

double Enemy::getMaxHealth() const
{
	return maxHealth;
}

double Enemy::getFirePower() const
{
	return firePower;
}

/***********************Output Functions ***************************/
void Enemy::output() const {
	
}
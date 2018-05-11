#include "Castle.h"
#include <string>
#include "..\GUI\GUI.h"

Castle::Castle()
{
}

string Castle::print(int p)
{
	string printInfo;
	double ihealth = int(round(towers[p].getHealth() * 100)) / 100.0;
	string health = to_string(ihealth);
	printInfo =  "TowerHealth(" + health +")";
	return printInfo;
}

void Castle::setTowersHealth(double h)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		towers[i].setHealth(h);
	}
}
void Castle::towersAttack(Battle*b, int currTime)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		towers[i].attack(b,i, currTime);
	}
}
void Castle::setTowersNum(int n)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		towers[i].setNum(n);
	}
}
Tower * Castle::getTower(int x)
{
	return &towers[x];
}
void Castle::testKill(int i)
{
	towers[i].damage(10000);
}
void Castle::setTowersFirePower(int pow)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		towers[i].setFirePower(pow);
	}
}

bool Castle::isDestroyed() {
	bool destroyed = true;
	for (int i = 0; i < NoOfRegions; i++) {
		destroyed = destroyed && towers[i].isDestroyed();
	}

	return destroyed;
}

bool Castle::isDestroyed(int i)
{
	if (i >= 0 && i < NoOfRegions)
		return towers[i].isDestroyed();
	return false;
}

#include "Castle.h"
#include <string>
#include "..\GUI\GUI.h"

Castle::Castle()
{
}

string Castle::print(int p)
{
	string printInfo;
	string health = to_string((int)towers[p].getHealth());
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
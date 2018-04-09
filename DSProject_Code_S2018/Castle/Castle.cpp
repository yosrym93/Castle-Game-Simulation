#include "Castle.h"
#include <string>
#include "..\GUI\GUI.h"

Castle::Castle()
{
}

string Castle::print(int p)
{
	string printInfo;
	string health = to_string(towers[p].getHealth());
	string fP = to_string(towers[p].getFirePower());
	string maxNum = to_string(towers[p].getMaxNum());
	printInfo =  "TowerInfo(" + health + " , " + fP + "," + maxNum+" )";
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
void Castle::setTowersFirePower(int pow)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		towers[i].setFirePower(pow);
	}
}
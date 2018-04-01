#include "Castle.h"

#include "..\GUI\GUI.h"

Castle::Castle()
{
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
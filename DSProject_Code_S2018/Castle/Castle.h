#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"

#include "Tower.h"

class Castle
{
	Tower towers[NoOfRegions];

	
public:
	Castle();
	void towersAttack(Battle*);
	string print(int);
	void setTowersHealth(double h);
	void testKill(int);		//tests killing a tower
	void setTowersFirePower(int pow);
	void setTowersNum(int n);
	Tower* getTower(int);
	bool isDestroyed();			//Returns true if all towers all destroyed
	bool isDestroyed(int);		//Returns true if a specific tower is destroyed
};

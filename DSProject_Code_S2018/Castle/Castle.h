#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"

#include "Tower.h"

class Castle
{
	Tower towers[NoOfRegions];
	//
	// TODO: Add More Data Members As Needed
	//
	
public:

	Castle();
	string print(int);
	void setTowersHealth(double h);
	void setTowersFirePower(int pow);
	void setTowersNum(int n);
	Tower* getTower(int);
	//
	// TODO: Add More Member Functions As Needed
	//
};

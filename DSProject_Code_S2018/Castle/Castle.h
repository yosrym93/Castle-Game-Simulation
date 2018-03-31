#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"

#include "Tower.h"

class Castle
{
	Tower Towers[NoOfRegions];
	int Unpaved[4]; // unpaved distance of each region
	//
	// TODO: Add More Data Members As Needed
	//
	
public:

	Castle();
	void SetTowersHealth(double h);

	//
	// TODO: Add More Member Functions As Needed
	//
};

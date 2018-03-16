#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

// Enemy is the base class of each type of enemy
// Enemy is an abstract class.
class Enemy
{

protected:
	int ID;         //Each enemy has a unique ID (sequence number)
	color Clr;	    //Color of the enemy (will be set depending on the enemy type: Paver, ...etc.)
	REGION Region;  //Region of this enemy
	int Distance;	//Horizontal distance between enemy & the tower of its region
	                //Always positive (ranges from 2 to 60)
	double Health;	//Enemy health
	
	//
	// TODO: Add More Data Members As Needed
	//

public:
	Enemy(color r_c, REGION r_region, int d = MaxDistance);
	virtual ~Enemy();

	color GetColor() const;
	REGION GetRegion() const;

	void DecrementDist();

	void SetDistance(int d);
	int GetDistance() const;

	// Virtual Functions: ----------------

	//virtual void Move() = 0;	    //All enemies can move
	//virtual void Attack() = 0;	//All enemies can attack (attacking is paving or shooting)

	//
	// TODO: Add More Member Functions As Needed
	//

};


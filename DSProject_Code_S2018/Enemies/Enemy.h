#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

// Enemy is the base class of each type of enemy
// Enemy is an abstract class.
class Enemy
{

protected:
	int id;         //Each enemy has a unique ID (sequence number)
	color Clr;	    //Color of the enemy (will be set depending on the enemy type: Paver, ...etc.)
	REGION Region;  //Region of this enemy
	int Distance;	//Horizontal distance between enemy & the tower of its region
	                //Always positive (ranges from 2 to 60)
	double health;	//Enemy health
	bool canAttack;
	int K;
	int arrivalTime;
	int reload;
	TYPE type;
	double firePower;
	int deathTime;
	int firstShot;
	
	//
	// TODO: Add More Data Members As Needed
	//

public:
	Enemy(color r_c, REGION r_region, int d = MaxDistance);
	virtual ~Enemy();

	color getColor() const;
	REGION getRegion() const;
	void decrementDist();
	//setters and getters 
	void setId(int);
	int getId() const;
	void SetDistance(int d);
	void setArrTime(int);
	int getArrTime();
	void setHealth(double);
	void setPow(int);
	void setRld(int);
	void setType(int);
	int getDistance() const;
	double getHealth()const;
	// Virtual Functions: ----------------

	//virtual void Move() = 0;	    //All enemies can move
	//virtual void Attack() = 0;	//All enemies can attack (attacking is paving or shooting)

	//
	// TODO: Add More Member Functions As Needed
	//

};


#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
// Enemy is the base class of each type of enemy
// Enemy is an abstract class.
class Battle;
class Enemy
{

protected:
	int id;         //Each enemy has a unique ID (sequence number)
	color Clr;	    //Color of the enemy (will be set depending on the enemy type: Paver, ...etc.)
	REGION Region;  //Region of this enemy
	int Distance;	//Horizontal distance between enemy & the tower of its region
	                //Always positive (ranges from 2 to 60)
	int speed;		//How many distance units could be covered per time step
	double health;	//Enemy health
	double maxHealth;  //health of enemy before being attacked
	//bool canAttack;
	int K;
	int arrivalTime;
	int reload;
	TYPE type;
	double firePower;

	int firstShotDelay;	//T(first_shot) - T(arrival)
	int killDelay;		//T(enemy_killed) - T(first_shot)

public:
	Enemy(color r_c, REGION r_region, int d = MaxDistance);
	virtual ~Enemy();

	color getColor() const;
	REGION getRegion() const;
	void decrementDist();
	void move(Battle* B);
	string print();
	void heal();	//increases enemy health by 5% of initial health during balloon attack time
	//Setters and getters 
	void setId(int);
	int getId() const;
	void SetDistance(int d);
	void setArrTime(int);
	int getArrTime();
	void setHealth(double);
	void setPow(int);
	void setRld(int);
	void setType(int);
	void setSpeed(int);
	int getDistance() const;
	double getHealth()const;
	string getTypeStr() const; //Returns the type as a string (for printing)
	bool isKilled();
	bool canAttack(int);
	void calcFD(int firstShotTime);	//Calculates the firstShotDelay (Parameter is firstShot time step)
	void calcKD(int killTime);		//Calculates the killDelay (Parameter is kill time step)
	int getFD();					//Returns the firstShotDelay
	int getKD();					//Return the killDelay
	double getMaxHealth()const;		//Returns Maximum health
	double getFirePower()const;
	/****************Output Functions*****************/
	void output() const;

	// Virtual Functions: ----------------

	//virtual void Move() = 0;	    //All enemies can move
	virtual void Attack(Battle*) = 0;	//All enemies can attack (attacking is paving or shooting)



};


#pragma once
#include "../Enemies/Enemy.h"
class Battle;
class Tower
{
	double health;
	int N; // max number of elements tower can attack in time step
	double firePower;
	bool isKilled;
	bool canAttack;
	int currentTime;
	int freezeTime;		//attack time of freeze tank

public:
	Tower();
	//setter and getters..
	void setHealth(double h);
	double getHealth() const;
	void setNum(int );
	void setFirePower(int );
	int getMaxNum()const;
	int getFirePower()const;
	//---------------------------------------------------------------------------------
	void damage(double);				//decrease tower health
	bool isDestroyed()const;			//returns true when tower is completely damaged
	bool getCanAttack(int)const;		//returns false during freezeTank attack time - USE CURRENT TIME AS A PARAMETER
	void freeze(int);					//freeze the tower during freezeTank attack time 
	void attack(Battle*,int reg, int currTime);			//attack of the tower
	void attackEnemy(Enemy*);			//attack the enemy
};


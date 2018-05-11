#pragma once
#include "Enemy.h"
class Battle;
class Shielded :
	public Enemy
{
	double Priority;
public:
	Shielded(color r_c, REGION r_region, int d);
	void Attack(Battle*);
	void updateEnemy(Battle*);
	//bool operator>(Enemy*);
	int getRemainingTime(int );
	double getPriority();						//priority in negative for further implementations
	~Shielded();
};


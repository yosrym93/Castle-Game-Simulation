#pragma once
#include "Enemies\Enemy.h"
#include "Array.h"
#include "Array.cpp"
#include "Battle.h"
class ShieldedEnemies
{
	Array<Enemy> ShieldedArray;
public:
	ShieldedEnemies();
	int getCount() const;
	void addEnemy(Enemy* newEnemy);
	void clear();
	bool killRand();				//for phase 1: picks a random enemy and sets its health to zero.
	bool isEmpty();
	void update();					//Updates enemies in the active list (removes the killed enemies)
	~ShieldedEnemies();
	string print();
};


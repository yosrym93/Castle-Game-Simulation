#pragma once
#include "..\Enemies\Enemy.h"
#include "..\ADTs\Array.h"


class Battle;

class ShieldedEnemies
{
	Array<Enemy> ShieldedArray;
public:
	ShieldedEnemies();
	int getCount() const;
	void addEnemy(Enemy* newEnemy);
	void clear();
	bool killRand();			//for phase 1: picks a random enemy and sets its health to zero.
	bool isEmpty();
	void removeKilled(Battle &);		//Removes killed enemies from the list and calls Battles' killEnemy(killedEnemy)
	~ShieldedEnemies();
	string print();
};


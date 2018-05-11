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
	void importOther(ShieldedEnemies&);	//Moves enemies from one region to another	
	void removeKilled(Battle &);		//Removes killed enemies from the list and calls Battles' killEnemy(killedEnemy)
	~ShieldedEnemies();
	string print();
	void traverseToAttack(Battle*);			//traverse the list to call attack for each enemy
	void traverseToMove(Battle*);			//traverse the list to call move for each enemy
	void traverseToHeal(int*);					//traverse the list to call heal for each enemy
	void traverseToTravel(int);				//traverse the list to change region for each enemy
};


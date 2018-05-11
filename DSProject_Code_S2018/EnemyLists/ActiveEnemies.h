#pragma once

#include "../Enemies/Enemy.h"
#include "../ADTs/List.h"
#include "../Castle/Tower.h"
class Battle;

class ActiveEnemies 
{
	List<Enemy*> enemiesList;
public:
	ActiveEnemies();
	void addEnemy(Enemy* newEnemy);
	bool killRand();						//for phase 1: picks a random enemy and sets its health to zero.
	int getCount() const;
	bool isEmpty() const;
	void clear();
	void importOther(ActiveEnemies&);	//Moves enemies from one region to another	
	void removeKilled(Battle &);	//Removes killed enemies from the list and calls Battles' killEnemy(killedEnemy)
	string print();
	~ActiveEnemies();
	void traverseToAttack(Battle*);			//traverse the list to call attack for each enemy
	void traverseToMove(Battle*);			//traverse the list to call move for each enemy
	void traverseToHeal();					//traverse the list to call heal for each enemy
	void towerAttack(Tower*,int);		//traverse the list to attack the enemies by the tower
};



/*
void doNothing(Enemy*) {};
void doNothingForAll() {
ActiveEnemies a;
enemiesList.traverse(&ActiveEnemies::doNothing, a);
}*/
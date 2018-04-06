#pragma once

#include "../Enemies/Enemy.h"
#include "List.h"

class ActiveEnemies 
{
	List<Enemy*> enemiesList;
public:
	ActiveEnemies();
	void addEnemy(Enemy* newEnemy);
	Enemy* pickRand();				//for phase 1: picks a random enemy, return null if there is no enemies
	int getCount() const;
	bool isEmpty() const;
	void clear();
	
	~ActiveEnemies();
};



/*
void doNothing(Enemy*) {};
void doNothingForAll() {
ActiveEnemies a;
enemiesList.traverse(&ActiveEnemies::doNothing, a);
}*/
#pragma once

#include "../Enemies/Enemy.h"
#include "List.h"

class ActiveEnemies 
{
	List<Enemy*> enemiesList;
public:
	ActiveEnemies();
	void addEnemy(Enemy* newEnemy);
	void pickRand();				//for phase 1: picks a random enemy and sets its health to zero.
	int getCount() const;
	bool isEmpty() const;
	void clear();
	void update();
	~ActiveEnemies();
};



/*
void doNothing(Enemy*) {};
void doNothingForAll() {
ActiveEnemies a;
enemiesList.traverse(&ActiveEnemies::doNothing, a);
}*/
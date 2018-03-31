#pragma once
#include "Queue.h"
#include "../Enemies/Enemy.h"

class InactiveEnemies
{
	Queue<Enemy*> enemiesQueue;
public:
	InactiveEnemies();
	void addEnemy(Enemy* newEnemy);
	//void activateEnemies(int);
	void clear();
	~InactiveEnemies();
};


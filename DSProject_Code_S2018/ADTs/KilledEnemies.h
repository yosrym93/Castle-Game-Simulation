#pragma once

#include "Queue.h"
#include "../Enemies/Enemy.h"

class KilledEnemies
{
	Queue<Enemy*> enemiesQueue;
public:
	KilledEnemies();
	void addEnemy(Enemy* newEnemy);
	void clear();
	~KilledEnemies();
};
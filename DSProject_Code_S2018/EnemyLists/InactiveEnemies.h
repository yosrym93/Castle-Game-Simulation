#pragma once
#include "../ADTs/Queue.h"
#include "../Enemies/Enemy.h"

class Battle;

class InactiveEnemies
{
	Queue<Enemy*> enemiesQueue;
public:
	InactiveEnemies();
	void addEnemy(Enemy* newEnemy);
	int getCount() const;
	void activateEnemies(Battle& B);		//activates enemies according to their arrival time
	bool isEmpty() const;
	void clear();
	~InactiveEnemies();
};


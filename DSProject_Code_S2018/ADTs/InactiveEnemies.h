#pragma once
#include "Queue.h"
#include "../Enemies/Enemy.h"

class InactiveEnemies : public Queue<Enemy*>
{
public:
	InactiveEnemies();
	void activateEnemies(int);
	~InactiveEnemies();
};


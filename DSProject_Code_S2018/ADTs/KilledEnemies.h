#pragma once

#include "Queue.h"
#include "../Enemies/Enemy.h"

class KilledEnemies : public Queue<Enemy*>
{
public:
	KilledEnemies();
	~KilledEnemies();
};
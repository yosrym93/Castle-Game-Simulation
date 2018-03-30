#pragma once

#include "Queue.h"
#include "../Enemies/Enemy.h"

class ActiveEnemies : public Queue<Enemy*>
{
public:
	ActiveEnemies();
	~ActiveEnemies();
};
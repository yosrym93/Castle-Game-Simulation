
#pragma once
#include "Enemies\Enemy.h"
#include "Array.h"
#include "Array.cpp"
class ShieldedEnemies
{
	Array<Enemy> ShieldedArray;
public:
	ShieldedEnemies();
	void addEnemy(Enemy* newEnemy);
	void clear();


	~ShieldedEnemies();
};


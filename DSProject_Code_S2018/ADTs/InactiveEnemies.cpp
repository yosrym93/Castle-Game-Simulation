#include "InactiveEnemies.h"


InactiveEnemies::InactiveEnemies()
{
}

void InactiveEnemies::addEnemy(Enemy* newEnemy) {
	enemiesQueue.enqueue(newEnemy);
}

void InactiveEnemies::clear() {
	enemiesQueue.clear();
}

InactiveEnemies::~InactiveEnemies()
{
}


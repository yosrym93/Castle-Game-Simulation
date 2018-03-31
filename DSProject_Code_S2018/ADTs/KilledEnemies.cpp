#include "KilledEnemies.h"



KilledEnemies::KilledEnemies()
{
}

void KilledEnemies::addEnemy(Enemy* newEnemy) {
	enemiesQueue.enqueue(newEnemy);
}

void KilledEnemies::clear() {
	enemiesQueue.clear();
}

KilledEnemies::~KilledEnemies()
{
}

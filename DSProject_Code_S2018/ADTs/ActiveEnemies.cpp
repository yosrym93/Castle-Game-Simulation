#include "ActiveEnemies.h"



ActiveEnemies::ActiveEnemies()
{
}

void ActiveEnemies::addEnemy(Enemy* newEnemy) {
	enemiesList.push(newEnemy);
}

Enemy* ActiveEnemies::pickRand() {
	return enemiesList.pickRand();
}

int ActiveEnemies::getCount() const {
	return enemiesList.getCount();
}

bool ActiveEnemies::isEmpty() const {
	return enemiesList.isEmpty();
}

void ActiveEnemies::clear() {
	enemiesList.clear();
}

ActiveEnemies::~ActiveEnemies()
{
}

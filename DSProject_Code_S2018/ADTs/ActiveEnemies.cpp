#include "ActiveEnemies.h"



ActiveEnemies::ActiveEnemies()
{
}

void ActiveEnemies::addEnemy(Enemy* newEnemy) {
	enemiesList.push(newEnemy);
}
void ActiveEnemies::pickRand() {
	 enemiesList.pickRand();
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

void ActiveEnemies::update()
{
	enemiesList.update();
}

ActiveEnemies::~ActiveEnemies()
{
}

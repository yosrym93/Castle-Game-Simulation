#include "ActiveEnemies.h"



ActiveEnemies::ActiveEnemies()
{
}

void ActiveEnemies::addEnemy(Enemy* newEnemy) {
	enemiesList.push(newEnemy);
}

void ActiveEnemies::clear() {
	enemiesList.clear();
}

ActiveEnemies::~ActiveEnemies()
{
}

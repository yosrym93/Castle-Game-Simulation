#include "ActiveEnemies.h"



ActiveEnemies::ActiveEnemies()
{
}

void ActiveEnemies::addEnemy(Enemy* newEnemy) {
	enemiesList.push(newEnemy);
}

bool ActiveEnemies::killRand() {
	if (enemiesList.isEmpty())
		return false;

	Enemy* randomEnemy = enemiesList.pickRand();
	randomEnemy->setHealth(0);		//kills the enemy
	return true;
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
	enemiesList.condtionalRemove(&Enemy::isKilled);
}

string ActiveEnemies::print()
{
	int size = enemiesList.getCount();
	Enemy* enemy;
	string print;
	for (int i = 0; i < size; i++)
	{
		enemy =  enemiesList.get(i);
		if(i!=0)
		print = print +", "+ enemy->print();
		else print = enemy->print();
	}
	return print;
}

ActiveEnemies::~ActiveEnemies()
{
}

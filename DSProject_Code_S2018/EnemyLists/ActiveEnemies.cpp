#include "ActiveEnemies.h"
#include "..\Battle.h"


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

//Removes killed enemies from the list and calls Battles' killEnemy(killedEnemy)
void ActiveEnemies::removeKilled(Battle &b)
{
	enemiesList.condtionalRemove(&Battle::isKilledEnemy, b);
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

void ActiveEnemies::traverseToAttack(Battle* b)
{
	enemiesList.traverse(&Enemy::Attack , b);
}

void ActiveEnemies::traverseToHeal()
{
	enemiesList.traverse(&Enemy::heal);
}

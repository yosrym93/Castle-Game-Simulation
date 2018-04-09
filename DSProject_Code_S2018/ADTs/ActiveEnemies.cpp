#include "ActiveEnemies.h"



ActiveEnemies::ActiveEnemies()
{
}

void ActiveEnemies::addEnemy(Enemy* newEnemy) {
	enemiesList.push(newEnemy);
}
bool ActiveEnemies::pickRand() {
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

void ActiveEnemies::update()
{
	enemiesList.update();
}

string ActiveEnemies::print()
{
	int size = enemiesList.getCount();
	Enemy* enemy;
	string print;
	for (int i = 0; i < size; i++)
	{
		enemy =  enemiesList.get(i);
		print = print +" ,"+ enemy->print();
	}
	return print;
}

ActiveEnemies::~ActiveEnemies()
{
}

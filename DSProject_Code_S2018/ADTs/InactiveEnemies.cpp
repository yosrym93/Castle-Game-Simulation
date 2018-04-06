#include "InactiveEnemies.h"
#include "../Battle.h"


InactiveEnemies::InactiveEnemies()
{
}

void InactiveEnemies::addEnemy(Enemy* newEnemy) {
	enemiesQueue.enqueue(newEnemy);
}

//activates enemies according to their arrival time
void InactiveEnemies::activateEnemies(Battle& B) {
	if (enemiesQueue.isEmpty())
		return;
	int currTime = B.getCurrentTime();
	Enemy* topEnemy = enemiesQueue.peek();
	while (topEnemy->getArrivalTime() <= currTime) {
		B.activateEnemy(enemiesQueue.dequeue());
		if (enemiesQueue.isEmpty())
			return;
		topEnemy = enemiesQueue.peek();
	}
}

int InactiveEnemies::getCount() const {
	return enemiesQueue.getCount();
}

bool InactiveEnemies::isEmpty() const {
	return enemiesQueue.isEmpty();
}

void InactiveEnemies::clear() {
	enemiesQueue.clear();
}

InactiveEnemies::~InactiveEnemies()
{
}


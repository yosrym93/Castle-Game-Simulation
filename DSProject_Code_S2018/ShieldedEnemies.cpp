#include "ShieldedEnemies.h"
ShieldedEnemies::ShieldedEnemies()
{
}

void ShieldedEnemies::addEnemy(Enemy * newEnemy)
{
	ShieldedArray.insert(newEnemy);
}

void ShieldedEnemies::clear()
{
	ShieldedArray.clear();
}


ShieldedEnemies::~ShieldedEnemies()
{
}

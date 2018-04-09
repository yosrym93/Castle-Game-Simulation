#include "ShieldedEnemies.h"
ShieldedEnemies::ShieldedEnemies()
{
}

void ShieldedEnemies::addEnemy(Enemy * newEnemy)
{
	ShieldedArray.insert(newEnemy);
}
int ShieldedEnemies::getCount() const
{
	return ShieldedArray.getCount();
}
 void ShieldedEnemies::pickRand()
	{
	 ShieldedArray.pickRand();
	}
 bool ShieldedEnemies::isEmpty()
 {
	 return ShieldedArray.isEmpty();
 }
 void ShieldedEnemies::clear()
{
	ShieldedArray.clear();
}
 void ShieldedEnemies::update()
 {
	 ShieldedArray.update();
 }

ShieldedEnemies::~ShieldedEnemies()
{
}

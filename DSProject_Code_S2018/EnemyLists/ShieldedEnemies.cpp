#include "ShieldedEnemies.h"
#include "..\Battle.h"

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

bool ShieldedEnemies::killRand()
{
	if (ShieldedArray.isEmpty())
		return false;

	Enemy* randomEnemy = ShieldedArray.pickRand();
	randomEnemy->setHealth(0);		//kills the enemy
	return true;
}

 bool ShieldedEnemies::isEmpty()
 {
	 return ShieldedArray.isEmpty();
 }
 void ShieldedEnemies::importOther(ShieldedEnemies &other)
 {
	 ShieldedArray.importOther(other.ShieldedArray);
 }
 void ShieldedEnemies::clear()
{
	ShieldedArray.clear();
}
 //Removes killed enemies from the list and calls Battles' killEnemy(killedEnemy)
 void ShieldedEnemies::removeKilled(Battle &b)
 {
	 ShieldedArray.condtionalRemove(&Battle::isKilledEnemy, b);
 }

string ShieldedEnemies::print()
 {
	 
	 int size = ShieldedArray.getCount();
	 Enemy* enemy;
	 string print;
	 for (int i = 0; i < size; i++)
	 {
		 enemy = ShieldedArray.get(i);
		 if (i != 0)
			 print = print + ", " + enemy->print();
		 else print = enemy->print();
	 }
	 return print;
 }
void ShieldedEnemies::calcPriority(Battle *b)
{
	ShieldedArray.traverse(&Enemy::updateEnemy,b);
}
void ShieldedEnemies::towerAttack(Tower*tower, int num)
{
	ShieldedArray.sort(&Enemy::getPriority);
	ShieldedArray.traverse(&Tower::attackEnemy, *tower, num);
}
void ShieldedEnemies::enemiesAttack(Battle *b)
{
	ShieldedArray.traverse(&Enemy::Attack, b);
}
void ShieldedEnemies::enemiesMove(Battle *b)
{
	ShieldedArray.traverse(&Enemy::move, b);
}
void ShieldedEnemies::enemiesHeal(int*A)
{
	ShieldedArray.traverse(&Enemy::heal , A);
}
void ShieldedEnemies::enemiesTravel(int n, int d)
{
	ShieldedArray.traverse(&Enemy::setCRegion, n);
	ShieldedArray.traverse(&Enemy::setNDistance, d);
}
ShieldedEnemies::~ShieldedEnemies()
{
}

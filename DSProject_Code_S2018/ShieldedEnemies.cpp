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
bool ShieldedEnemies::pickRand()
{
	 return ShieldedArray.pickRand();
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

string ShieldedEnemies::print()
 {
	 
	 int size = ShieldedArray.getCount();
	 Enemy* enemy;
	 string print;
	 for (int i = 0; i < size; i++)
	 {
		 enemy = & ShieldedArray.get(i);
		 print = print + " ," + enemy->print();
	 }
	 return print;
 }
ShieldedEnemies::~ShieldedEnemies()
{
}

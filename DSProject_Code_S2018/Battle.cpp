#include "Battle.h"


Battle::Battle()
{
	EnemyCount = 0;
}

void Battle::AddEnemy(Enemy* Ptr)
{
	if (EnemyCount < MaxEnemyCount) 
		BEnemiesForDraw[EnemyCount++] = Ptr;

	// Note that this function doesn't allocate any enemy objects
	// It only makes the first free pointer in the array
	// points to what is pointed to by the passed pointer Ptr
}

void Battle::DrawEnemies(GUI * pGUI)
{
	pGUI->DrawEnemies(BEnemiesForDraw, EnemyCount);
}

Castle * Battle::GetCastle()
{
	return &BCastle;
}

int Battle::getCurrentTime() const {
	return currentTime;
}


/****************************  Inactive Enemies Functions  ****************************/
void Battle::activateEnemy(Enemy* inactiveEnemy) {
	Enemy* fighter = dynamic_cast<Fighter*>(inactiveEnemy);
	if (fighter) {
		normalEnemies.addEnemy(fighter);
		return;
	}

	Enemy* paver = dynamic_cast<Paver*>(inactiveEnemy);
	if (paver) {
		normalEnemies.addEnemy(paver);
		return;
	}

	Enemy* balloon = dynamic_cast<Balloon*>(inactiveEnemy);
	if (balloon) {
		normalEnemies.addEnemy(balloon);
		return;
	}

	Enemy* tank = dynamic_cast<Tank*>(inactiveEnemy);
	if (tank) {
		tankEnemies.addEnemy(tank);
		return;
	}

	Enemy* shieldedFighter = dynamic_cast<Shielded*>(inactiveEnemy);
	if (shieldedFighter) {
		//shieldedEnemies.addEnemy(shieldedFighter);
		return;
	}
}
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
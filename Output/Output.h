#pragma once
#include "..\ADTs\Array.h"
#include "..\Enemies\Enemy.h"

class Battle;

class Output
{
	Array<Enemy> enemiesList;		//Enemies killed in one time step
	int sumFD, sumKD;				//total FirstShotDelay, KillDelay
	double towerStartingHealth;		//Towers starting health
	int nKilled;					//Total number of killed enemies
	int nEnemies;					//Total number of all enemies (active, killed & inacive)
public:
	Output();
	void addEnemy(Enemy*);	//adds an enemy to the enemiesToOutput list
	void writeEnemy(Enemy* , int currentTime);		//outputs an enemy's data
	void writeEnemies(Battle &b);		//writes enemies in the enemeisToOutput list, then deletes them
	void writeGameStatus(Battle &b);	//writes final statistics and game status

	void setTotalEnemies(int);
	void setTowerStartingHealth(double);

	void reset();
	~Output();
};


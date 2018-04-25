#pragma once
#include <fstream>

#include "Enemies\Enemy.h"
#include "Enemies\Fighter.h"
#include "Enemies\Balloon.h"
#include "Enemies\Paver.h"
#include "Enemies\Shielded.h"
#include "Enemies\Tank.h"

#include "Castle\Castle.h"
#include "Castle\Tower.h"

#include "ADTs\ActiveEnemies.h"
#include "ADTs\InactiveEnemies.h"
#include "ShieldedEnemies.h"


// it is the controller of the project
class Battle
{
private:
	Castle bCastle;
	int enemyCount;									 //the actual number of enemies in the game
	double c1, c2, c3;							     // input constants for priority equation
	int currentTime;
	int Unpaved[NoOfRegions];						 // unpaved distance of each region
	int killed[NoOfRegions];				//number of killed enemies in each region
	MenuItem mode;

	/************************Inactive Enemies List(s)************************/
	InactiveEnemies inactiveEnemies;				//all inactive enemies

	/************************Active Enemies List(s)************************/
	ActiveEnemies normalEnemies[NoOfRegions];		//pavers, fighters and balloons
	ShieldedEnemies shieldedEnemies[NoOfRegions];	//shielded fighters
	ActiveEnemies tankEnemies[NoOfRegions];			//tanks
	
	/************************ GUI Array ************************/
	Enemy * bEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
								  			

public:
	
	Battle();
	void AddEnemy(Enemy* Ptr);		//Adds an enemy to the GUI array
	void DrawEnemies(GUI * pGUI);	//Draws enemies in the GUI array
	Castle * GetCastle();
	void killRandom();				//Kills enemieas randomly according to phase 1.
	void update(int);					//Updates all lists and the GUI array
	int getCurrentTime() const;	
	int getTotalAlive();			//Gets the number of alive enemies at any moment.
	void print();					//Prints data for phase 1.
	void Load(GUI*);				//Load all enemies to the inactive list
	bool isFighting();				//are there still ENEMIES ALIVE????!!
	REGION getRegion(char);			//converting char type into enum type
	char getRegion(int);			//converting enum type into char type
	void print(GUI*);				//print towers,active and inactive enemies info.
	void timeCounter();
	void interactiveTime();
	void stepByStepTime();
	void silentTime();
	
	/****************************  Inactive Enemies Functions  ****************************/
	void activateEnemy(Enemy* inactiveEnemy);

};


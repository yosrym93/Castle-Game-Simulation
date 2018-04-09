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
#include "Enemies\Paver.h"
#include "Enemies\Fighter.h"
#include "Enemies/Shielded.h"
#include "Enemies\Balloon.h"
#include "Enemies\Tank.h"
#include "ADTs\ActiveEnemies.h"
#include "ADTs\InactiveEnemies.h"
#include "ShieldedEnemies.h"


// it is the controller of the project
class Battle
{
private:
	Castle bCastle;
	int enemyCount;	//the actual number of enemies in the game
	int enemyRegionalCount[NoOfRegions];
	double c1, c2, c3; // input constants for periority equation
	int Unpaved[NoOfRegions]; // unpaved distance of each region
	InactiveEnemies inactiveEnemies; // the list that contain the inactive enemies
	ActiveEnemies normalEnemies[NoOfRegions];
	ShieldedEnemies shieldedEnemies[NoOfRegions];
	ActiveEnemies tankEnemies[NoOfRegions];
	Queue<Enemy*> killedEnemies;		
	Enemy * bEnemiesForDraw[MaxEnemyCount]; 	// This Array of Pointers is used for drawing elements in the GUI
								  			// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function
	int currentTime,killed;
	//
	// TODO: Add More Data Members As Needed
	//

public:
	
	Battle();
	void AddEnemy(Enemy* Ptr);
	void DrawEnemies(GUI * pGUI);
	Castle * GetCastle();
	void killRandom();		//Kills enemieas randomly according to phase 1.
	void update();
	int getCurrentTime() const;
	int getTotalAlive();		//Gets the number of alive enemies at any moment.
	void print();				//Prints data for phase 1.
	void Load(); // load all enemies in the inactive queue
	bool isFighting(); //are there still ENEMIES ALIVE????!!
	REGION getRegion(char);
	//
	// TODO: Add More Member Functions As Needed
	//
	/****************************  Inactive Enemies Functions  ****************************/
	void activateEnemy(Enemy* inactiveEnemy);
};


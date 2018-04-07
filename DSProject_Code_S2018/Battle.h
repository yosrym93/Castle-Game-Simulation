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
// it is the controller of the project
class Battle
{
private:
	Castle bCastle;
	int enemyCount;	//the actual number of enemies in the game
	Enemy * bEnemiesForDraw[MaxEnemyCount]; 
	double c1, c2, c3; // input constants for periority equation
	int Unpaved[NoOfRegions]; // unpaved distance of each region
	InactiveEnemies inactiveEnemies; // the list that contain the inactive enemies
	                                        // This Array of Pointers is used for drawing elements in the GUI
	ActiveEnemies normalEnemies;
	ActiveEnemies tankEnemies;
	Enemy * BEnemiesForDraw[MaxEnemyCount];	// This Array of Pointers is used for drawing elements in the GUI
								  			// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function
	int currentTime;
	//
	// TODO: Add More Data Members As Needed
	//

public:
	
	Battle();
	void AddEnemy(Enemy* Ptr);
	void DrawEnemies(GUI * pGUI);
	Castle * GetCastle();
	int getCurrentTime() const;
	void Load(); // load all enemies in the inactive queue
	REGION getRegion(char);
	//
	// TODO: Add More Member Functions As Needed
	//
	/****************************  Inactive Enemies Functions  ****************************/
	void activateEnemy(Enemy* inactiveEnemy);
};


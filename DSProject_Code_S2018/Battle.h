#pragma once

#include "Enemies\Enemy.h"
#include "Enemies\Fighter.h"
#include "Enemies\Balloon.h"
#include "Enemies\Paver.h"
#include "Enemies\Shielded.h"
#include "Enemies\Tank.h"
#include "Castle\Castle.h"
#include "ADTs\ActiveEnemies.h"
#include "ADTs\InactiveEnemies.h"

// it is the controller of the project
class Battle
{
private:
	Castle BCastle;
	ActiveEnemies normalEnemies;
	ActiveEnemies tankEnemies;
	int EnemyCount;	//the actual number of enemies in the game
	Enemy * BEnemiesForDraw[MaxEnemyCount];	// This Array of Pointers is used for drawing elements in the GUI
								  			// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function
	double C1, C2, C3; // input constants for periority equation
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

	/****************************  Inactive Enemies Functions  ****************************/
	void activateEnemy(Enemy* inactiveEnemy);
};


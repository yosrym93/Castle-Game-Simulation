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

#include "EnemyLists\ActiveEnemies.h"
#include "EnemyLists\InactiveEnemies.h"
#include "EnemyLists\ShieldedEnemies.h"

#include "Output\Output.h"


// it is the controller of the project
class Battle
{
private:
	Castle bCastle;
	int enemyCount;									//The number of active enemies (enemies in the GUI Array)
	double c1, c2, c3;							    //input constants for priority equation
	int currentTime;
	int unpavedDistance[NoOfRegions];				// unpaved distance of each region
	int nKilledEnemies[NoOfRegions];				//number of killed enemies in each region
	MenuItem mode;

	/************************Inactive Enemies List(s)************************/
	InactiveEnemies inactiveEnemies;				//all inactive enemies

	/************************Active Enemies List(s)************************/
	ActiveEnemies normalEnemies[NoOfRegions];		//pavers, fighters and balloons
	ShieldedEnemies shieldedEnemies[NoOfRegions];	//shielded fighters
	ActiveEnemies tankEnemies[NoOfRegions];			//tanks
	
	/************************ GUI Array ************************/
	Enemy * bEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI

	/************************ Output writer ************************/
	Output writer;							//Writes data to the output file

public:
	
	Battle();

	/************************ GUI array functions ************************/
	void addEnemyGUI(Enemy* Ptr);	//Adds an enemy to the GUI array
	void drawEnemies(GUI * pGUI);	//Draws enemies in the GUI array
	void removeKilledGUI();			//Removes killed enemies from the GUI array

	/********************************* Time Handling Functions ********************************/
	void timeCounter();
	void interactiveTime();
	void stepByStepTime();
	void silentTime();
	
	/***************************************************************************************/
	void killRandom();				//Kills enemieas randomly according to phase 1.
	void update(int);				//Updates all lists and the GUI array
	void load(GUI*);				//Loads all enemies to the inactive list
	bool isFighting();				//Are there still ENEMIES ALIVE????!!
	void print(GUI*);				//Prints towers,active and inactive enemies info.
	void healEnemies(int);				//increase enemies health in balloon fire time

	/****************************  Getter Functions  ****************************/
	Castle * getCastle();
	REGION getRegion(char);			//Converts char type into enum type
	char getRegion(int);			//Converts enum type into char type
	int getCurrentTime() const;		//Returns the current time step
	int getTotalAlive();			//Gets the number of alive enemies at any moment.
	int getUnpavedDist(int);		//Returns the unpaved distance of a region

	/****************************  Inactive Enemies Functions  ****************************/
	void activateEnemy(Enemy* inactiveEnemy);

	/**************************** Enmies Killing / Output Functions  ****************************/
	void removeKilledEnemies();		//Removes all killed enemies from all lists and sends them to the writer
	bool isKilledEnemy(Enemy*);		//Returns true if an enemy is killed and sends it to the writer
	void outputEnemy(Enemy*);		//Outputs enemy's data to output file (through writer)

};


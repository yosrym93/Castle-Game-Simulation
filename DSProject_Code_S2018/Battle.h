#pragma once
#include <fstream>
#include <Windows.h>
#include <mmsystem.h>
#include "Exceptions\ActionException.h"

#include "Enemies\Enemy.h"
#include "Enemies\Fighter.h"
#include "Enemies\Balloon.h"
#include "Enemies\Paver.h"
#include "Enemies\Shielded.h"
#include "Enemies\FreezeTank.h"

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
	int totalEnemiesCount;							//Total number of enemies in the game (inactive, active and killed);
	double c1, c2, c3;							    //input constants for priority equation
	int currentTime;
	int unpavedDistance[NoOfRegions];				// unpaved distance of each region
	int activeEnemies[NoOfRegions];
	int nKilledEnemies[NoOfRegions];				//number of killed enemies in each region
	bool enemyKilledAtT;							//true if an enemy was killed in this current step
	MODE mode;

	/************************Inactive Enemies List(s)************************/
	InactiveEnemies inactiveEnemies;				//all inactive enemies

	/************************Active Enemies List(s)************************/
	ActiveEnemies normalEnemies[NoOfRegions];		//pavers, fighters and balloons
	ShieldedEnemies shieldedEnemies[NoOfRegions];	//shielded fighters
	ActiveEnemies freezeTankEnemies[NoOfRegions];			//tanks
	
	/************************ GUI Array ************************/
	Enemy ** bEnemiesForDraw; // This Array of Pointers is used for drawing elements in the GUI

	/************************ Output writer ************************/
	Output writer;							//Writes data to the output file
public:
	
	Battle();
	~Battle();
	/*************************** Getters for the lists  ****************************/
	ActiveEnemies* getNormalEnemies();		
	ShieldedEnemies* getShieldedEnemies();	
	ActiveEnemies* getFreezeTankEnemies();
	double getC1();
	double getC2();
	double getC3();
	/*************************** GUI updating functions ****************************/
	void clearGUI(GUI* pGUI);		//Clears the GUI for redrawing
	void updateGUI(GUI* pGUI);		//Redraws the GUI
	/************************ GUI array functions ************************/
	void createGUIArray();			//Allocates the GUI array (or not) according to the mode
	void addEnemyGUI(Enemy* Ptr);	//Adds an enemy to the GUI array
	void drawEnemies(GUI * pGUI);	//Draws enemies in the GUI array
	void removeKilledGUI();			//Removes killed enemies from the GUI array
	void deleteGUIArray();			//Deallocates the GUI array (if allocated)

	/********************************* Time Handling Functions ********************************/
	void timeCounter(GUI*);

	
	/***************************************************************************************/
	void startBattle(GUI* pGUI);	//Initiates the battle
	void resetBattle();				//Resets all lists and output file to start over
	void killRandom();				//Kills enemieas randomly according to phase 1.
	void update();					//Updates all lists and the GUI array
	void updateShielded();			//Updates the pirority of the shielded lists
	void load(GUI*);				//Loads all enemies to the inactive list
	bool isFighting();				//Are there still ENEMIES ALIVE????!!
	void print(GUI*);				//Prints towers,active and inactive enemies info.
	void healEnemies(int);			//traverses enemies lists to icrease health in balloon fire time
	void input(GUI*);               //load the file and decide the mode
	void enemiesAttack();			//traverse enemies lists and call attack function for each enemy
	void pave(int,int);				//decrease paved distance during paver attack time
	void castleAttack();			//traverse enemies lists and call attack function for each enemy
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
	void writeEnemy(Enemy*);		//Outputs enemy's data to output file (through writer)

	/**************************** Audio Functions  ****************************/
	void playDeathSound();				//done
	void playTowerDestructionSound();
	void playPavingSound();				
	void playHealingSound();			//done
	void playFreezingSound();			//done
	void playVictorySound();
	void playDefeatSound();
};


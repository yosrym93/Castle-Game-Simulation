	#pragma once

#define NoOfRegions 4
#define MaxDistance  60         // the maximum distance between any enemy and its tower
#define MinDistance  2          // the minimum distance between any enemy and its tower
#define MaxVerticaEnemies  15   // the maximum number of enemies that can be drawn
		                        // if they are in the same region and same distance
								// (will be drawn vertical to each other)
#define MaxEnemyCount 300       // the maximum number of enemies the application can work on
//The four regions: A, B, C , and D
enum REGION {	
	A_REG,
	B_REG,
	C_REG,
	D_REG
};

// types of the enemies 
enum TYPE {
	paver,
	fighter,
	shielded,
	balloon,
	tank
};

//modes
enum Mode {
	interactive,
	stepbystep,
	silent
};
enum Action //action to do
{
	ACTION_INTERACTIVE,
	ACTION_STEPBYSTEP,
	ACTION_SILENT,
	ACTION_LOAD,
	ACTION_EXIT,
	BATTLE_AREA,  //A click on the battle area
	STATUS,       //A click on the status bar
	EMPTY        //A click on empty place in the toolbar


};
enum MenuItem
{
	//Note: menu icons are ordered here as they appear in menu
	//If you want to change the menu icons order, change the order here
	MENU_INTERACTIVE,
	MENU_STEPBYSTEP,
	MENU_SILENT,
	MENU_LOAD,
	MENU_EXIT,
	//TODO: Add more items names here
	//      for the 3 modes of the application
				
	MENU_ITM_COUNT	//no. of menu icons ==> This should be the last line in this enum
};

struct Point
{
	int x;
	int y;
	Point(int a=0, int b=0)	//constructor
	{ x=a;	y=b;	}
};
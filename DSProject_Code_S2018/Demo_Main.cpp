#include "Battle.h"
#include "GUI\GUI.h"

void Simulation(Battle *B, GUI *G);

int main()
{
	//
	// THIS IS JUST A DEMO
	// THIS MAIN SHOULD BE CHANGED IN PHASE 1 AND PHASE 2
	//

	Battle* pGameBattle = new Battle;

	GUI * pGUI = new GUI;
	Simulation(pGameBattle, pGUI);
	/*
	pGUI->PrintMessage("This is Just a Demo. Click to Move to the Next Time Step ...");

	//intialize health of the towers with 200
	pGameBattle->GetCastle()->setTowersHealth(200);
///	pGameBattle->Load();
	// Declare some enemies and fill their data
	// In the game, enemies should be loaded from an input file
	// and should be dynamically allocated
	Enemy e1(DARKBLUE, A_REG, 6);
	Enemy e2(DARKBLUE, D_REG, 60);
	Enemy e3(DARKOLIVEGREEN, B_REG, 30); 
	Enemy e4(DARKOLIVEGREEN, A_REG, 4);
	Enemy e5(ORANGERED, C_REG, 19); 
	Enemy e6(ORANGERED, C_REG, 30); 
	Enemy e7(ORANGERED, A_REG, 2);
	Enemy e8(DARKOLIVEGREEN, C_REG, 7); 
	Enemy e9(ORANGERED, A_REG, 30); 
	Enemy e10(DARKBLUE, C_REG, 4); 

	// Adding the enemies to the battle
	pGameBattle->AddEnemy(&e1);
	pGameBattle->AddEnemy(&e2);
	pGameBattle->AddEnemy(&e3);
	pGameBattle->AddEnemy(&e4);
	pGameBattle->AddEnemy(&e5);
	pGameBattle->AddEnemy(&e6);
	pGameBattle->AddEnemy(&e7);
	pGameBattle->AddEnemy(&e8);
	pGameBattle->AddEnemy(&e9);
	pGameBattle->AddEnemy(&e10);

	// Drawing the battle enemies
	pGameBattle->DrawEnemies(pGUI);

	Point p;
	pGUI->GetPointClicked(p);

	// Now a demo to move enemies some time steps
	// TimeStep is a normal integer that is incremented each time by 1
		for(int TimeStep = 1 ; TimeStep <= 10 ; TimeStep++)
	{
		// Clear for redrawing
		pGUI->ClearStatusBar();
		pGUI->ClearBattleArea();
		pGUI->DrawCastle();

		// Decrement the distance of each enemy
		e1.decrementDist();
		e2.decrementDist();
		e3.decrementDist();
		e4.decrementDist();
		e5.decrementDist();
		e6.decrementDist();
		e7.decrementDist();
		e8.decrementDist();
		e9.decrementDist();
		e10.decrementDist();

		// Redraw the enemies
		pGameBattle->DrawEnemies(pGUI);

		pGUI->GetPointClicked(p);
	}
	*/
	delete pGUI;
	delete pGameBattle;
	
	return 0;
}

void Simulation(Battle *pGameBattle,GUI *pGUI)
{
	pGameBattle->Load();
	pGUI->PrintMessage("Load Successful.");
	Point p;
	string msg;
	int TimeStep = 1;
	//pGUI->GetPointClicked(p);
	while (pGameBattle->isFighting())
	{
		pGUI->GetPointClicked(p);
		// Clear for redrawing
		pGUI->ClearStatusBar();
		pGUI->ClearBattleArea();
		pGUI->DrawCastle();
		pGameBattle->update();
		// Decrement the distance of each enemy
		

		// Redraw the enemies
		pGameBattle->DrawEnemies(pGUI);
		pGameBattle->killRandom();
		//pGUI->PrintMessage();
		TimeStep++;
	}

}
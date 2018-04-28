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
	delete pGUI;
	delete pGameBattle;
	
	return 0;
}

void Simulation(Battle *pGameBattle,GUI *pGUI)
{
	pGameBattle->load(pGUI);
	Point p;
	string msg;
	int TimeStep = 0;
	while (pGameBattle->isFighting())
	{
		pGUI->GetPointClicked(p);
		// Clear for redrawing
		pGUI->ClearStatusBar();
		pGUI->ClearBattleArea();
		pGUI->DrawCastle();
		pGameBattle->update(TimeStep);
		//printing info
		pGameBattle->print(pGUI);
		// Redraw the enemies
		pGameBattle->drawEnemies(pGUI);
		pGameBattle->killRandom();

		TimeStep++;
	}

	pGUI->GetPointClicked(p);
	
}

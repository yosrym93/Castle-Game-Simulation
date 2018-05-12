#include "Battle.h"
#include<chrono>
#include<thread>


using Clock = std::chrono::high_resolution_clock;


Battle::Battle()
{
	currentTime = 0;
	enemyCount = 0;
	totalEnemiesCount = 0;
	for (int i = 0; i < NoOfRegions; i++)
	{
		isDestroyed[i] = false;
		nKilledEnemies[i] = 0;
		unpavedDistance[i] = MaxDistance/2;
		activeEnemies[i] = 0;
	}

	bEnemiesForDraw = nullptr;
	gameStatus = WIN;
}
void Battle::killRandom()
{
	int list, region;
	for (int i = 0; i < 4;i++)
	{ 
		region = rand() % 4;
		list = rand() % 4;
		Enemy* temp;
		switch (list)
		{
		case 1:
			freezeTankEnemies[region].killRand();
			break;
		case 2:
			shieldedEnemies[region].killRand();
			break;
		case 3:
			normalEnemies[region].killRand();
			break;
		default:
			break;
		}

	}
}

/*************************** GUI updating functions ****************************/
//Clears the GUI for redrawing
void Battle::clearGUI(GUI* pGUI) {
	pGUI->ClearStatusBar();
	//pGUI->ClearBattleArea();
	//pGUI->DrawCastle();
	pGUI->drawDestroyedCastle(isDestroyed);
}

//Redraws the GUI
void Battle::updateGUI(GUI* pGUI) {
	print(pGUI);
	pGUI->DrawPaved(unpavedDistance);
	drawEnemies(pGUI);
}

/*************************** GUI array functions ****************************/
//Allocates the GUI array (or not) according to the mode
void Battle::createGUIArray() {
	if (mode!=MODE_SILENT) 	
		bEnemiesForDraw = new Enemy*[totalEnemiesCount];
}

//Adds an enemy to the GUI array
void Battle::addEnemyGUI(Enemy* Ptr)
{
	if (!bEnemiesForDraw)	//Checks if the array is allocated
		return;

	if (enemyCount < MaxEnemyCount)
	{
		bEnemiesForDraw[enemyCount++] = Ptr;
	}
}

//Draws enemies in the GUI array
void Battle::drawEnemies(GUI * pGUI)
{
	if (!bEnemiesForDraw)	//Checks if the array is allocated
		return;
	pGUI->DrawEnemies(bEnemiesForDraw, enemyCount);
}

void Battle::removeKilledGUI() {

	if (!bEnemiesForDraw)	//Checks if the array is allocated
		return;

	for (int i = 0; i < enemyCount; i++)
	{
		if (bEnemiesForDraw[i]->isKilled())
		{
			bEnemiesForDraw[i] = bEnemiesForDraw[enemyCount - 1];
			enemyCount--;
			i--;

		}
	}
}

void Battle::deleteGUIArray() {
	if (bEnemiesForDraw)			//Checks if the array was allocated
		delete[]bEnemiesForDraw;	//deletes the array only, as the enemies themselves are deleted from their lists

	bEnemiesForDraw = nullptr;
}

/********************************* Time Handling Functions ********************************/
void Battle::timeCounter(GUI* pGUI)
{
	ACTION userAction;
	bool modeChange = false;	//Flags for a mode change

	do {
		try {	//To throw mode change exceptions
			modeChange = false;
			switch (mode)
			{
			case MODE_INTERACTIVE:        //interactive mode
			{
				Point x;
				while (isFighting())
				{
					userAction = pGUI->getUserAction();
					//If a different action is picked throw an exception
					if (userAction == ACTION_STEPBYSTEP || userAction == ACTION_SILENT || 
						userAction == ACTION_LOAD || userAction == ACTION_EXIT)	
						throw ActionException(userAction);
					clearGUI(pGUI);
					update();
					updateGUI(pGUI);
					currentTime++;
				}
			}
			break;
			case MODE_STEPBYSTEP:        //step by step mode
			{
				auto next = Clock::now() + 1.2s;
				while (isFighting())
				{
					clearGUI(pGUI);
					update();
					updateGUI(pGUI);
					currentTime++;
					userAction = pGUI->getUserAction(next - Clock::now());
					//If a different action is picked throw an exception
					if (userAction == ACTION_INTERACTIVE || userAction == ACTION_SILENT ||
						userAction == ACTION_LOAD || userAction == ACTION_EXIT)
						throw ActionException(userAction);
					
					this_thread::sleep_until(next);
					next += 1.2s;
				}
			}
			break;
			case MODE_SILENT:             //silent mode
			{
				while (isFighting())
				{
					update();
					currentTime++;
				}

			}
			break;
			}
		}

		catch (ActionException actExc) {
			ACTION newAction = actExc.getExceptionAction();
			switch (newAction) {
				case ACTION_INTERACTIVE: 
				{
					mode = MODE_INTERACTIVE;	//Setting the new mode
					modeChange = true;			//To enter the loop again
					break;
				}
				case ACTION_STEPBYSTEP: 
				{
					mode = MODE_STEPBYSTEP;	//Setting the new mode
					modeChange = true;		//To enter the loop again
					break;
				}
				case ACTION_SILENT: 
				{
					mode = MODE_SILENT;	//Setting the new mode
					modeChange = true;	//To enter the loop again
					break;
				}
				case ACTION_LOAD: 
				{
					resetBattle();
					load(pGUI);
					createGUIArray();
					modeChange = true;	//To enter the loop again
					break;
				}

				case ACTION_EXIT:
					throw;
			}
		}
	} while (modeChange);
}





/*************************************/
//Initiates the battle
void Battle::startBattle(GUI* pGUI) {
	try {
		//Play background music
		playBackgroundMusic();
		//Inputs data from the user (input file & mode)
		input(pGUI);
		//Starts counting time and updating according to the chosen mode
		timeCounter(pGUI);
		//Game ended check status
		if (gameStatus == WIN) {
			//Do something
		}
		else {
			//Do something else
		}
	}
	catch (ActionException) {
		return;
	}
}

//Resets all lists and output file to start over
void Battle::resetBattle() {
	for (int i = 0; i < NoOfRegions; i++) {
		unpavedDistance[i] = MaxDistance/2;
		activeEnemies[i] = 0;
		nKilledEnemies[i] = 0;
		normalEnemies[i].clear();
		shieldedEnemies[i].clear();
		freezeTankEnemies[i].clear();
	}

	currentTime = 0;
	enemyCount = 0;
	totalEnemiesCount = 0;

	gameStatus = WIN;
	writer.reset();
	deleteGUIArray();
}

void Battle::checkTowers()
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		if (!isDestroyed[i] && bCastle.isDestroyed(i))
		{
			isDestroyed[i] = true;
			regionalMove(i);
			playTowerDestructionSound();
		}
	}
}

void Battle::regionalMove(int i)
{
	if (bCastle.isDestroyed())
		return;

	int next = i + 1;
	if (next == NoOfRegions)
		next = 0;
	while (bCastle.isDestroyed(next))
	{
		next++;
		if (next == NoOfRegions)
			next = 0;
	}
	normalEnemies[next].importOther(normalEnemies[i]);
	freezeTankEnemies[next].importOther(freezeTankEnemies[i]);
	shieldedEnemies[next].importOther(shieldedEnemies[i]);
	normalEnemies[next].enemiesTravel(next, unpavedDistance[next]);
	shieldedEnemies[next].enemiesTravel(next, unpavedDistance[next]);
	freezeTankEnemies[next].enemiesTravel(next, unpavedDistance[next]);
	while (activeEnemies[i] > 0)
	{
		activeEnemies[i]--;
		activeEnemies[next]++;
	}
}

//Updates all lists and the GUI array
void Battle::update()
{
	inactiveEnemies.activateEnemies(*this);
	updateShielded();
	castleAttack(currentTime);
	enemyKilledAtT = false;
	enemiesAttack();
	checkTowers();
	enemiesMove();
	removeKilledEnemies();

}
void Battle::enemiesMove()
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		normalEnemies[i].enemiesMove(this);
		shieldedEnemies[i].enemiesMove(this);
		freezeTankEnemies[i].enemiesMove(this);
	}
}

GAMESTATUS Battle::getGameStatus() {
	return gameStatus;
}

void Battle::updateShielded()
{
	for (int i = 0; i < NoOfRegions; i++)
		shieldedEnemies[i].calcPriority(this);
}


//print towers,active and inactive enemies info.
void Battle::print(GUI *pGUI)
{
	pGUI->ClearStatusBar();
	string castleInfo;
	string region;
	string enemies;
	pGUI->setHeight(1);
	pGUI->updatePrintedMessage("    Castle info: (at T = " + to_string(currentTime) + ")");
	for (int i = 0; i < NoOfRegions; i++)
	{
		pGUI->setHeight(2+2*i);
		castleInfo = bCastle.print(i);
		region = getRegion(i);
		pGUI->setWidth(0);
		pGUI->updatePrintedMessage("    Region " + region + "  " + castleInfo+"    Unpaved distance:"+to_string(unpavedDistance[i]));
		pGUI->setWidth(0);
		pGUI->setHeight(3 + 2*i);
		pGUI->updatePrintedMessage("    Active Enemies : "+ to_string(activeEnemies[i]) + "    Killed Enemies:" + to_string(nKilledEnemies[i]));
	}
}
void Battle::healEnemies(int regNumber,int* A)
{
	normalEnemies[regNumber].enemiesHeal(A);
	freezeTankEnemies[regNumber].enemiesHeal(A);
	shieldedEnemies[regNumber].enemiesHeal(A);
	playHealingSound();
}
//load the file and decide the mode 
void Battle::input(GUI *pGUI) 
{
	bool bload = false;
	bool bmode = false;
	ACTION action;

	while (!bload || !bmode)
	{
		action = pGUI->getUserAction();
		switch (action)
		{
		case ACTION_INTERACTIVE:
			bmode = true;
			mode = MODE_INTERACTIVE;
			break;
		case ACTION_STEPBYSTEP:
			bmode = true;
			mode = MODE_STEPBYSTEP;
			break;
		case ACTION_SILENT:
			bmode = true;
			mode = MODE_SILENT;
			break;
		case ACTION_LOAD:
			bload = true;
			load(pGUI);
			break;
		case ACTION_EXIT:
			throw ActionException(ACTION_EXIT);
			break;
		default:
			pGUI->PrintMessage("Pick the mode and load input file");
		}
		if (bload == true && bmode == false)
		{
			pGUI->PrintMessage("File loaded ,please choose a mode");
		}
		if (bload == false && bmode == true)
		{
			pGUI->PrintMessage("Mode choosen,please choose a file");
		}
	}
	//pGUI->drawFightingMenu(fileName,mode);
	createGUIArray();
}

void Battle::enemiesAttack()
{
	int sumunpavedA = 0, sumunpavedB = 0;
	for (int i = 0; i < NoOfRegions; i++)
	{
		sumunpavedA += unpavedDistance[i];
		normalEnemies[i].enemiesAttack(this);
		freezeTankEnemies[i].enemiesAttack(this);
		shieldedEnemies[i].enemiesAttack(this);
	}
	for (int i = 0; i < NoOfRegions; i++)
		sumunpavedB += unpavedDistance[i];
	if (sumunpavedA != sumunpavedB)
		playPavingSound();
}
//-------------Tower Attack----------------
void Battle::castleAttack(int currTime)
{
	bCastle.towersAttack(this, currTime);
}
ActiveEnemies* Battle::getNormalEnemies()
{
	return normalEnemies;
}
ShieldedEnemies* Battle::getShieldedEnemies()
{
	return shieldedEnemies;
}
ActiveEnemies* Battle::getFreezeTankEnemies()
{
	return freezeTankEnemies;
}
double Battle::getC1()
{
	return c1;
}
double Battle::getC2()
{
	return c2;
}
double Battle::getC3()
{
	return c3;
}
//------------------------------------------
void Battle::pave(int regNumber, int distance)
{
	unpavedDistance[regNumber] = (unpavedDistance[regNumber] < distance) ? unpavedDistance[regNumber] : distance;
}

// function that loads the inputs from the file 
void Battle::load(GUI*pGUI)
{
	inactiveEnemies.clear();
	ifstream inFile;
	pGUI->PrintMessage("Enter the file name ");
	string fileName = pGUI->GetString();
	inFile.open(fileName + ".txt"); //opening the file that we are going to read the data from it
	if (inFile.is_open()) //check if the file is open to access the data 
	{
		double tH;
		int maxNum, tP;
		double rc1, rc2, rc3;
		inFile >> tH >> maxNum >> tP >> rc1 >> rc2 >> rc3;
		c1 = rc1;
		c2 = rc2;
		c3 = rc3;
		// set health, Number and fire power of the 4 tower inside the castle
		bCastle.setTowersHealth(tH);
		bCastle.setTowersNum(maxNum);
		bCastle.setTowersFirePower(tP);

		int id;
		int type;
		int arrTime, pow, rld, spd;
		double health;
		char cRegion;
		REGION region;
		Enemy*pEnemy;
		inFile >> id;
		while (!inFile.eof() && (id != -1)) // looping until the end of the file (entering -1 )
		{
			pEnemy = nullptr;
			// read the data of the enemy
			inFile >> type >> arrTime >> health >> pow >> rld >> spd >> cRegion;
			region = getRegion(cRegion);
			//indicating the type of the enemy t assign the data to it
			switch (type)
			{
			case 0:
				pEnemy = new Paver(DARKBLUE, region, MaxDistance);
				break;
			case 1:
				pEnemy = new Fighter(DARKOLIVEGREEN, region, MaxDistance);
				break;
			case 2:
				pEnemy = new Shielded(ORANGERED, region, MaxDistance);
				break;
			case 3:
				pEnemy = new Balloon(MAGENTA, region, MaxDistance);
				break;
			case 4:
				pEnemy = new FreezeTank(SNOW, region, MaxDistance);
				break;
			default:
				break;
			}
			// if the pointer is not null set the data to the enemy specified
			if (pEnemy != nullptr)
			{
				pEnemy->setId(id);
				pEnemy->setType(type);
				pEnemy->setArrTime(arrTime);
				pEnemy->setHealth(health);
				pEnemy->setPow(pow);
				pEnemy->setRld(rld);
				pEnemy->setSpeed(spd);
				totalEnemiesCount++;
			}
			inactiveEnemies.addEnemy(pEnemy);
			inFile >> id;
		}
		//Sets some values for the writer 
		writer.setTotalEnemies(totalEnemiesCount);
		writer.setTowerStartingHealth(tH);

		pGUI->PrintMessage("Load Successful.");
	}
	else {
		Point p;
		pGUI->PrintMessage("No file with this name.");
		pGUI->GetPointClicked(p);
		load(pGUI);
	}
	if (inFile.is_open())
		inFile.close();
}


bool Battle::isFighting()
{
	bool allEnemiesKilled = true;
	for (int i = 0; i < NoOfRegions;i++)
		allEnemiesKilled = allEnemiesKilled && (freezeTankEnemies[i].isEmpty() && shieldedEnemies[i].isEmpty() && 
			normalEnemies[i].isEmpty() && inactiveEnemies.isEmpty());
	bool castleDestroyed = bCastle.isDestroyed();
	if (castleDestroyed)
		gameStatus = LOSE;
	return (!allEnemiesKilled && !castleDestroyed);
}

/****************************  Getter Functions  ****************************/
Castle * Battle::getCastle()
{
	return &bCastle;
}

//function that prepare the war (load all the Battle specifications)
int Battle::getTotalAlive()
{
	return enemyCount;
}


//return enum REGION from a char
REGION Battle::getRegion(char cRegion)
{
	REGION r;
	switch (cRegion)
	{
	case 'A':
		r = A_REG;
		break;
	case 'B':
		r = B_REG;
		break;
	case 'C':
		r = C_REG;
		break;
	case 'D':
		r = D_REG;
		break;
	default:
		r = A_REG;//default (this case should never happen)
		break;

	}
	return r;
}
// return char type of enum type
char Battle::getRegion(int cRegion)
{
	char r;
	switch (cRegion)
	{
	case A_REG:
		r = 'A';
		break;
	case B_REG:
		r = 'B';
		break;
	case C_REG:
		r = 'C';
		break;
	case D_REG:
		r = 'D';
		break;
	default:
		r ='A';//default (this case should never happen)
		break;

	}
	return r;
}

int Battle::getCurrentTime() const {
	return currentTime;
}

//Returns the unpaved distance of a region
int Battle::getUnpavedDist(int r) {
	return unpavedDistance[r];
}

/****************************  Inactive Enemies Functions  ****************************/
void Battle::activateEnemy(Enemy* inactiveEnemy) {
	int Reg = inactiveEnemy->getRegion();
	activeEnemies[Reg]++;

	if (mode!=MODE_SILENT) 
		addEnemyGUI(inactiveEnemy);

	Enemy* newActiveEnemy = dynamic_cast<Fighter*>(inactiveEnemy);
	if (newActiveEnemy) {
		normalEnemies[Reg].addEnemy(newActiveEnemy);
		return;
	}

	newActiveEnemy = dynamic_cast<Paver*>(inactiveEnemy);
	if (newActiveEnemy) {
		normalEnemies[Reg].addEnemy(newActiveEnemy);
		return;
	}

	newActiveEnemy = dynamic_cast<Balloon*>(inactiveEnemy);
	if (newActiveEnemy) {
		normalEnemies[Reg].addEnemy(newActiveEnemy);
		return;
	}

	newActiveEnemy = dynamic_cast<FreezeTank*>(inactiveEnemy);
	if (newActiveEnemy) {
		freezeTankEnemies[Reg].addEnemy(newActiveEnemy);
		return;
	}

	newActiveEnemy = dynamic_cast<Shielded*>(inactiveEnemy);
	if (newActiveEnemy) {
		shieldedEnemies[Reg].addEnemy(newActiveEnemy);
		return;
	}
}

/****************************  Killed Enemies Functions  ****************************/
//Removes all killed enemies from all lists and sends them to the writer
void Battle::removeKilledEnemies() {
	//Remove killed enemies from active lists
	for (int i = 0; i < NoOfRegions; i++) {
		normalEnemies[i].removeKilled(*this);
		shieldedEnemies[i].removeKilled(*this);
		freezeTankEnemies[i].removeKilled(*this);
	}

	//Remove killed enemies from the GUI array
	if (mode!=MODE_SILENT)	
		removeKilledGUI();

	//Writes removed enemies' data and delete them
	writer.writeEnemies(*this);
}

//Returns true if an enemy is killed and sends it to the writer
bool Battle::isKilledEnemy(Enemy* e) {
	if (e->isKilled()) {
		e->calcKD(currentTime);
		writer.addEnemy(e);
		nKilledEnemies[e->getRegion()]++;
		if (!enemyKilledAtT) {
			playDeathSound();
			enemyKilledAtT = true;
		}
		return true;
	}
	return false;
}

void Battle::writeEnemy(Enemy* e) {
	writer.writeEnemy(e, currentTime);
}

/**************************** Audio Functions  ****************************/

void Battle::playBackgroundMusic() {
		if (backgroundMusic.openFromFile("Sounds\\Fantascape.wav")) {
			backgroundMusic.play();
			backgroundMusic.setLoop(true);
			backgroundMusic.setVolume(100);
		}
}

void Battle::playDeathSound() {
	if (mode != MODE_SILENT)
		PlaySound(TEXT("Sounds\\EnemyDeath.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void Battle::playTowerDestructionSound() {
	if (mode != MODE_SILENT)
		PlaySound(TEXT("Sounds\\TowerDestruction.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void Battle::playPavingSound() {
	if (mode != MODE_SILENT)
		PlaySound(TEXT("Sounds\\Paving.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void Battle::playHealingSound() {
	if (mode != MODE_SILENT)
		PlaySound(TEXT("Sounds\\Healing.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void Battle::playFreezingSound() {
	if (mode != MODE_SILENT)
		PlaySound(TEXT("Sounds\\Freezing.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void Battle::playVictorySound() {
	if (mode != MODE_SILENT)
		PlaySound(TEXT("Sounds\\Victory.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void Battle::playDefeatSound() {
	if (mode != MODE_SILENT)
		PlaySound(TEXT("Sounds\\Defeat.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
/****************************  Destructor ****************************/
Battle::~Battle() {
	deleteGUIArray();
}


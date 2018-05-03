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
		nKilledEnemies[i] = 0;
		unpavedDistance[i] = MaxDistance;
		activeEnemies[i] = 0;
	}

	bEnemiesForDraw = nullptr;
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
			tankEnemies[region].killRand();
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
	pGUI->ClearBattleArea();
	pGUI->DrawCastle();
}

//Redraws the GUI
void Battle::updateGUI(GUI* pGUI) {
	print(pGUI);
	drawEnemies(pGUI);
	pGUI->DrawPaved(unpavedDistance);
}

/*************************** GUI array functions ****************************/
//Allocates the GUI array (or not) according to the mode
void Battle::createGUIArray() {
	if (mode!=silent) 	
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
}

/********************************* Time Handling Functions ********************************/
void Battle::timeCounter(GUI*p)
{
	switch (mode)
	{
	case interactive:        //interactive mode
	{
		Point x;
		while (isFighting())
		{
			p->GetPointClicked(x);
			update();
			currentTime++;
		}
	}
		break;
	case stepbystep:        //step by step mode
	{
		auto next = Clock::now() + 1s;
		while (isFighting())
		{
			 update();
			 currentTime++;
			 this_thread::sleep_until(next); 
			 next += 1s; 
		}
	}
		break;
	case silent:             //silent mode
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





/*************************************/

//Updates all lists and the GUI array
void Battle::update()
{
	enemyKilledAtT = false;
	
	removeKilledEnemies();

	inactiveEnemies.activateEnemies(*this);
}


//print towers,active and inactive enemies info.
void Battle::print(GUI *pGUI)
{
	pGUI->ClearStatusBar();
	string castleInfo;
	string region;
	string enemies;
	pGUI->setHeight(0);
	pGUI->updatePrintedMessage("Castle info: (at T = " + to_string(currentTime) + ")");
	for (int i = 0; i < NoOfRegions; i++)
	{
		pGUI->setHeight(1+2*i);
		castleInfo = bCastle.print(i);
		region = getRegion(i);
		pGUI->setWidth(0);
		pGUI->updatePrintedMessage("Region " + region + "  " + castleInfo+" Unpaved distance:"+to_string(unpavedDistance[i]));
		pGUI->setWidth(0);
		pGUI->setHeight(2 + 2*i);
		pGUI->updatePrintedMessage("Active Enemies : "+ to_string(activeEnemies[i]) + ". Killed Enemies:" + to_string(nKilledEnemies[i]));
	}
}
void Battle::healEnemies(int regNumber)
{
	normalEnemies[regNumber].traverseToHeal();
	tankEnemies[regNumber].traverseToHeal();
	shieldedEnemies[regNumber].traverseToHeal();
}
//load the file and decide the mode 
bool Battle::input(GUI *pGUI) 
{
	bool bload = false;
	bool bmode = false;
	Action action;
	while (!bload || !bmode)
	{
		action = pGUI->getUserAction();
		switch (action)
		{
		case ACTION_INTERACTIVE:
			bmode = true;
			mode = interactive;
			break;
		case ACTION_STEPBYSTEP:
			bmode = true;
			mode = stepbystep;
			break;
		case ACTION_SILENT:
			bmode = true;
			mode = silent;
			break;
		case ACTION_LOAD:
			bload = true;
			load(pGUI);
			break;
		case ACTION_EXIT:
			return false;
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
	pGUI->drawFightingMenu(fileName,mode);
	createGUIArray();
	return true;
}

void Battle::enemiesAttack()
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		normalEnemies[i].traverseToAttack(this);
		tankEnemies[i].traverseToAttack(this);
		shieldedEnemies[i].traverseToAttack(this);
	}
}

void Battle::pave(int regNumber, int distance, double firePower)
{
	if (distance - unpavedDistance[regNumber] <= int(firePower))
		unpavedDistance[regNumber] = unpavedDistance[regNumber] - int(firePower);
}

// function that loads the inputs from the file 
void Battle::load(GUI*pGUI)
{
	inactiveEnemies.clear();
	ifstream inFile;
	pGUI->PrintMessage("Enter the file name ");
	fileName = pGUI->GetString();
	inFile.open(fileName+".txt"); //opening the file that we are going to read the data from it
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
		int arrTime, pow, rld;
		double health;
		char cRegion;
		REGION region;
		Enemy*pEnemy;
		inFile >> id;
		while (!inFile.eof()&&(id!=-1)) // looping until the end of the file (entering -1 )
		{
			pEnemy=nullptr;
			// read the data of the enemy
			inFile >> type >> arrTime >> health >> pow >> rld >> cRegion;
			region = getRegion(cRegion);
			//indicating the type of the enemy t assign the data to it
			switch (type)
			{
			case 0:
				pEnemy = new Paver(DARKBLUE,region,MaxDistance);
				break;
			case 1:
				pEnemy = new Fighter(DARKOLIVEGREEN, region , MaxDistance);
				break;
			case 2:
				pEnemy = new Shielded(ORANGERED, region , MaxDistance);
				break;
			case 3:
				pEnemy = new Balloon(MAGENTA, region , MaxDistance);
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
				activeEnemies[region]++;
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
	bool isFig = false;
	for (int i = 0; i < NoOfRegions;i++)
		isFig = isFig || (!tankEnemies[i].isEmpty() || !shieldedEnemies[i].isEmpty() || !normalEnemies[i].isEmpty() || !inactiveEnemies.isEmpty());
	return isFig;
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

	if (mode!=silent) 
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
		tankEnemies[Reg].addEnemy(newActiveEnemy);
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
		tankEnemies[i].removeKilled(*this);
	}

	//Remove killed enemies from the GUI array
	if (mode!=silent)	
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

void Battle::playDeathSound() {
	PlaySound(TEXT("Sounds\\EnemyDeath.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void Battle::playTowerDestructionSound() {
	PlaySound(TEXT("Sounds\\TowerDestruction.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void Battle::playPavingSound() {
	PlaySound(TEXT("Sounds\\Paving.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void Battle::playHealingSound() {
	PlaySound(TEXT("Sounds\\Healing.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void Battle::playFreezingSound() {
	PlaySound(TEXT("Sounds\\Freezing.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void Battle::playVictorySound() {
	PlaySound(TEXT("Sounds\\Victory.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void Battle::playDefeatSound() {
	PlaySound(TEXT("Sounds\\Defeat.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
/****************************  Destructor ****************************/
Battle::~Battle() {
	deleteGUIArray();
}


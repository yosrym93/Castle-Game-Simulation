#include "Battle.h"

Battle::Battle()
{
	currentTime = 0;
	enemyCount = 0;
	for (int i = 0; i < NoOfRegions; i++)
	{
		nKilledEnemies[i] = 0;
	}
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

/*************************** GUI array functions ****************************/

//Adds an enemy to the GUI array
void Battle::addEnemyGUI(Enemy* Ptr)
{
	if (enemyCount < MaxEnemyCount)
	{
		bEnemiesForDraw[enemyCount++] = Ptr;
		//enemyRegionalCount[Ptr->getRegion()]++;
	}
	// Note that this function doesn't allocate any enemy objects
	// It only makes the first free pointer in the array
	// points to what is pointed to by the passed pointer Ptr
}

//Draws enemies in the GUI array
void Battle::drawEnemies(GUI * pGUI)
{
	pGUI->DrawEnemies(bEnemiesForDraw, enemyCount);
}

void Battle::removeKilledGUI() {

	for (int i = 0; i < enemyCount; i++)
	{
		if (bEnemiesForDraw[i]->isKilled())
		{
			nKilledEnemies[bEnemiesForDraw[i]->getRegion()]++;
			bEnemiesForDraw[i] = bEnemiesForDraw[enemyCount - 1];
			enemyCount--;
			i--;

		}
	}
}


/*************************************/


//Updates all lists and the GUI array
void Battle::update(int cTime)
{
	currentTime = cTime;
	
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
	pGUI->setWidth(0);
	pGUI->updatePrintedMessage("Format of printing: Enemy(Type,ID,Health,ArrivalTime,FirePwr,Rld), Tower(Health,Firepwr,No. of Enemies)" );
	pGUI->setHeight(1);
	pGUI->updatePrintedMessage("Castle info: (at T = " + to_string(currentTime) + ")");
	for (int i = 0; i < NoOfRegions; i++)
	{
		pGUI->setHeight(2+2*i);
		castleInfo = bCastle.print(i);
		region = getRegion(i);
		pGUI->setWidth(0);
		pGUI->updatePrintedMessage(("Region " + region+ ". Killed Enemies:"+to_string(nKilledEnemies[i])+"  "+castleInfo));
		pGUI->setWidth(0);
		pGUI->setHeight(3 + 2*i);
		pGUI->updatePrintedMessage("Active Enemies info: ");
		enemies=normalEnemies[i].print()+tankEnemies[i].print()+ shieldedEnemies[i].print();
		pGUI->setWidth(3);
		pGUI->updatePrintedMessage(enemies);
	}
}
void Battle::timeCounter()
{
		switch (mode)
		{
		case MENU_INTERACTIVE:        //interactive mode
			interactiveTime();
			break;
		case MENU_STEPBYSTEP:        //step by step mode
			stepByStepTime();
			break;
		case MENU_SILENT:             //silent mode
			silentTime();
			break;
		}

}
void Battle::interactiveTime()
{
	Point x;
	GUI*p;
	while (isFighting())
	{
		p->GetPointClicked(x);
		currentTime++;
	}
}
void Battle::stepByStepTime()
{
	while (isFighting())
	{
		Sleep(500);
		currentTime++;

	}
}
void Battle::silentTime()
{
	while (isFighting())
	{
		currentTime++;
	}
}
// function that loads the inputs from the file 
void Battle::load(GUI*pGUI)
{
	string fileName;
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

		int totalEnemiesCount = 0;

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
				pEnemy = new Tank(SNOW, region, MaxDistance);
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
	if (dynamic_cast<Fighter*>(inactiveEnemy)) {
		normalEnemies[Reg].addEnemy(inactiveEnemy);
		addEnemyGUI(inactiveEnemy);
		return;
	}
	if (dynamic_cast<Paver*>(inactiveEnemy)) {
		normalEnemies[Reg].addEnemy(inactiveEnemy);
		addEnemyGUI(inactiveEnemy);
		return;
	}
	if (dynamic_cast<Balloon*>(inactiveEnemy)) {
		normalEnemies[Reg].addEnemy(inactiveEnemy);
		addEnemyGUI(inactiveEnemy);
		return;
	}

	Enemy* tank = dynamic_cast<Tank*>(inactiveEnemy);
	if (tank) {
		tankEnemies[Reg].addEnemy(inactiveEnemy);
		addEnemyGUI(inactiveEnemy);
		return;
	}

	Enemy* shieldedFighter = dynamic_cast<Shielded*>(inactiveEnemy);
	if (shieldedFighter) {
		shieldedEnemies[Reg].addEnemy(inactiveEnemy);
		addEnemyGUI(inactiveEnemy);
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
	if (1)
		removeKilledGUI();

	//Writes removed enemies' data and delete them
	writer.writeEnemies(*this);
}

//Returns true if an enemy is killed and sends it to the writer
bool Battle::isKilledEnemy(Enemy* e) {
	if (e->isKilled()) {
		e->calcKD(currentTime);
		writer.addEnemy(e);
		return true;
	}
	return false;
}

void Battle::outputEnemy(Enemy* e) {
	writer.writeEnemy(e, currentTime);
}


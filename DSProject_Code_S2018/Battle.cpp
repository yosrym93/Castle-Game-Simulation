#include "Battle.h"
#include "ShieldedEnemies.cpp"

Battle::Battle()
{
	currentTime = 0;
	enemyCount = 0;
	for (int i = 0; i < NoOfRegions; i++)
	{
		killed[i] = 0;
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

//Adds an enemy to the GUI array
void Battle::AddEnemy(Enemy* Ptr)
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
void Battle::DrawEnemies(GUI * pGUI)
{
	pGUI->DrawEnemies(bEnemiesForDraw, enemyCount);
}

Castle * Battle::GetCastle()
{
	return &bCastle;
}

//Updates all lists and the GUI array
void Battle::update(int cTime)
{
	currentTime = cTime;
	
	double health;
	Enemy*temp;
	for (int i = 0;i < enemyCount;i++)
	{
		health=bEnemiesForDraw[i]->getHealth();
		if(health==0)
		{
			killed[bEnemiesForDraw[i]->getRegion()]++;
			bEnemiesForDraw[i] = bEnemiesForDraw[enemyCount-1];
			enemyCount--;
			i--;

		}
		else {
			bEnemiesForDraw[i]->decrementDist();
		}
	}
	for (int j = 0;j < NoOfRegions;j++)
	{
		normalEnemies[j].update();
		shieldedEnemies[j].update();
		tankEnemies[j].update();
	}

	inactiveEnemies.activateEnemies(*this);
}

//function that prepare the war (load all the Battle specifications)
int Battle::getTotalAlive()
{
	return enemyCount;
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
		pGUI->updatePrintedMessage(("Region " + region+ ". Killed Enemies:"+to_string(killed[i])+"  "+castleInfo));
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
void Battle::healEnemies(int reNumber)
{

}
// function that loads the inputs from the file 
void Battle::Load(GUI*pGUI)
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
			}
			inactiveEnemies.addEnemy(pEnemy);
			inFile >> id;
		}
		pGUI->PrintMessage("Load Successful.");
	}
	else {
		Point p;
		pGUI->PrintMessage("No file with this name.");
		pGUI->GetPointClicked(p);
		Load(pGUI);
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


/****************************  Inactive Enemies Functions  ****************************/
void Battle::activateEnemy(Enemy* inactiveEnemy) {
	int Reg = inactiveEnemy->getRegion();
	if (dynamic_cast<Fighter*>(inactiveEnemy)) {
		normalEnemies[Reg].addEnemy(inactiveEnemy);
		AddEnemy(inactiveEnemy);
		return;
	}
	if (dynamic_cast<Paver*>(inactiveEnemy)) {
		normalEnemies[Reg].addEnemy(inactiveEnemy);
		AddEnemy(inactiveEnemy);
		return;
	}
	if (dynamic_cast<Balloon*>(inactiveEnemy)) {
		normalEnemies[Reg].addEnemy(inactiveEnemy);
		AddEnemy(inactiveEnemy);
		return;
	}

	Enemy* tank = dynamic_cast<Tank*>(inactiveEnemy);
	if (tank) {
		tankEnemies[Reg].addEnemy(inactiveEnemy);
		AddEnemy(inactiveEnemy);
		return;
	}

	Enemy* shieldedFighter = dynamic_cast<Shielded*>(inactiveEnemy);
	if (shieldedFighter) {
		shieldedEnemies[Reg].addEnemy(inactiveEnemy);
		AddEnemy(inactiveEnemy);
		return;
	}
}
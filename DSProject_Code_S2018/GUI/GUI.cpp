#include "GUI.h"
int height=150;
int width=0;
//////////////////////////////////////////////////////////////////////////////////////////
GUI::GUI()
{
	pWind = new window(WindWidth+15,WindHeight,0,0);
	pWind->ChangeTitle("The Castle Game");

	DrawMenu();

	ClearStatusBar();
	ClearBattleArea();
	DrawCastle();
	
}
//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== INPUT FUNCTIONS ====================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::GetPointClicked(Point &P) const
{
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::setHeight(int i)
{
	height = StatusBarHeight;
	height -= (15 * i);
}
void GUI::setWidth(int i)
{
	width = 0;
	width = (50 * i);
}
string GUI::GetString() const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		
		PrintMessage(Label);
	}
}
///////////////////////////////////////////////////////

Action GUI::getUserAction()
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

									//[1] User clicks on the Battle area
	if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight)
	{
		return BATTLE_AREA;
	}

	//[2] If user clicks on the Toolbar
	else if (y >= 0 && y < MenuBarHeight) {
		//Check whick Menu item was clicked
		//==> This assumes that menu items are lined up horizontally <==
		int ClickedItemOrder = (x / MenuItemWidth);
		//Divide x coord of the point clicked by the menu item width (int division)
		//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
		switch (ClickedItemOrder)
		{
		case MENU_INTERACTIVE:return ACTION_INTERACTIVE;
		case MENU_STEPBYSTEP:return ACTION_STEPBYSTEP;
		case MENU_SILENT:return ACTION_SILENT;
		case MENU_LOAD:return ACTION_LOAD;
		case MENU_EXIT:return ACTION_EXIT;
		default: return EMPTY;
		}
	}
	return STATUS;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== OUTPUT FUNCTIONS ===================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(DARKRED);
	pWind->SetFont(18, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, WindHeight - (int) (StatusBarHeight / 1.5), msg); // You may need to change these coordinates later 
	                                                                      // to be able to write multi-line
}
void GUI::updatePrintedMessage(string msg) const	//Prints a message on status bar
{
	pWind->SetPen(DARKRED);
	pWind->SetFont(18, BOLD, BY_NAME, "Arial");
	pWind->DrawString(width, WindHeight - (int)(height), msg); // You may need to change these coordinates later 
															   // to be able to write multi-line
}

void GUI::drawFightingMenu(string fileName,Mode rmode)
{
	clearToolbar();
	string mode;
	switch (rmode)
	{
	case interactive:
		mode = "Interactive";
		break;
	case stepbystep:
		mode = "Step By Step";
		break;
	case silent:
		mode = "Silent";
		break;
	}
	pWind->SetBrush(LIGHTYELLOW);
	pWind->DrawRectangle(0, 0, WindWidth, WindHeight- MenuBarHeight);
	pWind->SetPen(DARKRED);
	pWind->SetFont(24, BOLD, BY_NAME, "Helvetica");
	pWind->DrawString( 20 , 10 ,"File Name:"+fileName);
	pWind->SetPen(DARKRED);
	pWind->SetFont(24, BOLD, BY_NAME, "Helvetica");
	pWind->DrawString(180, 10, "Mode:" + mode);
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, MenuBarHeight, WindWidth, MenuBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(DARKRED);
	pWind->SetFont(18, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(iX, iY, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawMenu() const
{
	//You can draw the menu icons any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in enum MenuItem
	string MenuItemImages[MENU_ITM_COUNT];

	MenuItemImages[MENU_LOAD] = "images\\MenuItems\\Menu_Load.jpg";
	MenuItemImages[MENU_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";
	MenuItemImages[MENU_INTERACTIVE] = "images\\MenuItems\\interactive.jpg";
	MenuItemImages[MENU_STEPBYSTEP] = "images\\MenuItems\\stepbystep.jpg";
	MenuItemImages[MENU_SILENT] = "images\\MenuItems\\Silent.jpg";

	//Draw menu item one image at a time
	for(int i=0; i<MENU_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, MenuBarHeight);

	//Draw a line under the menu bar
	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, MenuBarHeight, WindWidth, MenuBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	pWind->SetPen(WHITE, 3);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight , WindWidth, WindHeight);	

	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, WindHeight - StatusBarHeight , WindWidth, WindHeight - StatusBarHeight);	
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::ClearBattleArea() const
{
	// Clearing the battle area
	pWind->SetPen(KHAKI, 3);
	pWind->SetBrush(KHAKI);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::clearToolbar()
{
	pWind->SetPen(WHITE, 3);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, WindWidth, WindHeight - MenuBarHeight);

	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, WindHeight - MenuBarHeight, WindWidth, WindHeight - MenuBarHeight);

}
///////////////////////////////////////////////////////////////////////////////////
void GUI::DrawCastle() const
{
	int L = CastleWidth / 2;

	// 1- Drawing the brown square of the castle
	//pWind->SetPen(BROWN);
	//pWind->SetBrush(BROWN);
	//pWind->DrawRectangle(CastleStartX, CastleStartY, CastleEndX, CastleEndY);
	pWind->DrawImage("images\\MenuItems\\castle.jpg", CastleStartX, CastleStartY, CastleWidth, CastleWidth);
	// 2- Drawing the 2 brown crossed lines (for making 4 regions)
	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, YHalfBattleArea, WindWidth, YHalfBattleArea);
	pWind->DrawLine(WindWidth/2, MenuBarHeight, WindWidth/2, WindHeight-StatusBarHeight);

	// 3- Drawing the 2 white crossed lines (inside the castle)
	//pWind->SetPen(WHITE);
	//pWind->DrawLine(WindWidth/2, YHalfBattleArea - CastleWidth/2, WindWidth/2, YHalfBattleArea + CastleWidth/2);
	//pWind->DrawLine(WindWidth/2 - CastleWidth/2, YHalfBattleArea, WindWidth/2 + CastleWidth/2, YHalfBattleArea);

	// 4- Drawing the 4 white squares inside the castle (one for each tower)
	//pWind->SetPen(WHITE);
	//pWind->SetBrush(WHITE);
	//pWind->DrawRectangle(CastleStartX + L/3, CastleStartY + L/3, CastleStartX + 2*L/3, CastleStartY + 2*L/3);
	//pWind->DrawRectangle(CastleStartX + L/3, CastleEndY - L/3, CastleStartX + 2*L/3, CastleEndY - 2*L/3);
	//pWind->DrawRectangle(CastleEndX - 2*L/3, CastleStartY + L/3, CastleEndX - L/3, CastleStartY + 2*L/3);
	//pWind->DrawRectangle(CastleEndX - 2*L/3, CastleEndY - L/3, CastleEndX - L/3, CastleEndY - 2*L/3);

	// 5- Writing the letter of each region (A, B, C, D)
	//pWind->SetPen(BROWN);
	//pWind->SetFont(25, BOLD , BY_NAME, "Arial");
	//pWind->DrawString(CastleStartX + 0.44*L, CastleStartY + 5*L/12, "A");
	//pWind->DrawString(CastleStartX + 0.44*L, YHalfBattleArea + 5*L/12, "D");
	//pWind->DrawString(WindWidth/2 + 0.44*L, CastleStartY + 5*L/12, "B");
	//pWind->DrawString(WindWidth/2 + 0.44*L, YHalfBattleArea + 5*L/12, "C");

	// 6- Drawing the 2 vertical brown lines at distance 60
	// that is because some rounding errors may occur if you choose another width and height for the window
	// so we draw 2 vertical lines at distance 60 to mark it
	pWind->SetPen(BROWN);
	pWind->DrawLine(CastleStartX - MaxDistance*EnemyWidth - MaxDistance -1, MenuBarHeight,
		CastleStartX - MaxDistance*EnemyWidth - MaxDistance -1, WindHeight-StatusBarHeight);
	pWind->DrawLine(CastleEndX + MaxDistance*EnemyWidth + MaxDistance +1, MenuBarHeight,
		CastleEndX + MaxDistance*EnemyWidth + MaxDistance +1, WindHeight-StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawEnemy(const Enemy & E, int YPos) const       // It's a private function
{
	color clr = E.getColor();
	REGION Region = E.getRegion();
	int Distance = E.getDistance();

	int x, y, refX, refY;
	//First calculate x,y position of the enemy on the output screen
	//It depends on the region and the enemy distance
	switch (Region)
	{
	case A_REG:
		refX = (WindWidth/2 - CastleWidth/2);
		refY = YHalfBattleArea- 1 - EnemyWidth; //
		x = refX - Distance*EnemyWidth - Distance; //(Distance)
		y = refY - YPos*EnemyHeight - YPos; // YPos
		break;
	case B_REG:
		refX = (WindWidth/2 + CastleWidth/2);
		refY = YHalfBattleArea- 1 - EnemyWidth; //
		x = refX + (Distance-1)*EnemyWidth + Distance; //(Distance)
		y = refY - YPos*EnemyHeight - YPos; // YPos
		break;
	case C_REG:
		refX = (WindWidth/2 + CastleWidth/2);
		refY = YHalfBattleArea + 2 + EnemyWidth; //
		x = refX + (Distance-1)*EnemyWidth + Distance; //(Distance)
		y = refY + (YPos-1)*EnemyHeight + YPos; // YPos
		break;
	case D_REG:
		refX = (WindWidth/2 - CastleWidth/2);
		refY = YHalfBattleArea + 2 + EnemyWidth; //
		x = refX - Distance*EnemyWidth - Distance; //(Distance)
		y = refY + (YPos-1)*EnemyHeight + YPos; // YPos
		break;
	default:
		break;
	}

	// Drawing the enemy
	pWind->SetPen(clr);
	pWind->SetBrush(clr);
	pWind->DrawRectangle(x, y, x + EnemyWidth, y + EnemyHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
/* A function to draw a list of enemies and ensure there is no overflow in the drawing*/
// To use this function, you must prepare its input parameters as specified
// [Input Parameters]:
//    enemies [ ] : array of enemy pointers (ALL enemies from all regions in one array)
//    size : the size of the array (total no. of enemies)
void GUI::DrawEnemies(Enemy* enemies[], int size) const
{
	//draw enemies at each region 
	for(int region = A_REG; region <= D_REG; region++)
	{
		int CountEnemies = 0;	// count Enemies at the same distance to draw them vertically if they are <= 15 enemy 
		                        // else print number of enemy in the region
		bool draw=true;
		for(int distance = MaxDistance ; distance >= MinDistance ; distance--)
		{
			CountEnemies = 0;

			for(int i = 0 ; i < size ; i++)
			{	
				if(enemies[i]->getDistance() == distance && enemies[i]->getRegion() == region)
				{
					CountEnemies++;
				}
			}
			if(CountEnemies > 15)
			{
				draw=false;
				break;
			}
		}
		if(draw)
		{
			for( int distance = MaxDistance ; distance > 1 ; distance-- )
			{
				CountEnemies=0;

				for(int i = 0 ; i < size ; i++)
				{	
					if(enemies[i]->getDistance() == distance && enemies[i]->getRegion() == region)
					{
						DrawEnemy(*(enemies[i]), CountEnemies + 1);
						CountEnemies++;
					}
				}
			}
		}
		else // print message maximum reached in this region
		{
			PrintMessage("Cannot Draw Enemies of region " + to_string(region+1) + 
				"! More than" + to_string(MaxVerticaEnemies) + " enemies are in the same region and distance..");
			Sleep(1000); // because may be more than one region has drawing overflow
		}
	}
}

/* Barret Fisher
 * CS 216
 * Fall 2013
*/

#include "Tools.h"
#include "GenericFactory.h"
#include "DungeonLevel.h"
#include "Tile.h"
#include "Character.h"
#include "Player.h"
#include "Creature.h"
#include "Item.h"
#include "Consumable.h"
#include "Equipment.h"
#include "Armor.h"
#include "Weapon.h"

#include <ncurses.h>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

void message()
{
	int y = 33;
	move(y,0);
	printw(" Careful. You've just entered Grimlich's Dungeon. Six levels beneath your feet\n");
	y++;
	move(y,0);
	printw("he lies in wait, and only he has the treasure you seek. You must defeat him in\n");
	y++;
	move(y,0);
	printw("order to obtain the Silver Key ('$'). Obtain it and exit upstairs and you win!\n");
	y++;
	move(y,0);
	printw("But! (And there's always a but.) In order to advance to the seventh level you\n");
	y++;
	move(y,0);
	printw("must increase in skill as the creatures you encounter will get harder. They\n");
	y++;
	move(y,0);
	printw("will also regenerate every step you take. Look for items and weapons to help\n");
	y++;
	move(y,0);
	printw("you on your quest. Killing as many creatures as you can will also advance your\n");
	y++;
	move(y,0);
	printw("health and stats. Navigate your way down by going to downstairs tiles ('>') and\n");
	y++;
	move(y,0);
	printw("return by climbing upstairs tiles ('<'). You'll know Grimlich when you see him,\n");
	y++;
	move(y,0);
	printw("the magenta-colored serpent is easy to spot ... just be ready when you do.\n");
	move(31,29);
}

void itemGrab(DungeonLevel * pLevel, Player * pPlayer, int y, int x)
{
	for (int j = (y-1); j < (y+2); j++)
	{
		for (int i = (x-1); i < (x+2); i++)
		{
			if (pLevel->at(j,i).getItem() != NULL)
			{
				pPlayer->pickUp(pLevel->at(j,i).getItem());
				pLevel->remove(j,i);
			}
		}
	}
}

int changeLevel(vector<DungeonLevel*> theGame, int level, Player * pPlayer, int newY, int newX)
{
	int yLine;
	int xLine;
	getyx(stdscr,yLine,xLine);
	
	vector<int> newPosition;
	stringstream ss;
	if ( theGame[level]->at(newY,newX).getUnderTileChar() == '<')
	{
		level--;
		if (level >= 0)
		{
			ss.str("");
			ss << "You have gone upstairs. New level is " << level+1 << ".";
			addstr(ss.str().c_str());
			yLine++;
			move(yLine,0);
			newPosition = theGame[level]->getDownstairs();
			theGame[level]->warp(pPlayer,newPosition[0],newPosition[1]);
			theGame[level+1]->setPlayer(NULL);
		}
	} else if ( theGame[level]->at(newY,newX).getUnderTileChar() == '>') {
		if (level < 6)
		{
			level++;
			ss.str("");
			ss << "You have gone downstairs. New level is " << level+1 << ".";
			addstr(ss.str().c_str());
			yLine++;
			move(yLine,0);
			newPosition = theGame[level]->getUpstairs();
			theGame[level]->warp(pPlayer,newPosition[0],newPosition[1]);
			theGame[level-1]->setPlayer(NULL);
		} else {
			ss.str("");
			ss << "You are on the last level!";
			addstr(ss.str().c_str());
			yLine++;
			yLine++;
			move(yLine,0);
		}
	}
	return level;
}

string fight(DungeonLevel * pLevel, Player * pPlayer, int level, string command, int y, int x)
{
	int yLine;
	int xLine;
	getyx(stdscr,yLine,xLine);

	pLevel->stepCreatures();
	stringstream ss;

	vector<vector<int>> creatureCoords = pLevel->findCreatures();
	vector<int> aCreature;
	int creatureY;
	int creatureX;

	for (size_t i = 0; i < creatureCoords.size(); i++)
	{
		aCreature = creatureCoords[i];
		creatureY = aCreature[0];
		creatureX = aCreature[1];
		if (((creatureY-1 == y)&&(creatureX == x)) || ((creatureY+1 == y)&&(creatureX == x))
			|| ((creatureX-1 == x)&&(creatureY == y)) || ((creatureX+1 == x)&&(creatureY == y)))
		{
			int max = pLevel->at(creatureY,creatureX).getCreature()->getHealth();
			pPlayer->clearDeath();
			if (pLevel->at(creatureY,creatureX).getCreature()->getHostility())
			{
				char boss = pLevel->at(creatureY,creatureX).getCreature()->getSymbol();
				command = "Defend";
				ss.str("");
				ss << pLevel->at(creatureY,creatureX).getCreature()->getName() << " is attacking you!";
				addstr(ss.str().c_str());
				yLine++;
				yLine++;
				move(yLine,0);

				pLevel->at(creatureY,creatureX).getCreature()->attack(*pPlayer);
				getyx(stdscr,yLine,xLine);
				yLine++;
				move(yLine,0);

				if ( (pLevel->at(creatureY,creatureX).getCreature()->getHealth() <= 0) && (pPlayer->getHealth() > 0) )
				{
					int points = Tools::randomValue(pLevel->at(creatureY,creatureX).getCreature()->getStats());
					points+=2;
					pPlayer->setExperience( points );
					ss.str("");
					ss << pLevel->at(creatureY,creatureX).getCreature()->getName() << " has been destroyed. You gained " << points << " experience points!";
					addstr(ss.str().c_str());
					yLine++;
					yLine++;
					move(yLine,0);

					pLevel->at(creatureY,creatureX).getCreature() -> ~Creature();
					pLevel->kill(creatureY,creatureX);

					if (boss != '?')
					{
						int oneInFour = Tools::randomValue(4);
						if (oneInFour == 3)
						{
							ss.str("");
							ss << "... the creature dropped an item!";
							addstr(ss.str().c_str());
							yLine++;
							move(yLine,0);

							int oneInTwo = Tools::randomValue(2);
							if (oneInTwo == 0) {
								pLevel->dropItem(GenericFactory::instance().generateArmor(max+25), creatureY, creatureX);
							} else if (oneInTwo == 1) {
								pLevel->dropItem(GenericFactory::instance().generateWeapon(max+25), creatureY, creatureX);
							}
						}
					} else {
						ss.str("");
						ss << "... Grimlich dropped the Silver Key!";
						addstr(ss.str().c_str());
						yLine++;
						move(yLine,0);
						pLevel->dropItem(GenericFactory::instance().generateEquipment('$'), creatureY, creatureX);
					}
				} else {
					command = "q";
				}
			} else {

				pPlayer->playerMap(pLevel->getMap(),level);

				ss.str("");
				ss << pLevel->at(creatureY,creatureX).getCreature()->getName() << " nearby, but it is not hostile. Attack? (y or n) ";
				addstr(ss.str().c_str());
				
				refresh();
				string sAttack;
				int iAttack = getch();
				sAttack = static_cast<char>(iAttack);
				clear();

				move(33,0);

				if (sAttack == "y")
				{
					command = "Attack";
					pPlayer -> attack(*pLevel->at(creatureY,creatureX).getCreature());
					getyx(stdscr,yLine,xLine);
					yLine++;
					move(yLine,0);

					if ( (pLevel->at(creatureY,creatureX).getCreature()->getHealth() <= 0) && (pPlayer->getHealth() > 0) )
					{
						int points = Tools::randomValue(pLevel->at(creatureY,creatureX).getCreature()->getStats());
						points+=2;
						pPlayer->setExperience( points );
						ss.str("");
						ss << pLevel->at(creatureY,creatureX).getCreature()->getName() << " has been destroyed. You gained " << points << " experience points!";
						addstr(ss.str().c_str());				
						yLine++;
						yLine++;
						move(yLine,0);
						pLevel->at(creatureY,creatureX).getCreature() -> ~Creature();
						pLevel->kill(creatureY,creatureX);
						int oneInFour = Tools::randomValue(4);
						if (oneInFour == 0)
						{
							ss.str("");
							ss << "... the creature dropped an item!";
							addstr(ss.str().c_str());
							yLine++;
							move(yLine,0);
							int oneInTwo = Tools::randomValue(2);
							if (oneInTwo == 0) {
								pLevel->dropItem(GenericFactory::instance().generateArmor(max+25), creatureY, creatureX);
							} else if (oneInTwo == 1) {
								pLevel->dropItem(GenericFactory::instance().generateWeapon(max+25), creatureY, creatureX);
							}
						}
					} else {
						command = "q";
					}
				}
			}
		}
	}
	return command;
}


int main(int argc, char * argv[])
{
	cout << endl;
	cout << "Please adjust your window to full screen for maximum benefit..." << endl;
	cout << endl;
	cout << endl;
	cout << "-= Grimlich's Dungeon =-" << endl;
	cout << endl;
	
	string name;
	cout << "Enter your name: ";
	cin >> name;
	cout << endl;

	vector<DungeonLevel*> Game;

	DungeonLevel * level0 = new DungeonLevel();
	DungeonLevel * level1 = new DungeonLevel();
	DungeonLevel * level2 = new DungeonLevel();
	DungeonLevel * level3 = new DungeonLevel();
	DungeonLevel * level4 = new DungeonLevel();
	DungeonLevel * level5 = new DungeonLevel();
	DungeonLevel * level6 = new DungeonLevel();

	Game.push_back(level0);
	Game.push_back(level1);
	Game.push_back(level2);
	Game.push_back(level3);
	Game.push_back(level4);
	Game.push_back(level5);
	Game.push_back(level6);

	int level = 0;

	Player user = Player();
	user.setName(name);
	if (name == "Barret")
	{
		user.setMaxHealth(975);
		user.setHealth(975);
		user.setLevel(100);
	}


	Game[level]->addElement(' ',&user);
	
	for (int i=0; i<7; i++)
	{
		Game[0]->addElement(' ',GenericFactory::instance().generateCreature(0,21));
		Game[1]->addElement(' ',GenericFactory::instance().generateCreature(10,41));
		Game[2]->addElement(' ',GenericFactory::instance().generateCreature(20,61));
		Game[3]->addElement(' ',GenericFactory::instance().generateCreature(30,81));
		Game[4]->addElement(' ',GenericFactory::instance().generateCreature(40,101));
		Game[5]->addElement(' ',GenericFactory::instance().generateCreature(80,151));
		Game[6]->addElement(' ',GenericFactory::instance().generateCreature(120,201));
	}

	Game[0]->addElement(' ',GenericFactory::instance().generateConsumable());
	Game[0]->addElement(' ',GenericFactory::instance().generateConsumable());
	Game[0]->addElement(' ',GenericFactory::instance().generateConsumable());

	Game[0]->addElement(' ',GenericFactory::instance().generateArmor(21));
	Game[0]->addElement(' ',GenericFactory::instance().generateWeapon(11));
	Game[2]->addElement(' ',GenericFactory::instance().generateWeapon(51));	
	Game[3]->addElement(' ',GenericFactory::instance().generateArmor(81));
	Game[3]->addElement(' ',GenericFactory::instance().generateWeapon(81));
	Game[4]->addElement(' ',GenericFactory::instance().generateWeapon(131));
	Game[5]->addElement(' ',GenericFactory::instance().generateArmor(146));
	Game[6]->addElement(' ',GenericFactory::instance().generateArmor(201));
	Game[6]->addElement(' ',GenericFactory::instance().generateWeapon(201));
	
	Game[6]->addElement(' ',GenericFactory::instance().generateCreature(349,351));

	initscr();
	keypad(stdscr, TRUE);

	if(has_colors() == FALSE)
	{	
		endwin();
		printf("Your terminal does not support color\n");
		return 0;
	} else {
		start_color();
		init_pair(0, COLOR_BLACK, COLOR_BLACK);
		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_GREEN, COLOR_BLACK);
		init_pair(3, COLOR_YELLOW, COLOR_BLACK);
		init_pair(4, COLOR_BLUE, COLOR_BLACK);
		init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(6, COLOR_CYAN, COLOR_BLACK);
		init_pair(7, COLOR_WHITE, COLOR_BLACK);
	}

	stringstream ss;
	int iCommand = ' ';
	string sCommand = "(none)";
	
	vector<int> position = user.getPosition();
	int turns = 1;

	while (sCommand != "q")
	{
		move(0,0);

		if ((turns % 30 == 0) && (Game[level]->findCreatures().size() < (unsigned int)level+10))
		{
			Game[level]->addElement(' ',GenericFactory::instance().generateCreature(level,(level+1)*30));
		}

		if (turns % 50 == 0)
		{
			Game[level]->addElement(' ',GenericFactory::instance().generateConsumable());
		}

		if (user.getHealth() < 20)
		{
			attron( COLOR_PAIR(1) );
			ss.str("");
			ss << "Health is getting low...";					//line 0
			move(0,0);
			clrtoeol();
			addstr(ss.str().c_str());
			attroff( COLOR_PAIR(1) );
		}
		
		user.playerMap(Game[level]->getMap(),level);				//line 2-29

		ss.str("");
		ss << "Turn: " << turns << ", Last command: " << sCommand;
		move(31,0);																					//line 31
		clrtoeol();
		addstr(ss.str().c_str());

		if (turns == 1)
		{
			message();
		}

		refresh();
		iCommand = getch();
		sCommand = static_cast<char>(iCommand);
		clear();

		move(33,0);																					//line 33

		if (sCommand != "q")
		{
			if (sCommand == "p")
			{
				itemGrab(Game[level],&user,position[0],position[1]);
				sCommand = "Pickup";
			}

			if (sCommand == "u")
			{
				user.use(Game[level]->getMap(),level);
				sCommand = "Use";
			}

			if (sCommand == "d")
			{
				Game[level]->dropItem(	user.drop(Game[level]->getMap(),level), position[0], position[1]);
				sCommand = "Drop";
			}

			position = user.getPosition();
			int nextY = position[0];
			int nextX = position[1];

			if ( (iCommand == KEY_UP) || (iCommand == KEY_DOWN) || (iCommand == KEY_LEFT) || (iCommand == KEY_RIGHT) )
			{
				if (iCommand == KEY_UP)
				{
					nextY--;
					sCommand = "Up";
				} else if (iCommand == KEY_DOWN) {
					nextY++;
					sCommand = "Down";
				} else if (iCommand == KEY_LEFT) {
					nextX--;
					sCommand = "Left";
				} else if (iCommand == KEY_RIGHT) {
					nextX++;
					sCommand = "Right";
				}

				Game[level]->step(position[0],position[1],nextY,nextX);
				
				int nextLevel = changeLevel(Game, level, &user, nextY, nextX);
				
				position = user.getPosition();

				if (level == nextLevel)
				{
					if ( (position[0] == nextY) && (position[1] == nextX) )
					{
						turns++;
						sCommand = fight(Game[nextLevel], &user, level, sCommand, position[0], position[1]);
					}
				}
				level = nextLevel;

				if (level == -1)
				{
					sCommand = "q";
				}

			}
			if (turns % 10 == 0)
			{
				if ( (user.getHealth()+1) <= user.getMaxHealth() )
				{
					user.setHealth( user.getHealth() + 1 );
				}
			}

		}
	}

	endwin();

	if (user.getHealth() > 0)
	{
		if (user.hasKey())
		{
			cout << "The dungeon was escaped ... with the Silver Key! You win!" << endl;
			cout << endl;
		} else {
			cout << "The dungeon was escaped ... but you did not retrieve the key." << endl;
			cout << endl;
		}
	} else {
		vector<string> finalWords = user.getDeath();
		for (int i = 0; i < finalWords.size(); i++)
		{
			cout << finalWords[i];
			cout << endl;
		}
	}
	cout << endl;
	cout << "    -= END GAME =-" << endl;
	cout << endl;
	cout << "Your game lasted " << turns << " turns." << endl;
	cout << endl;
	user.dumpObject();

	return 0;
}
 

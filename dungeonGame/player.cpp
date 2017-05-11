#include <ncurses.h>
#include "Player.h"
#include "Item.h"
#include "Consumable.h"
#include "Equipment.h"
#include "Armor.h"
#include "Weapon.h"
#include "DungeonLevel.h"
#include "Tools.h"
#include <cstdlib>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

Player::Player()
{
	for (int i = 0; i < 3; i++)
	{
		equipped.push_back(NULL);
	}
	play_score = 0;
	play_experience = 0;
	play_level = 0;
	base_stats = 0;
	max_health = 0;
	attack_stats = 0;
	attack_bonus = 0;
	defense_stats = 5;
	defense_bonus = 0;
	setLevel(1);
	setAttack( attack_stats, attack_bonus );
	setDefense( defense_stats, defense_bonus );
	setSymbol('@');
	key = false;
	max_health = 50;
	setHealth(max_health);
}


void Player::setExperience(int new_points)
{
	int yLine;
	int xLine;
	getyx(stdscr,yLine,xLine);

	stringstream ss;
	play_score += new_points;
	play_experience += new_points;
	if (play_experience > 50)
	{
		attron(COLOR_PAIR(2));
		setLevel(getLevel()+1);
		move(0,0);
		clrtoeol();
		ss.str("");
		ss << "You leveled up!";
		addstr(ss.str().c_str());
		play_experience = 0;
		attroff(COLOR_PAIR(2));
	}
	move(yLine,0);
}

void Player::setLevel(int new_play_level)
{
	play_level = new_play_level;
	max_health += 25;
	base_stats = (play_level * 10);
	setStats(base_stats);
	if ( (getHealth()+25) < max_health )
	{
		setHealth(getHealth()+25);
	} else {
		setHealth(max_health);
	}
}

int Player::getExperience()
{
	return play_experience;
}

int Player::getLevel()
{
	return play_level;
}

int Player::getScore()
{
	return play_score;
}

int Player::setMaxHealth(int newHealth)
{
	max_health = newHealth;
}

int Player::getMaxHealth()
{
	return max_health;
}

int Player::getMaxAttack()
{
	return base_stats + attack_stats;
}

int Player::getAttackBonus()
{
	return attack_bonus;
}

int Player::getMaxDefense()
{
	return defense_stats;
}

int Player::getDefenseBonus()
{
	return defense_bonus;
}

bool Player::hasKey()
{
	return key;
}



void Player::playerMap(vector<vector<char>> pCharMap, int pLevel)
{
	stringstream ss;
	ss.str("");
	ss << "===============================================================================";	//line 2
	move(2,0);
	addstr(ss.str().c_str());

	ss.str("");
	ss << "HP:" << getHealth() << "/" << getMaxHealth() << "     Attack:Upto(" << getMaxAttack() << ")+" << getAttackBonus() << "     Defense:Upto(" << getMaxDefense() << ")+" << getDefenseBonus() << "     Score:" << getScore();			//line 3
	move(3,0);
	addstr(ss.str().c_str());

	ss.str("");
	ss << "Dungeon Level " << pLevel+1;					//line 5
	move(5,0);
	addstr(ss.str().c_str());

	for (size_t y = 0; y < pCharMap.size(); y++)
	{
		for (size_t x = 0; x < pCharMap[0].size(); x++)
		{
			move(y+6,x);											//line 6-26
			if (pCharMap[y][x] == '@')
			{
				addch(pCharMap[y][x] | COLOR_PAIR(3) | A_BOLD );
			} else if ((pCharMap[y][x] == 'p')||(pCharMap[y][x] == 'P')||(pCharMap[y][x] == 'f')||(pCharMap[y][x] == 'F')) {	//pPfF
				addch(pCharMap[y][x] | COLOR_PAIR(2) );
			} else if ((pCharMap[y][x] == 'l')||(pCharMap[y][x] == '9')||(pCharMap[y][x] == '1')||(pCharMap[y][x] == '4')||(pCharMap[y][x] == '!')||(pCharMap[y][x] == '0')||(pCharMap[y][x] == '3')||(pCharMap[y][x] == '8')||(pCharMap[y][x] == '%')) {	//l914!038%
				addch(pCharMap[y][x] | COLOR_PAIR(6) );
			} else if ((pCharMap[y][x] == 'k')||(pCharMap[y][x] == 'g')||(pCharMap[y][x] == 'G')||(pCharMap[y][x] == 'o')||(pCharMap[y][x] == 'O')||(pCharMap[y][x] == 'w')||(pCharMap[y][x] == 'W')||(pCharMap[y][x] == 'd')||(pCharMap[y][x] == 'D')||(pCharMap[y][x] == 'B')) {	//kgGoOwWdDB
				addch(pCharMap[y][x] | COLOR_PAIR(1) );
			} else if (pCharMap[y][x] == '?') {
				addch(pCharMap[y][x] | COLOR_PAIR(5) | A_BOLD );
			} else if (pCharMap[y][x] == '$') {
				addch(pCharMap[y][x] | COLOR_PAIR(4) | A_BOLD );
			} else {
				addch(pCharMap[y][x]);
			}
		}
	}

	ss.str("");
	ss << "Equipped Items:   ";									//line 27
	vector<string> equippedList = nowUsing();
	if (equippedList.size() > 0)
	{
		for (size_t i = 0; i < equippedList.size(); i++)
		{
			ss << equippedList[i] << "   ";
		}
	} else {
		ss << "(none)";
	}
	move(27,0);
	addstr(ss.str().c_str());

	ss.str("");
	ss << "Use keypad to navigate, 'p' to pickup, 'u' to use, 'd' to drop, and 'q' to quit";		//line 28
	move(28,0);
	addstr(ss.str().c_str());

	ss.str("");
	ss << "===============================================================================";		//line 29
	move(29,0);
	addstr(ss.str().c_str());

	move(31,0);
}



void Player::pickUp(Item * pItem)
{
	int yLine;
	int xLine;
	getyx(stdscr,yLine,xLine);
	
	stringstream ss;
	bool flag = true;
	for (size_t i = 0; i < inventory.size(); i++)
	{
		if ( pItem->getSymbol() == inventory[i]->getSymbol() )
		{
			if (dynamic_cast<Consumable*>(pItem) != NULL) {
				dynamic_cast<Consumable*>(inventory[i]) -> setQuantity(dynamic_cast<Consumable*>(inventory[i])->getQuantity() + dynamic_cast<Consumable*>(pItem)->getQuantity());
				ss.str("");
				ss << "You found a " << pItem->getName() << ". Updated inventory quantity.";
				addstr(ss.str().c_str());
				yLine++;
				move(yLine,0);
				flag = false;
				break;
			} else {
				ss.str("");
				ss << "You found a " << pItem->getName() << ". ... you already have that.";
				addstr(ss.str().c_str());
				yLine++;
				move(yLine,0);
				flag = false;
				break;
			}
		}
	}

	if (flag == true)
	{
		if (equipped[0] != NULL)
		{
			if (pItem->getSymbol() == equipped[0]->getSymbol())
			{
				ss.str("");
				ss << "You found a " << pItem->getName() << ". ... you already have that.";
				addstr(ss.str().c_str());
				yLine++;
				move(yLine,0);
				flag = false;
			}
		}
		if (equipped[1] != NULL)
		{
			if (pItem->getSymbol() == equipped[1]->getSymbol())
			{
				ss.str("");
				ss << "You found a " << pItem->getName() << ". ... you already have that.";
				addstr(ss.str().c_str());
				yLine++;
				move(yLine,0);
				flag = false;
			}
		}
		if (equipped[2] != NULL)
		{
			if (pItem->getSymbol() == equipped[2]->getSymbol())
			{
				ss.str("");
				ss << "You found a " << pItem->getName() << ". ... you already have that.";
				addstr(ss.str().c_str());
				yLine++;
				move(yLine,0);
				flag = false;
			}
		}
	}

	if (flag == true)
	{
		inventory.push_back(pItem);
		ss.str("");
		ss << "You found a " << pItem->getName() << "!";
		addstr(ss.str().c_str());
		yLine++;
		move(yLine,0);

		if (dynamic_cast<Equipment*>(pItem) != NULL)
		{
			int slot = dynamic_cast<Equipment*>(pItem)->getSlot();
			if (equipped[0] == NULL)
			{
				if (slot == 0)
				{
					equipped[0] = dynamic_cast<Armor*>(pItem);
					equipArmor();
					inventory.pop_back();
					ss.str("");
					ss << " ... it is now equipped.";
					addstr(ss.str().c_str());
					yLine++;
					move(yLine,0);
				}
			}
			if (equipped[1] == NULL)
			{
				if (slot == 1)
				{
					equipped[1] = dynamic_cast<Weapon*>(pItem);
					equipWeapon();
					inventory.pop_back();
					ss.str("");
					ss << " ... it is now equipped.";
					addstr(ss.str().c_str());
					yLine++;
					move(yLine,0);
				}
			}
			if (equipped[2] == NULL)
			{
				if (slot == 2)
				{
					equipped[2] = dynamic_cast<Equipment*>(pItem);
					key = true;
					inventory.pop_back();
					ss.str("");
					ss << " ... it is now equipped.";
					addstr(ss.str().c_str());
					yLine++;
					move(yLine,0);
				}
			}
		}
	}
}

void Player::use(vector<vector<char>> pCharMap, int pLevel)
{
	playerMap(pCharMap, pLevel);
	move(33,0);
	getInventory();
	move(31,0);
	
	stringstream ss;

	if (inventory.size() > 0)
	{
		ss.str("");
		ss << "Select Item to use: (enter a number between 1 and " << inventory.size() << ", then press ENTER) ";
		addstr(ss.str().c_str());

		refresh();
		char aString[78];
		getstr(aString);
		clear();

		move(33,0);

		int selection = atoi(aString);

		if ((selection < 1) || (selection > inventory.size())) 
		{
			ss.str("");
			ss << "That is not a valid selection.";
			addstr(ss.str().c_str());
		} else {
			selection--;
			if (dynamic_cast<Equipment*>(inventory[selection]) != NULL)
			{
				int slot = dynamic_cast<Equipment*>(inventory[selection])->getSlot();
				Item * temp;
				if (slot == 0)
				{
					temp = equipped[0];
					equipped[0] = dynamic_cast<Equipment*>(inventory[selection]);
					ss.str("");
					ss << equipped[0]->getName() << " equipped.";
					addstr(ss.str().c_str());
					equipArmor();
					inventory[selection] = temp;
				} else if (slot == 1) {
					temp = equipped[1];
					equipped[1] = dynamic_cast<Equipment*>(inventory[selection]);
					ss.str("");
					ss << equipped[1]->getName() << " equipped.";
					addstr(ss.str().c_str());
					equipWeapon();
					inventory[selection] = temp;
				} else if (slot == 2) {
					temp = equipped[2];
					equipped[2] = dynamic_cast<Equipment*>(inventory[selection]);
					ss.str("");
					ss << equipped[2]->getName() << " equipped.";
					addstr(ss.str().c_str());
					inventory[selection] = temp;
				}
			} else {
				int boost = dynamic_cast<Consumable*>(inventory[selection])->getValue();
				if ( (getHealth()+boost) < max_health )
				{
					setHealth(getHealth()+boost);
					ss.str("");
					ss << "You are feeling restored!";
					addstr(ss.str().c_str());
				} else {
					setHealth(max_health);
					ss.str("");
					ss << "Your health is completely full.";
					addstr(ss.str().c_str());
				}
				if (dynamic_cast<Consumable*>(inventory[selection])->getQuantity() > 1)
				{
					dynamic_cast<Consumable*>(inventory[selection])->setQuantity( dynamic_cast<Consumable*>(inventory[selection])->getQuantity() - 1 );
				} else {
					inventory[selection] = NULL;
					inventory.erase(inventory.begin() + (selection));
				}
			}
		}
	} else {
		ss.str("");
		ss << "You have nothing in your inventory...";
		addstr(ss.str().c_str());
	}
}

void Player::getInventory()
{
	int yLine;
	int xLine;
	getyx(stdscr,yLine,xLine);

	stringstream ss;

	ss.str("");
	ss << "Current Inventory: ";
	addstr(ss.str().c_str());
	yLine++;
	move(yLine,0);

	for (size_t i = 0; i < inventory.size(); i++)
	{
		if (inventory[i] != NULL)
		{
			ss.str("");
			ss << i+1 << ": " << inventory[i]->getName();
			if (dynamic_cast<Consumable*>(inventory[i]) != NULL)
			{
				if (dynamic_cast<Consumable*>(inventory[i])->getQuantity() > 1)
				{
					ss << " (x" << dynamic_cast<Consumable*>(inventory[i])->getQuantity() << ")";
				}
			}

			addstr(ss.str().c_str());
			if ((i == 4)||(i == 8))
			{
				xLine += 26;
				yLine = 34;
			} else {
				yLine++;
			}
			move(yLine,xLine);
		}
	}
}

Item * Player::drop(vector<vector<char>> pCharMap, int pLevel)
{
	playerMap(pCharMap, pLevel);
	move(33,0);
	getInventory();
	move(31,0);
	
	stringstream ss;
	Item * temp = NULL;
	
	if (inventory.size() > 0)
	{
		ss.str("");
		ss << "Select Item to drop: (enter a number between 1 and " << inventory.size() << ", then press ENTER) ";
		addstr(ss.str().c_str());
		
		refresh();
		char aString[78];
		getstr(aString);
		clear();

		move(33,0);

		int selection = atoi(aString);

		if ((selection < 1) || (selection > inventory.size())) {
			ss.str("");
			ss << "That is not a valid selection.";
			addstr(ss.str().c_str());
		} else {
			selection--;
			temp = inventory[selection];
			ss.str("");
			ss << "You dropped a " << temp->getName() << ".";
			addstr(ss.str().c_str());
			inventory.erase(inventory.begin() + (selection));
		}
	} else {
		ss.str("");
		ss << "You have nothing in your inventory...";
		addstr(ss.str().c_str());
	}
	return temp;
}

void Player::equipArmor()
{
	if (equipped[0] != NULL)
	{
		defense_stats = dynamic_cast<Armor*>(equipped[0])->getValue();
		defense_bonus = dynamic_cast<Armor*>(equipped[0])->getDefenseBonus();
		setDefense( defense_stats, defense_bonus);
	}
}

void Player::equipWeapon()
{
	if (equipped[1] != NULL)
	{
		attack_stats = dynamic_cast<Weapon*>(equipped[1])->getValue();
		attack_bonus = dynamic_cast<Weapon*>(equipped[1])->getAttackBonus();
		setAttack( attack_stats, attack_bonus);
	}
}

vector<string> Player::nowUsing()
{
	vector<string> equippedList;
	for (size_t i = 0; i < equipped.size(); i++)
	{
		if (equipped[i] != NULL)
		{
			equippedList.push_back( equipped[i]->getName() );
		}
	}
	return equippedList;
}

void Player::attack(Character & target)
{
	int yLine;
	int xLine;
	getyx(stdscr,yLine,xLine);

	stringstream ss;

	ss.str("");
	ss << "Round 0: " << "Your health is " << getHealth() << ", " << target.getName() << "'s is " << target.getHealth() << ".";
	addstr(ss.str().c_str());
	setDeath(ss.str());
	yLine++;
	move(yLine,0);

	int round = 1;
	int newHealth;
	while ( (target.getHealth() > 0) && (getHealth() > 0) )
	{
		target.setHealth( target.getHealth() - getAttack() );
		newHealth = ( getHealth() + getDefense() - Tools::randomValue(target.getStats()) );
		if (newHealth < getHealth())
		{
			setHealth(newHealth);
		}
		ss.str("");
		ss << "Round " << round << ": " << "Your health is " << getHealth() << ", " << target.getName() << "'s is " << target.getHealth() << ".";
		addstr(ss.str().c_str());
		setDeath(ss.str());
		yLine++;
		move(yLine,0);
		round++;
	}
	setDeath(" ");
	setDeath("You should have left well-enough alone ... because now you're dead.");
}


void Player::dumpObject()
{
	cout << "Player:" << endl;
	dumpObjectData();
}

void Player::dumpObjectData()
{
	Character::dumpObjectData();
	cout << "         Level: " << getLevel() << endl;
	cout << "         Score: " << getScore() << endl;
}

void Player::writeFragment(ostream & output)
{
	output << " <Player>";
	writeDataAsFragment(output);
	output << " </Player>"
		<< endl;
}

void Player::writeDataAsFragment(ostream & output)
{
	Character::writeDataAsFragment(output);
	output << "   <experience>"
		<< getExperience()
		<< "</experience>"
		<< endl
		<< "   <level>"
		<< getLevel()
		<< "</level>"
		<< endl;
}

void Player::setElementData(string sElementName, string sValue)
{
	Character::setElementData(sElementName, sValue);
	int iValue = atoi(sValue.c_str());
	if (sElementName == "experience")
	{
		setExperience(iValue);
	} else if (sElementName == "level") {
		setLevel(iValue);
	}
}
 

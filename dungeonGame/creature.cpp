#include <ncurses.h>
#include "Creature.h"
#include "Tools.h"
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

Creature::Creature()
{
	crea_hostility = false;
}

void Creature::setHostility(bool new_crea_hostility)
{
	crea_hostility = new_crea_hostility;
}

bool Creature::getHostility()
{
	return crea_hostility;
}

void Creature::attack(Character & target)
{
	int yLine;
	int xLine;
	getyx(stdscr,yLine,xLine);

	stringstream ss;

	ss.str("");
	ss << "Round 0: " << "Your health is " << target.getHealth() << ", " << getName() << "'s is " << getHealth() << ".";
	addstr(ss.str().c_str());
	target.setDeath(ss.str());
	yLine++;
	move(yLine,0);

	int round = 1;
	int newHealth;
	while ( (target.getHealth() > 0) && (getHealth() > 0) )
	{
		newHealth = ( target.getHealth() + target.getDefense() - Tools::randomValue(getStats()) );
		if (newHealth < target.getHealth())
		{
			target.setHealth(newHealth);
		}
		setHealth( getHealth() - target.getAttack() );
		ss.str("");
		ss << "Round " << round << ": Your health is " << target.getHealth() << ", " << getName() << "'s is " << getHealth() << ".";
		addstr(ss.str().c_str());
		target.setDeath(ss.str());
		yLine++;
		move(yLine,0);
		round++;
	}
	target.setDeath(" ");
	target.setDeath("And now you're dead. Didn't see that one coming, did ya'?");
}

void Creature::dumpObject()
{
	cout << "Creature:" << endl;
	dumpObjectData();
}

void Creature::dumpObjectData()
{
	Character::dumpObjectData();
	if (getHostility())
	{
		cout << "       Hostile: true" << endl;
	} else {
		cout << "       Hostile: false" << endl;
	}
	
}

void Creature::writeFragment(ostream & output)
{
	output << " <Creature>";
	writeDataAsFragment(output);
	output << " </Creature>"
		<< endl;
}

void Creature::writeDataAsFragment(ostream & output)
{
	Character::writeDataAsFragment(output);
	output << "   <hostile>";
	if (getHostility())
	{
		output << "true";
	} else {
		output << "false";
	}
	output << "</hostile>"
		<< endl;
}

void Creature::setElementData(string sElementName, string sValue)
{
	Character::setElementData(sElementName, sValue);
	if (sElementName == "hostile")
	{
		if (sValue[0] == 't')
		{
			setHostility(true);
		} else {
			setHostility(false);
		}
	}
}
 

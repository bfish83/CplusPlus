#include "Character.h"
#include "Tools.h"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

Character::Character()
{
	char_health = 0;
	char_stats = 0;
	a_stats = 0;
	a_bonus = 0;
	d_stats = 0;
	d_bonus = 0;
}

void Character::setHealth(int new_char_health)
{
	char_health = new_char_health;
}

void Character::setStats(int new_char_stats)
{
	char_stats = (new_char_stats);
}

int Character::getHealth()
{
	return char_health;
}

int Character::getStats()
{
	return char_stats;
}


void Character::setAttack(int newAttack, int bonus)
{
	a_stats = newAttack;
	a_bonus = bonus;
}

void Character::setDefense(int newDefense, int bonus)
{
	d_stats = newDefense;
	d_bonus = bonus;
}

int Character::getAttack()
{
	return (Tools::randomValue(char_stats+a_stats) + a_bonus);
}

int Character::getDefense()
{
	return (Tools::randomValue(d_stats) + d_bonus);
}

void Character::clearDeath()
{
	vector<string> empty;
	death = empty;
}

void Character::setDeath(string message)
{
	death.push_back(message);
}

vector<string> Character::getDeath()
{
	return death;
}

void Character::dumpObject()
{
	cout << "Character:" << endl;
	dumpObjectData();
}

void Character::dumpObjectData()
{
	Entity::dumpObjectData();
	cout << "        Health: " << getHealth() << endl;
}

void Character::writeFragment(ostream & output)
{
	output << " <Character>";
	writeDataAsFragment(output);
	output << " </Character>"
		<< endl;
}

void Character::writeDataAsFragment(ostream & output)
{
	Entity::writeDataAsFragment(output);
	output << "   <health>"
		<< getHealth()
		<< "</health>"
		<< endl;
}

void Character::setElementData(string sElementName, string sValue)
{
	Entity::setElementData(sElementName, sValue);
	int iValue = atoi(sValue.c_str());
	if (sElementName == "health")
	{
		setHealth(iValue);
		setStats(iValue);
	}
}
 

#include "Armor.h"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

Armor::Armor()
{
	a_bonus = 0;
}

void Armor::setDefenseBonus(int new_a_bonus)
{
	a_bonus = new_a_bonus;
}

int Armor::getDefenseBonus()
{
	return a_bonus;
}

void Armor::dumpObject()
{
	cout << "Armor:" << endl;
	dumpObjectData();
}

void Armor::dumpObjectData()
{
	Equipment::dumpObjectData();
	cout << " Defense Bonus: " << getDefenseBonus() << endl;
}

void Armor::writeFragment(ostream & output)
{
	output << " <Armor>";
	writeDataAsFragment(output);
	output << " </Armor>"
		<< endl;
}

void Armor::writeDataAsFragment(ostream & output)
{
	Equipment::writeDataAsFragment(output);
	output << "   <defenseBonus>"
		<< getDefenseBonus()
		<< "</defenseBonus>"
		<< endl;
}

void Armor::setElementData(string sElementName, string sValue)
{
	Equipment::setElementData(sElementName, sValue);
	int iValue = atoi(sValue.c_str());
	if (sElementName == "defenseBonus")
	{
		setDefenseBonus(iValue);
	}
}
 

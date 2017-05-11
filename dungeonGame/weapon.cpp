#include "Weapon.h"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

Weapon::Weapon()
{
	w_type = 0;
	w_bonus = 0;
}

void Weapon::setWeaponType(int new_w_type)
{
	w_type = new_w_type;
}

void Weapon::setAttackBonus(int new_w_bonus)
{
	w_bonus = new_w_bonus;
}

int Weapon::getWeaponType()
{
	return w_type;
}

int Weapon::getAttackBonus()
{
	return w_bonus;
}

void Weapon::dumpObject()
{
	cout << "Weapon:" << endl;
	dumpObjectData();
}

void Weapon::dumpObjectData()
{
	Equipment::dumpObjectData();
	cout << "   Weapon Type: " << getWeaponType() << endl;
	cout << "  Attack Bonus: " << getAttackBonus() << endl;
}

void Weapon::writeFragment(ostream & output)
{
	output << " <Weapon>";
	writeDataAsFragment(output);
	output << " </Weapon>"
		<< endl;
}

void Weapon::writeDataAsFragment(ostream & output)
{
	Equipment::writeDataAsFragment(output);
	output << "   <weaponType>"
		<< getWeaponType()
		<< "</weaponType>"
		<< endl
		<< "   <attackBonus>"
		<< getAttackBonus()
		<< "</attackBonus>"
		<< endl;
}

void Weapon::setElementData(string sElementName, string sValue)
{
	Equipment::setElementData(sElementName, sValue);
	int iValue = atoi(sValue.c_str());
	if (sElementName == "weaponType")
	{
		setWeaponType(iValue);
	} else if (sElementName == "attackBonus") {
		setAttackBonus(iValue);
	}
}
 

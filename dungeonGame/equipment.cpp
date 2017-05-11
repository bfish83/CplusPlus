#include "Equipment.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

Equipment::Equipment()
{
	equip_slot = 0;
}

void Equipment::setSlot(int new_equip_slot)
{
	equip_slot = new_equip_slot;
}

int Equipment::getSlot()
{
	return equip_slot;
}

void Equipment::dumpObject()
{
	cout << "Equipment:" << endl;
	dumpObjectData();
}

void Equipment::dumpObjectData()
{
	Item::dumpObjectData();
	cout << "          Slot: " << getSlot() << endl;
}

void Equipment::writeFragment(ostream & output)
{
	output << " <Equipment>";
	writeDataAsFragment(output);
	output << " </Equipment>"
		<< endl;
}

void Equipment::writeDataAsFragment(ostream & output)
{
	Item::writeDataAsFragment(output);
	output << "   <slot>"
		<< getSlot()
		<< "</slot>"
		<< endl;
}

void Equipment::setElementData(string sElementName, string sValue)
{
	Item::setElementData(sElementName, sValue);
	int iValue = atoi(sValue.c_str());
	if (sElementName == "slot")
	{
		setSlot(iValue);
	}
}
 

#include "Consumable.h"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

Consumable::Consumable()
{
	con_quantity = 0;
}

void Consumable::setQuantity(int new_con_quantity)
{
	con_quantity = new_con_quantity;
}

int Consumable::getQuantity()
{
	return con_quantity;
}

void Consumable::dumpObject()
{
	cout << "Consumable:" << endl;
	dumpObjectData();
}

void Consumable::dumpObjectData()
{
	Item::dumpObjectData();
	cout << "      Quantity: " << getQuantity() << endl;
}

void Consumable::writeFragment(ostream & output)
{
	output << " <Consumable>";
	writeDataAsFragment(output);
	output << " </Consumable>"
		<< endl;
}

void Consumable::writeDataAsFragment(ostream & output)
{
	Item::writeDataAsFragment(output);
	output << "   <quantity>"
		<< getQuantity()
		<< "</quantity>"
		<< endl;
}

void Consumable::setElementData(string sElementName, string sValue)
{
	Item::setElementData(sElementName, sValue);
	int iValue = atoi(sValue.c_str());
	if (sElementName == "quantity")
	{
		setQuantity(iValue);
	}
}
 

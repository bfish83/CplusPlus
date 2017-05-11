#include "Item.h"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

Item::Item()
{
	item_value = 0;
	item_weight = 0;
}

void Item::setValue(int new_item_value)
{
	item_value = new_item_value;
}

void Item::setWeight(int new_item_weight)
{
	item_weight = new_item_weight;
}

int Item::getValue()
{
	return item_value;
}

int Item::getWeight()
{
	return item_weight;
}

void Item::dumpObject()
{
	cout << "Item:" << endl;
	dumpObjectData();
}

void Item::dumpObjectData()
{
	Entity::dumpObjectData();
	cout << "        Weight: " << getWeight() << endl;
	cout << "         Value: " << getValue() << endl;
}

void Item::writeFragment(ostream & output)
{
	output << " <Item>";
	writeDataAsFragment(output);
	output << " </Item>"
		<< endl;
}

void Item::writeDataAsFragment(ostream & output)
{
	Entity::writeDataAsFragment(output);
	output << "   <weight>"
		<< getWeight()
		<< "</weight>"
		<< endl
		<< "   <value>"
		<< getValue()
		<< "</value>"
		<< endl;
}

void Item::setElementData(string sElementName, string sValue)
{
	Entity::setElementData(sElementName, sValue);
	int iValue = atoi(sValue.c_str());
	if (sElementName == "weight")
	{
		setWeight(iValue);
	} else if (sElementName == "value") {
		setValue(iValue);
	}
}
 

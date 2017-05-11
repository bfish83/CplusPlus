#include "Entity.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

Entity::Entity()
{
	ent_name = "";
	ent_symbol;
	position.resize(2);
}

void Entity::setName(string new_ent_name)
{
	ent_name = new_ent_name;
}

void Entity::setSymbol(char new_ent_symbol)
{
	ent_symbol = new_ent_symbol;
}

void Entity::setPosition(int y, int x)
{
	position.clear();
	position.push_back(y);
	position.push_back(x);
}

string Entity::getName()
{
	return ent_name;
}

char Entity::getSymbol()
{
	return ent_symbol;
}

vector<int> Entity::getPosition()
{
	return position;
}

void Entity::dumpObject()
{
	cout << "Entity:" << endl;
	dumpObjectData();
}

void Entity::dumpObjectData()
{
	cout << "          Name: " << getName() << endl;
	cout << "        Symbol: " << getSymbol() << endl;
}

void Entity::writeFragment(ostream & output)
{
	output << " <Entity>";
	writeDataAsFragment(output);
	output << " </Entity>"
		<< endl;
}

void Entity::writeDataAsFragment(ostream & output)
{
	output << endl
		<< "   <name>"
		<< getName()
		<< "</name>"
		<< endl
		<< "   <symbol>"
		<< getSymbol()
		<< "</symbol>"
		<< endl;
}

void Entity::setElementData(string sElementName, string sValue)
{
	if (sElementName == "name")
	{
		setName(sValue);
	} else if (sElementName == "symbol") {
		setSymbol(sValue[0]);
	}
}
 

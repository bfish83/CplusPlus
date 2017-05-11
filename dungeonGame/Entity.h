#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "XMLSerializable.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Entity : public XMLSerializable {
public:
	Entity();
	~Entity() {}

	virtual void setName(string new_ent_name);
	virtual void setSymbol(char new_ent_symbol);
	void setPosition(int y, int x);

	virtual string getName();
	virtual char getSymbol();
	vector<int> getPosition();

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);

private:
	string ent_name;
	char ent_symbol;
	vector<int> position;
};

#endif
 
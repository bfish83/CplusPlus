#ifndef CREATURE_H_INCLUDED
#define CREATURE_H_INCLUDED

#include "Character.h"
#include <string>
#include <iostream>

using namespace std;

class Creature : public Character {
public:
	Creature();
	~Creature() {}

	void setHostility(bool new_crea_hostility);
	bool getHostility();

	virtual void attack(Character & target);

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);

private:
	bool crea_hostility;
};

#endif
 
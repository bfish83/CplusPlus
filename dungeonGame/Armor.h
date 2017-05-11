#ifndef ARMOR_H_INCLUDED
#define ARMOR_H_INCLUDED

#include "Equipment.h"
#include <string>
#include <iostream>

using namespace std;

class Armor : public Equipment {
public:
	Armor();
	~Armor() {}

	void setDefenseBonus(int new_a_bonus);

	int getDefenseBonus();

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);

private:
	int a_bonus;

};

#endif
 
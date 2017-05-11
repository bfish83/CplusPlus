#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

#include "Equipment.h"
#include <string>
#include <iostream>

using namespace std;

class Weapon : public Equipment {
public:
	Weapon();
	~Weapon() {}

	void setWeaponType(int new_w_type);
	void setAttackBonus(int new_w_bonus);

	int getWeaponType();
	int getAttackBonus();

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);

private:
	int w_type;
	int w_bonus;

};

#endif
 
#ifndef EQUIPMENT_H_INCLUDED
#define EQUIPMENT_H_INCLUDED

#include "Item.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Equipment : public Item {
public:
	Equipment();
	~Equipment() {}

	void setSlot(int new_equip_slot);
	int getSlot();

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);

private:
	int equip_slot;

};

#endif
 
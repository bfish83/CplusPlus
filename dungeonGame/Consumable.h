#ifndef CONSUMABLE_H_INCLUDED
#define CONSUMABLE_H_INCLUDED

#include "Item.h"
#include <string>
#include <iostream>

using namespace std;

class Consumable : public Item {
public:
	Consumable();
	~Consumable() {}

	void setQuantity(int new_con_quantity);
	int getQuantity();

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);

private:
	int con_quantity;

};

#endif
 
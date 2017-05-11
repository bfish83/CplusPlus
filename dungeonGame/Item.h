#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include "Entity.h"
#include <string>
#include <iostream>

using namespace std;

class Item : public Entity {
public:
	Item();
	~Item() {}

	void setValue(int new_item_value);
	void setWeight(int new_item_weight);

	int getValue();
	int getWeight();

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);

private:
	int item_value;
	int item_weight;

};

#endif
 
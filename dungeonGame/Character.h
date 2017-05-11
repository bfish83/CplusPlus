#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include "Entity.h"
#include <string>
#include <iostream>

using namespace std;

class Character : public Entity {
public:
	Character();
	~Character() {}
	
	void setHealth(int new_char_health);
	void setStats(int new_char_stats);

	int getHealth();
	int getStats();

	void setAttack(int newAttack, int bonus);
	void setDefense(int newDefense, int bonus);
	int getAttack();
	int getDefense();

	void clearDeath();
	void setDeath(string message);
	vector<string> getDeath();

	virtual void attack(Character & target, int yLine) {}
	
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);

private:
	int char_health;
	int char_stats;
	int a_stats;
	int a_bonus;
	int d_stats;
	int d_bonus;
	vector<string> death;
};

#endif
 
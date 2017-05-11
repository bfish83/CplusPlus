#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Character.h"
#include "Item.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Player : public Character {
public:
	Player();
	~Player() {}

	void setExperience(int new_points);
	void setLevel(int new_play_level);
	int getExperience();
	int getLevel();
	int getScore();
	int setMaxHealth(int newHealth);
	int getMaxHealth();
	int getMaxAttack();
	int getAttackBonus();
	int getMaxDefense();
	int getDefenseBonus();
	bool hasKey();
	
	void playerMap(vector<vector<char>> pCharMap, int pLevel);

	void pickUp(Item * pItem);									//p
	void use(vector<vector<char>> pCharMap, int pLevel);		//u
	void getInventory();										//i
	Item * drop(vector<vector<char>> pCharMap, int pLevel);		//d
	void equipArmor();
	void equipWeapon();
	vector<string> nowUsing();

	virtual void attack(Character & target);

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);

private:
	int play_experience;
	int play_level;
	int play_score;
	int max_health;
	int base_stats;
	int attack_stats;
	int attack_bonus;
	int defense_stats;
	int defense_bonus;
	vector<Item*> equipped;
	vector<Item*> inventory;
	bool key;
};

#endif
 
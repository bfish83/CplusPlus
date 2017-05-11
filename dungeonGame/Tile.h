#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include "Player.h"
#include "Creature.h"
#include "Item.h"
#include <vector>

using namespace std;

class Tile {
public:
	Tile();
	~Tile() {}

	void setTile(char Symbol, bool Pass);
	void setPassable(bool Pass);

	void setUnderTile(char new_char);
	void setOverTile(char new_char);

	char getTileChar();
	char getUnderTileChar();
	bool isPassable();

	void setPlayer(Player * newPlayer);
	void setCreature(Creature * newCreature);
	void setItem(Item * newItem);
	Player * getPlayer();
	Creature * getCreature();
	Item * getItem();

private:
	char underTile;
	char overTile;
	bool passable;
	Player * pPlayer;
	Creature * pCreature;
	vector<Item*> pItems;
};

#endif

#ifndef DUNGEONLEVEL_H_INCLUDED
#define DUNGEONLEVEL_H_INCLUDED

#include "Tile.h"
#include "XMLSerializable.h"
#include "Item.h"
#include "Player.h"
#include <string>
#include <vector>

using namespace std;

class DungeonLevel : public Tile {
public:
	DungeonLevel();
	~DungeonLevel() {}

	void addRoom(int y_plane, int x_min, int x_max);
	void addElement(char newTile, XMLSerializable * pObject);

	void dropItem(Item * pItem, int y, int x);
	void kill(int y,int x);
	void remove(int y, int x);

	vector<int> getUpstairs();
	vector<int> getDownstairs();
	void warp(Player * pPlayer, int y, int x);

	vector<int> findChar(char lookup);
	vector<vector<int>> findCreatures();
	void stepCreatures();
	void step(int old_y, int old_x, int new_y, int new_x);

	Tile at(int y, int x);

	vector<vector<char>> getMap();

private:
	vector<vector<Tile>> dungeonMap;
	vector<vector<char>> charMap;
	vector<int> player;
	vector<int> upstairs;
	vector<int> downstairs;
	bool moved;
};

#endif

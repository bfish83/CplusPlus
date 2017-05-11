#include "DungeonLevel.h"
#include "Tools.h"
#include "Tile.h"
#include "XMLSerializable.h"
#include "Item.h"
#include "Player.h"
#include <string>
#include <vector>
#include <cmath>

using namespace std;

DungeonLevel::DungeonLevel()
{
	moved = false;

	//dungeonLevel dimensions
	unsigned int height = 20;
	unsigned int width = 79;
	
	//make vector size of dimensions
	dungeonMap.resize(height, vector<Tile>(width, Tile()) );
	charMap.resize(height, vector<char>(width, ' '));

	//buffer for drawing tunnels, rooms (basically a spacer)
	unsigned int buffer;
	if (width >= height) {
		buffer = height/4;
	} else {
		buffer = width/4;
	}

	//create loop of tunnels
	for (size_t y=0; y < dungeonMap.size(); y++)
	{
		for (size_t x=0; x < dungeonMap[y].size(); x++)
		{
			if (y == buffer)
			{
				if ((x >= buffer) && (x < width-buffer))
				{
					dungeonMap[y][x].setTile('#',true);
				}
			} else if ((y > buffer) && (y < height-buffer-1)) {
				if ((x >= buffer) && (x < width-buffer))
				{
					dungeonMap[y][width-buffer-1].setTile('#',true);
					dungeonMap[y][width/2].setTile('#',true);
					dungeonMap[y][buffer].setTile('#',true);
				}
			} else if (y == height-buffer-1) {
				if ((x >= buffer) && (x < width-buffer))
				{
					dungeonMap[y][x].setTile('#',true);
				}
			}
		}
	}

	//create 6 random rooms
	addRoom(buffer, buffer, (buffer+(1*((width-(buffer*2))/3)))-buffer);
	addRoom(buffer, (buffer+(1*((width-(buffer*2))/3)))+buffer, (buffer+(2*((width-(buffer*2))/3)))-buffer);
	addRoom(buffer, (buffer+(2*((width-(buffer*2))/3)))+buffer, (buffer+(3*((width-(buffer*2))/3))));
	addRoom((height-buffer-1), buffer, (buffer+(1*((width-(buffer*2))/3)))-buffer);
	addRoom((height-buffer-1), (buffer+(1*((width-(buffer*2))/3)))+buffer, (buffer+(2*((width-(buffer*2))/3)))-buffer);
	addRoom((height-buffer-1), (buffer+(2*((width-(buffer*2))/3)))+buffer, (buffer+(3*((width-(buffer*2))/3))));

	//add upstairs/downstairs
	addElement('<', NULL);
	addElement('>', NULL);
}

void DungeonLevel::addRoom(int y_plane, int x_min, int x_max)
{
	unsigned int randomHeight;
	unsigned int randomWidth;
	
	//create room dimensions that are at least 34 square tiles per room (200/6) and ODDxODD, so room can be centered.
	do {
		randomHeight = Tools::randomValue(8);
		if (randomHeight%2 == 0)
			randomHeight+=1;
		randomWidth = Tools::randomValue(10);
		if (randomWidth%2 == 0)
			randomWidth+=1;
	} while (randomHeight*randomWidth < 34);

	int y_temp = y_plane;
	y_temp -= randomHeight/2;
	int y_start = y_temp;
	int y_stop = y_start+randomHeight;

	int x_temp = x_min + (Tools::randomValue(x_max - x_min));
	x_temp -= randomWidth/2;
	int x_start = x_temp;
	int x_stop = x_start+randomWidth;

	//draw room
	for (y_start; y_start < y_stop; y_start++)
	{
		for (x_start; x_start < x_stop; x_start++)
		{
			dungeonMap[y_start][x_start].setTile('.', true);
		}
		x_start = x_temp;
	}

	//change x,y start positions to original minus increment (to draw walls around room) 
	y_temp--;
	y_start = y_temp;
	y_stop++;

	x_temp--;
	x_start = x_temp;
	x_stop++;

	//draw walls
	for (x_start; x_start < x_stop; x_start++)
	{
		if (dungeonMap[y_start][x_start].isPassable() != true)
			dungeonMap[y_start][x_start].setTile('-',false);
	}
	x_start = x_temp;
	for (x_start; x_start < x_stop; x_start++)
	{
		if (dungeonMap[y_stop-1][x_start].isPassable() != true)
			dungeonMap[y_stop-1][x_start].setTile('-',false);
	}
	x_start = x_temp;
	y_start+=1;
	for (y_start; y_start < y_stop-1; y_start++)
	{
		if (dungeonMap[y_start][x_start].isPassable() != true)
			dungeonMap[y_start][x_start].setTile('|',false);
		if (dungeonMap[y_start][x_stop-1].isPassable() != true)
			dungeonMap[y_start][x_stop-1].setTile('|',false);
	}
	y_start = y_temp;
	if (dungeonMap[y_start][x_start].isPassable() != true)
		dungeonMap[y_start][x_start].setTile('+',false);
	if (dungeonMap[y_start][x_stop-1].isPassable() != true)
		dungeonMap[y_start][x_stop-1].setTile('+',false);
	if (dungeonMap[y_stop-1][x_start].isPassable() != true)
		dungeonMap[y_stop-1][x_start].setTile('+',false);
	if (dungeonMap[y_stop-1][x_stop-1].isPassable() != true)
		dungeonMap[y_stop-1][x_stop-1].setTile('+',false);

}

void DungeonLevel::addElement(char newTile, XMLSerializable * pObject)
{
	int iLimitedY = Tools::randomValue(20);
	int iLimitedX = Tools::randomValue(79);

	if ((dungeonMap[iLimitedY][iLimitedX].getUnderTileChar() == '.') && (dungeonMap[iLimitedY][iLimitedX].isPassable()))
	{
		if (newTile != ' ')
		{
			if ((dungeonMap[iLimitedY-1][iLimitedX].getUnderTileChar() != '#')
				&& (dungeonMap[iLimitedY+1][iLimitedX].getUnderTileChar() != '#')
				&& (dungeonMap[iLimitedY][iLimitedX-1].getUnderTileChar() != '#')
				&& (dungeonMap[iLimitedY][iLimitedX+1].getUnderTileChar() != '#'))
			{
				dungeonMap[iLimitedY][iLimitedX].setTile(newTile, true);
				if (newTile == '<')
				{
					upstairs.push_back(iLimitedY);
					upstairs.push_back(iLimitedX);
				} else if (newTile == '>') {
					downstairs.push_back(iLimitedY);
					downstairs.push_back(iLimitedX);
				}
			} else { 
				addElement(newTile, pObject);
			}
		} else {
			if (dynamic_cast<Player*>(pObject)!= NULL) {
				dungeonMap[iLimitedY][iLimitedX].setPlayer(dynamic_cast<Player*>(pObject));
				dynamic_cast<Player*>(pObject) -> setPosition(iLimitedY,iLimitedX);
				player = dungeonMap[iLimitedY][iLimitedX].getPlayer()->getPosition();
			} else if (dynamic_cast<Creature*>(pObject)!= NULL) {
				dungeonMap[iLimitedY][iLimitedX].setCreature(dynamic_cast<Creature*>(pObject));
				dynamic_cast<Creature*>(pObject) -> setPosition(iLimitedY,iLimitedX);
			} else if (dynamic_cast<Item*>(pObject)!= NULL) {
				dungeonMap[iLimitedY][iLimitedX].setItem(dynamic_cast<Item*>(pObject));
				dynamic_cast<Item*>(pObject) -> setPosition(iLimitedY,iLimitedX);
			}
		}
	} else { 
		addElement(newTile, pObject);
	}
}


void DungeonLevel::dropItem(Item * pItem, int y, int x)
{
	if (pItem != NULL)
	{
		dungeonMap[y][x].setItem(pItem);
		pItem -> setPosition(y,x);
	}
}

void DungeonLevel::kill(int y,int x)
{
	dungeonMap[y][x].setCreature(NULL);
}

void DungeonLevel::remove(int y, int x)
{
	dungeonMap[y][x].setItem(NULL);
}


vector<int> DungeonLevel::getUpstairs()
{
	return upstairs;
}

vector<int> DungeonLevel::getDownstairs()
{
	return downstairs;
}

void DungeonLevel::warp(Player * pPlayer, int y, int x)
{
	dungeonMap[y][x].setPlayer(pPlayer);
	pPlayer -> setPosition(y,x);
	player = pPlayer -> getPosition();
}


vector<int> DungeonLevel::findChar(char lookup)
{
	bool flag = false;
	vector<int> coordinates;
	for (size_t y=0; y < dungeonMap.size(); y++)
	{
		for (size_t x=0; x < dungeonMap[y].size(); x++)
		{
			if (dungeonMap[y][x].getTileChar() == lookup)
			 {
				 coordinates.push_back(y);
				 coordinates.push_back(x);
				 flag = true;
				 break;
			 }
		}
		if (flag)
		{
			break;
		}
	}
	return coordinates;
}

vector<vector<int>> DungeonLevel::findCreatures()
{
	vector<vector<int>> creatureCoords;
	vector<int> coordinates;
	int i = 0;
	for (size_t y=0; y < dungeonMap.size(); y++)
	{
		for (size_t x=0; x < dungeonMap[y].size(); x++)
		{
			if ((dungeonMap[y][x].getTileChar() != '@')
				&& (dungeonMap[y][x].getTileChar() != '+')
				&& (dungeonMap[y][x].getTileChar() != '|')
				&& (dungeonMap[y][x].getTileChar() != '-')
				&& (dungeonMap[y][x].getTileChar() != ' ')
				&& (dungeonMap[y][x].getTileChar() != '<')
				&& (dungeonMap[y][x].getTileChar() != '>')
				&& (dungeonMap[y][x].isPassable() == false))
			{
				coordinates.push_back(y);
				coordinates.push_back(x);
				creatureCoords.push_back(coordinates);
				coordinates.pop_back();
				coordinates.pop_back();
			}
		}
	}
	return creatureCoords;
}

void DungeonLevel::stepCreatures()
{
	vector<vector<int>> creatureCoords = findCreatures();

	int y;
	int x;
	vector<int> aCreature;

	for (size_t i = 0; i < creatureCoords.size(); i++)
	{
		aCreature = creatureCoords[i];
		y = aCreature[0];
		x = aCreature[1];
		
		int yDistance = abs(y - player[0]);
		int xDistance = abs(x - player[1]);
		moved = false;

		if ( dungeonMap[y][x].getCreature()->getHostility() )
		{
			if (yDistance > xDistance)
			{
				if (y < player[0])
				{
					step(y,x,y+1,x);
				} else if (y > player[0]) {
					step(y,x,y-1,x);
				}
				if (moved == false)
				{
					if (x < player[1])
					{
						step(y,x,y,x+1);
					} else if (x > player[1]) {
						step(y,x,y,x-1);
					}
				}
			} else {
				if (x < player[1])
				{
					step(y,x,y,x+1);
				} else if (x > player[1]) {
					step(y,x,y,x-1);
				}
				if (moved == false)
				{
					if (y < player[0] )
					{
						step(y,x,y+1,x);
					} else if (y > player[0]) {
						step(y,x,y-1,x);
					}
				}
			}
		} else {
			//random movement for non-hostile creatures
			int random = Tools::randomValue(4);
			if (random == 3)
			{
				step(y,x,y-1,x);
			} else if (random == 2) {
				step(y,x,y+1,x);
			} else if (random == 1) {
				step(y,x,y,x-1);
			} else if (random == 0) {
				step(y,x,y,x+1);
			}
		}
	}
}

void DungeonLevel::step(int old_y, int old_x, int new_y, int new_x)
{
	if (dungeonMap[new_y][new_x].isPassable())
	{
		if (dungeonMap[old_y][old_x].getPlayer() != NULL) 
		{
			dungeonMap[new_y][new_x].setPlayer(dungeonMap[old_y][old_x].getPlayer());
			dungeonMap[new_y][new_x].getPlayer()->setPosition(new_y,new_x);
			player = dungeonMap[new_y][new_x].getPlayer()->getPosition();
			dungeonMap[old_y][old_x].setPlayer(NULL);
		} else if (dungeonMap[old_y][old_x].getCreature() != NULL) {
			if ((dungeonMap[new_y][new_x].getUnderTileChar() != '<') && (dungeonMap[new_y][new_x].getUnderTileChar() != '>'))
			{
				dungeonMap[new_y][new_x].setCreature(dungeonMap[old_y][old_x].getCreature());
				dungeonMap[new_y][new_x].getCreature()->setPosition(new_y,new_x);
				dungeonMap[old_y][old_x].setCreature(NULL);
				moved = true;
			}
		}
	}
}


Tile DungeonLevel::at(int y, int x)
{
	return dungeonMap[y][x];
}

vector<vector<char>> DungeonLevel::getMap()
{
	for (size_t y=0; y < dungeonMap.size(); y++)
	{
		for (size_t x=0; x < dungeonMap[y].size(); x++)
		{
			charMap[y][x] = dungeonMap[y][x].getTileChar();
		}
	}
	return charMap;
}

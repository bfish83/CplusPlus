#include "Tile.h"
#include "Player.h"
#include "Creature.h"
#include "Item.h"
#include <vector>

using namespace std;

Tile::Tile()
{
	underTile = ' ';
	overTile = ' ';
	passable = false;
	pPlayer = NULL;
	pCreature = NULL;
}

void Tile::setTile(char Symbol, bool Pass)
{
	underTile = Symbol;
	passable = Pass;
	overTile = underTile;
}


void Tile::setPassable(bool Pass)
{
	passable = Pass;
}

void Tile::setUnderTile(char new_char)
{
	underTile = new_char;
}

void Tile::setOverTile(char new_char)
{
	overTile = new_char;
}


char Tile::getTileChar()
{
	return overTile;
}

char Tile::getUnderTileChar()
{
	return underTile;
}

bool Tile::isPassable()
{
	return passable;
}


void Tile::setPlayer(Player * newPlayer)
{
	pPlayer = newPlayer;
	if (pPlayer != NULL)
	{
		overTile = pPlayer->getSymbol();
		passable = false;
	} else {
		if (pItems.size() > 0)
		{
			overTile = pItems[pItems.size()-1]->getSymbol();
			passable = true;
		} else {
			overTile = underTile;
			passable = true;
		}
	}
}

void Tile::setCreature(Creature * newCreature)
{
	pCreature = newCreature;
	if (pCreature != NULL)
	{
		overTile = pCreature->getSymbol();
		passable = false;
	} else {
		if (pItems.size() > 0)
		{
			overTile = pItems[pItems.size()-1]->getSymbol();
			passable = true;
		} else {
			overTile = underTile;
			passable = true;
		}
	}
}

void Tile::setItem(Item * newItem)
{
	if (newItem != NULL)
	{
		pItems.push_back(newItem);
	} else {
		pItems.pop_back();
	}

	if ((pCreature == NULL) && (pPlayer == NULL))
	{
		if (pItems.size() > 0)
		{
			overTile = pItems[pItems.size()-1]->getSymbol();
		} else {
			overTile = underTile;
		}
	}
}

Player * Tile::getPlayer()
{
	return pPlayer;
}

Creature * Tile::getCreature()
{
	return pCreature;
}

Item * Tile::getItem()
{
	if (pItems.size() > 0)
	{
		return pItems[pItems.size()-1];
	} else {
		return NULL;
	}
}

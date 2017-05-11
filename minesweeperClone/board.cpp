/* Barret Fisher
 * CS 215, Spring 2013
 * Programming Assignment 4
 * 19 April, 2013
 *
 * Implementation of the MineSweeperBoard class.
 */ 
#include <iostream>
#include "board.h"
using namespace std;


//helper functions
bool** alloc_2d_array(int width, int height);
void free_2d_array(bool **array, int width, int height);


//allocate a 2D array
bool** alloc_2d_array(int width, int height)
{
	bool **array = new bool*[height];
	// For every row
	for (int rownum = 0; rownum < height; rownum++)
	{
		// mined[rownum] is a bool*
		// Allocate the row
		array[rownum] = new bool[width];
		for (int colnum = 0; colnum < width; colnum++)
		{
			array[rownum][colnum] = false;
		}
	}
	return array;
}


//free a 2D array
void free_2d_array(bool **array, int width, int height)
{
	for (int rownum = 0; rownum < height; rownum++)
	{
		delete[] array[rownum];
	}

	delete[] array;
}


// Initialize a board with a given width and height, containing the
// given number of randomly-placed mines.  Nothing should be revealed
// or flagged.  If there are more mines than spaces for them, fill
// the entire board with mines.
MineSweeperBoard::MineSweeperBoard(int board_width, int board_height, int mine_count)
	: width(board_width), height(board_height)
{
	// the data member is  bool **mined
	// pointer to pointer to a bool
	// pointer to an array of pointers to arrays of bool
	mined = alloc_2d_array(width, height);
	revealed = alloc_2d_array(width, height);
	flagged = alloc_2d_array(width, height);

	if (mine_count > width * height)
	{
		mine_count = width * height;
	}
		
	for (int i = 0; i < mine_count; i++)
	{
		int row = rand() % height;
		int col = rand() % width;

		if (mined[row][col]) {
			i--;
		} else {
			mined[row][col] = true;
		}
	}
}


// Clean up the board, freeing any dynamically allocated memory.
MineSweeperBoard::~MineSweeperBoard()
{
	free_2d_array(mined, width, height);
	free_2d_array(revealed, width, height);
	free_2d_array(flagged, width, height);
}


// Get the width of the board.
int MineSweeperBoard::get_width() const
{
	return width;
}


// Get the height of the board.
int MineSweeperBoard::get_height() const
{
	return height;
}


// Reveal a square.
// If this square wasn't already revealed, and if the number of
// adjacent mines equals the number of adjacent flags, recursively
// reveal all the surrounding squares that aren't flagged.
void MineSweeperBoard::reveal(Position p)
{
	int x = p.x();
	int y = p.y();
	int flags = 0;

	if (!revealed[y][x])
	{
		if (!flagged[y][x])
		{
			revealed[y][x] = true;
		}

		PositionList nearby = adjacent(p);
		for (int i =0; i < nearby.size(); i++)
		{
			Position neighbor = nearby.get(i);
			int new_x = neighbor.x();
			int new_y = neighbor.y();
			if (flagged[new_y][new_x])
				flags++;
		}

		if (flags == adjacent_mines(p))
		{
			for (int i = 0; i < nearby.size(); i++)
			{
				Position neighbor = nearby.get(i);
				int new_x = neighbor.x();
				int new_y = neighbor.y();
				if (!flagged[new_y][new_x])
				{
				reveal(neighbor);
				}
			}
		}
	}
}


// Put a flag on a square, or remove a flag that is
// already there.  Returns true if we placed a flag, false if
// we removed one.
bool MineSweeperBoard::flag(Position p)
{
	int x = p.x();
	int y = p.y();

	if (!flagged[y][x])
	{
		flagged[y][x] = true;
		return true;
	} else {
		flagged[y][x] = false;
		return false;
	}
}


// Return the appearance of the square (what will be
// displayed to the player) as a single character.
char MineSweeperBoard::appearance(Position p) const
{
	int x = p.x();
	int y = p.y();

	if (flagged[y][x]) {
		return '/';
	} else if (revealed[y][x]) {
		if (mined[y][x]) {
			// Boom!
			return '*';
		} else {
			// At most 8 adjacent mines, so one digit.
			int adjmines = adjacent_mines(p);
			// Convert a number to a digit character.
			return '0' + adjmines;
		}
	} else {
		// Unrevealed, unflagged.
		return '.';
	}
}


// Display the entire board to an output stream.  Prints
// a header with the column numbers, and prints the row
// number on each line.
void MineSweeperBoard::display(ostream &out) const
{
	cout << endl;

	// first row
	cout << "    |";
	if (width <= 10)
	{
		for (int i = 0; i < width; i++)
		{
			cout << "  " << i;
		}
		cout << endl;
	} else {
		for (int i = 0; i < 10; i++)
		{
			cout << "  " << i;
		}
		for (int i = 10; i < width; i++)
		{
			cout << " " << i;
		}
		cout << endl;
	}

	// second row
	cout << "----+";
	for (int i = 0; i < width; i++)
	{
		cout << "---";
	}
	cout << endl;

	// remaining rows
	if (height <= 10)
	{
		for (int i = 0; i < height; i++)
		{
			cout << "  " << i << " |";
			for (int j = 0; j < width; j++)
			{
				Position get_char(j,i);
				char mystery = appearance(get_char);
				cout << "  " << mystery;
			}
			cout << endl;
		}
	} else {
		for (int i = 0; i < 10; i++)
		{
			cout << "  " << i << " |";
			for (int j = 0; j < width; j++)
			{
				Position get_char(j,i);
				char mystery = appearance(get_char);
				cout << "  " << mystery;
			}
			cout << endl;
		}
		for (int i = 10; i < height; i++)
		{
			cout << " " << i << " |";
			for (int j = 0; j < width; j++)
			{
				Position get_char(j,i);
				char mystery = appearance(get_char);
				cout << "  " << mystery;
			}
			cout << endl;
		}
	}
	cout << endl;
}


// Returns true if the player won (every square with a mine
// is flagged, and every cell without a mine is revealed).
bool MineSweeperBoard::won() const
{
	// Check every square.  If we see a square that is mined but
	// not flagged, or unmined but not revealed, return false
	// immediately.  If we get to the end, every square is correct,
	// so the user won and we return true.
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (mined[y][x] && !flagged[y][x]) {
				return false;
			} else if (!mined[y][x] && !revealed[y][x]) {
				return false;
			}
		}
	}
	return true;
}


// Returns true if the player lost (there is a revealed
// mine).
bool MineSweeperBoard::lost() const
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (mined[y][x] && revealed[y][x]) 
			{
				return true;
			}
		}
	}
	return false;
}


// Reveal everything (losing the game in the process)
void MineSweeperBoard::give_up()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Position coordinates(x,y);
			reveal(coordinates);
			revealed[y][x] = true;
		}
	}
}


// Returns a list of all the positions adjacent to p.  If p
// is in the middle of the board, it has eight neighbors,
// but if it is on an edge or corner it will have fewer.
PositionList MineSweeperBoard::adjacent(Position p) const
{
	PositionList result;

	// Loop over the 3x3 block centered around p.
	for (int adj_y = p.y() - 1; adj_y <= p.y() + 1; adj_y++) {
		for (int adj_x = p.x() - 1; adj_x <= p.x() + 1; adj_x++) {
			// Make a position out of the new coordinates.
			Position adj(adj_x, adj_y);
			// Skip out-of-bounds squares
			if (!adj.in_bounds(width, height))
				continue;
			// Also skip the center.
			if (adj.x() == p.x() && adj.y() == p.y())
				continue;

			// If we get here, it's really adjacent, so add it to the list.
			result.push_front(adj);
		}
	}
	return result;
}


// Return the number of mines adjacent to a square.
int MineSweeperBoard::adjacent_mines(Position p) const
{
	PositionList neighbors = adjacent(p);

	// Loop over the neighbors.
	int adjacent_count = 0;
	for (int i = 0; i < neighbors.size(); i++) {
		Position adj = neighbors.get(i);
		// If it's mined, increase the count.
		if (mined[adj.y()][adj.x()])
			adjacent_count++;
	}
	return adjacent_count;
}


// Return the number of flags adjacent to a square.
int MineSweeperBoard::adjacent_flags(Position p) const
{
	PositionList neighbors = adjacent(p);

	// Loop over the neighbors.
	int adjacent_count = 0;
	for (int i = 0; i < neighbors.size(); i++) {
		Position adj = neighbors.get(i);
		// If it's flagged, increase the count.
		if (flagged[adj.y()][adj.x()])
			adjacent_count++;
	}
	return adjacent_count;
}
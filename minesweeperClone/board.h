// CS 215, Spring 2013
// Programming assignment 4
// 4 April, 2013
#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <iostream>
#include "position.h"
#include "positionlist.h"
using namespace std;

/* Class MineSweeperBoard - main driver class of game
 * Description: Creates a 2D board with random mines
 * Inputs: Takes height width and mine count parameters
 * Outputs: Places mines randomly, puts a number at positions
 *   that don't have mines.
*/
class MineSweeperBoard
{
public:

	/* MineSweeperBoard(int board_width, int board_height, int mine_count) 
     * Description: Initialize a board with a given width and height, 
	 *   containing the given number of randomly-placed mines. Nothing 
	 *   should be revealed or flagged.  If there are more mines than 
	 *   spaces for them, fill the entire board with mines.
     * Inputs: int board_width, int board_height, int mine_count
     * Outputs: Sets private variables, creates game
    */
	MineSweeperBoard(int board_width, int board_height, int mine_count);

	/* ~MineSweeperBoard() - Default destructor
     * Description: Clean up the board, freeing any dynamically allocated memory.
     * Inputs: None
     * Outputs: None
    */
	~MineSweeperBoard();

	/* get_width(), get_height() - get board size
     * Description: Get the size of the board.
     * Inputs: None
     * Outputs: Returns width, height of board as ints
    */
	int get_width() const;
	int get_height() const;

	/* reveal(Position p) - Reveal a square.
     * Description: If this square wasn't already revealed, and if 
	 *   the number of adjacent mines equals the number of adjacent 
	 *   flags, recursively reveal all the surrounding squares that 
	 *   aren't flagged.
     * Inputs: Position p
     * Outputs: None
    */
	void reveal(Position p);

	/* flag(Position p) - Place/remove flag
     * Description: Put a flag on a square, or remove a flag that 
	 *   is already there.  
     * Inputs: Position p
     * Outputs: Returns true if we placed a flag, 
	 *   false if we removed one.
    */
	bool flag(Position p);

	/* appearance(Position p) - Gets square appearance
     * Description: Return the appearance of the square (what will 
	 *   be displayed to the player) as a single character.
     * Inputs: Position p
     * Outputs: Char of square
    */
	char appearance(Position p) const;

	/* display(ostream &out) - Display the entire board to an output stream.
     * Description: Prints a header with the column numbers, and prints 
	 *   the row number on each line.
     * Inputs: cout
     * Outputs: Displays board on screen
    */
	void display(ostream &out) const;

	/* won() - Checks if player won
     * Description: Returns true if the player won (every square with a mine
	// is flagged, and every cell without a mine is revealed).
     * Inputs: None
     * Outputs: True if won, false otherwise
    */
	bool won() const;

	/* lost() - Checks if player lost
     * Description: Returns true if the player lost 
	 *   (there is a revealed mine).
     * Inputs: None
     * Outputs: True if lost, false otherwise
    */
	bool lost() const;

	/* give_up() - Displays entire board
     * Description: Reveal everything (losing the game in the process)
     * Inputs: None
     * Outputs: Displays entire board to screen
    */
	void give_up();

private:
	// Returns a list of all the positions adjacent to p.  If p
	// is in the middle of the board, it has eight neighbors,
	// but if it is on an edge or corner it will have fewer.
	PositionList adjacent(Position p) const;

	// Return the number of mines or flags adjacent to a square.
	int adjacent_mines(Position p) const;
	int adjacent_flags(Position p) const;

	// Size of the board.
	int width;
	int height;

	// Dynamically allocated 2D arrays indicating which squares are
	// revealed, which are mined, and which are flagged.
	bool **revealed;
	bool **mined;
	bool **flagged;
};
#endif

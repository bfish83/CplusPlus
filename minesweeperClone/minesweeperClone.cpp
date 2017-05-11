/* Barret Fisher
 * CS 215, Spring 2013
 * Programming Assignment 4
 * 19 April, 2013
 *
 * Minesweeper driver program.
 */ 

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "board.h"
using namespace std;

// helper function
void pause_215(bool have_newline);


/* main() - Main driver program
 * Description: Gets input from user and calls MineSweeperClass to create game
 * Inputs: Prompts user for board size and number of mines
 * Outputs: Uses MineSweeperClass to play game
*/
int main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	// welcome message
	cout << "Welcome to MineSweeper 215!" << endl;
	cout << endl;

	// initialize variables
	int board_width;
	int board_height;
	int num_mines;
	bool repeat = true;

	// TODO: Ask for the board size (between 5 and 20 in each direction)
	// and the number of mines.
	do {
		repeat = false;
		cout << "How large should the board be (width height)? ";
		cin >> board_width;
		cin >> board_height;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(200, '\n');
			repeat = true;
			cout << " Please enter two numbers separated by a space." << endl;
		} else if (board_width < 5) {
			repeat = true;
			cout << " Sorry, the width cannot be smaller than 5." << endl;
		} else if (board_width > 20) {
			repeat = true;
			cout << " Sorry, the width cannot be larger than 20." << endl;
		} else if (board_height < 5) {
			repeat = true;
			cout << " Sorry, the height cannot be smaller than 5." << endl;
		} else if (board_height > 20) {
			repeat = true;
			cout << " Sorry, the height cannot be larger than 20." << endl;
		}
	} while (repeat);

	// calculate maximum number of mines allowed
	int max_mines = board_width * board_height;
	if (max_mines > 80)
	{
		max_mines = 80;
	}

	repeat = true;
	do {
		repeat = false;
		cout << "How many mines to place (maximum " << max_mines << ")? ";
		cin >> num_mines;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(200, '\n');
			repeat = true;
			cout << " Please enter a positive number (maximum " << max_mines << "): " << endl;
		} else if (num_mines < 0 || num_mines > max_mines) {
			repeat = true;
			cout << " Please enter a positive number (maximum " << max_mines << "): " << endl;
		}
	} while (repeat);

	cout << "Beginning game!" << endl;

	// start timer
	time_t start = time(NULL);

	// Create a board of that size.
	MineSweeperBoard board(board_width, board_height, num_mines);

	while (!board.lost() && !board.won())
	{
		board.display(cout);
		// TODO: Ask the user to [R]eveal, [F]lag, or [G]ive up.
		// The first two commands also require a Position, so
		// you may need to ask for x and y coordinates as well.

		int x = 0;
		int y = 0;
		string command;

		repeat = true;
		do {
			repeat = false;
			cout << "[R]eveal, [F]lag, or [G]ive up?  ";
			cin >> command;
			if (command != "R" && command != "r" && command != "F" && command != "f" && command != "G" && command != "g")
			{
				repeat = true;
				cout <<  " Unknown command \"" << command << "\".";
			}
		} while (repeat);

		if (command != "G" && command != "g")
		{
			repeat = true;
			do {
				repeat = false;
				int x_max = board_width - 1;
				int y_max = board_height - 1;
				cout << "What position (x y)? ";
				cin >> x;
				cin >> y;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(200, '\n');
					repeat = true;
					cout << " Please enter two numbers separated by a space." << endl;
				} else if ( x < 0 || x > x_max) {
					repeat = true;
					cout << " Column " << x << " is out of bounds!" << endl;
				} else if ( y < 0 || y > y_max) {
					repeat = true;
					cout << " Row " << y << " is out of bounds!" << endl;
				}
			} while (repeat);
		}

		// TODO: Then perform that command by calling the appropriate
		// method.
		Position coordinates(x,y);
		if (command == "R" || command == "r")
		{
			board.reveal(coordinates);
		} else if (command == "F" || command == "f") {
			board.flag(coordinates);
		} else {
			board.give_up();
		}
	}

	// stop timer
	time_t finish = time(NULL);

	// if lost, reveal entire board
	if (board.lost())
	{
		board.give_up();
	}

	// display board
	board.display(cout);
	
	// TODO: Tell the user whether they won or lost.
	if (board.won())
	{
		cout << "*** Congratulations, you won! ***" << endl;	
	} else {
		cout << "*** Condolences, you have lost the game :( ***" << endl;	
	}

	// TODO: Compute and display how much time the game took.
	time_t game_time = finish - start;
	cout << "Your game took " << game_time << " seconds." << endl;

	pause_215(true);
	return 0;
}


/* pause_215() - Wait for the user to press ENTER.
*
* Description: 
*   Optionally read and discard the remainder of the user's last
*   line of input.  Then, prompt the user to press ENTER, then
*   read and discard another line of input.
*
* Inputs:
*   bool have_newline:
*     True if the user has already entered a newline that the
*     program has not yet read.  If true, this function first
*     discards remaining input up to and including that newline.
*
*   Reads two lines from standard input if have_newline is true,
*   one line if it is false.  Lines are assumed to be less than
*   two hundred characters long.
*
* Outputs:
*   No return value.
*
*   Prints a prompt to standard output.
*
* Notes:
*   This function is intended to be used at the end of a program,
*   just before returning from main().  Reading another line of
*   input prevents the console window from closing immediately.
*
*   In general, have_newline should be true if the last user input
*   from cin used the extraction operator (>>), and false if there
*   has been no user input or if the last input used getline().
*/
void pause_215(bool have_newline)
{
    if (have_newline) {
        // Ignore the newline after the user's previous input.
        cin.ignore(200, '\n');
    }

    // Prompt for the user to press ENTER, then wait for a newline.
    cout << endl << "Press ENTER to continue." << endl;
    cin.ignore(200, '\n');
}

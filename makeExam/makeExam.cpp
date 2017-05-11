/* Barret Fisher
 * CS 215, Spring 2013
 * Programming Assignment 3 - http://www.cs.uky.edu/~neil/215/pa/3/
 * 3 April, 2013
 *
 * Driver program for Exam and Question classes.
 */ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "exam.h"

using namespace std;

// Prototypes for non-member functions.
void pause_215(bool have_newline);
string check_filename();

// Non-member functions.

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

/* check_filename() - checks to make sure filename valid
 * Description: Prompts user for a filename, if its good it returns it,
 *   if aborted it returns empty string
 * Inputs: None
 * Outputs: Filename string, either good or bad
*/
string check_filename()
{
	//create strings
	string filename;
	string answer;

	//create flag
	bool flag = true;

	do {

		flag = false;

		//prompt for filename
		cout << "Please enter the name of the question pool file: ";
		cin >> filename;
		
		//open file to check
		ifstream in_file;
		in_file.open(filename.c_str());
	
		//check filename for errors
		if (in_file.fail())
		{
			cin.clear();
			cout << "That is a bad filename." << endl;
			cout <<  "Do you wish to try again? (Enter 'y' for yes, 'n' for no) ";
			cin >> answer;
			if (answer != "y")
			{
				filename = "";
			} else
			{
				cout << endl;
				flag = true;
			}
		}

		// closes stream
		in_file.close();

	} while (flag);

	return filename;
}

/* main() - Main driver program
 * Description: Calls functions and exam class to create exam based on user input
 * Inputs: Prompts user for num of questions, min chapter, max chapter and where to save files.
 * Outputs: Calls write functions from exam class to write exam and key to file
*/
int main()
{
	cout << "C++ Exam Creator 2013 by Barret Fisher" << endl;
	cout << endl;
	
	// check filename
	string filename = check_filename();

	// if filename good (bigger than 0)...
	if (filename.length() > 0)
	{
		cout << "Checking file: correct!" << endl;
		cout << endl;

		// creates arguments for calling exam class
		int num_questions;
		int min_chapter;
		int max_chapter;

		// do while loops do error checking on user input
		bool flag = true;
		do {
			flag = false;
			do {
				flag = false;
				cout << "How many questions should the exam have? ";
				cin >> num_questions;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(200, '\n');
					cout << "Please enter a positive number." << endl;
					cout << endl;
					flag = true;
				} else if (num_questions < 1)
				{
					cout << "Please enter a positive number." << endl;
					cout << endl;
					flag = true;
				}
			} while(flag);

			do {
				flag = false;
				cout << "What is the minimum chapter to cover in the exam? ";
				cin >> min_chapter;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(200, '\n');
					cout << "Please enter a positive number." << endl;
					cout << endl;
					flag = true;
				} else if (min_chapter < 1)
				{
					cout << "Please enter a positive number." << endl;
					cout << endl;
					flag = true;
				}
			} while(flag);
				
			do {
				flag = false;
				cout << "What is the maximum chapter to cover in the exam? ";
				cin >> max_chapter;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(200, '\n');
					cout << "Please enter a positive number." << endl;
					cout << endl;
					flag = true;
				} else if (max_chapter < 1)
				{
					cout << "Please enter a positive number." << endl;
					cout << endl;
					flag = true;
				} else if (max_chapter < min_chapter)
				{
					max_chapter = 0;
					cout << "Sorry, the maximum chapter cannot be smaller than the minimum." << endl;
					cout << endl;
					flag = true;
				} 
			} while(flag);

			// creates test exam to check number of questions
			Exam testExam(num_questions,min_chapter,max_chapter);
			int length = testExam.read_questions(filename);
				
			if (length < num_questions)
			{
				cout << "Sorry, there aren't enough questions from those chapters." << endl;
				cout << endl;
				flag = true;
			}
		} while(flag);

		cout << endl;
		cout << "Generating exam: selected "<< num_questions << " questions." << endl;
		cout << endl;

		// uses valid user input to create exam
		Exam newExam(num_questions,min_chapter,max_chapter);
		newExam.read_questions(filename);

		// creates strings for saving files
		string exam_name;
		string exam_key_name;
		
		// prompts user for string names (has default values for no input)
		string input;
		cout << "Where should I save the exam (default exam.txt): ";
		cin.ignore();
		getline(cin, input);
		if (!input.empty()) {
			exam_name = input;
		} else {
			exam_name = "exam.txt";
		}

		cout << "Where should I save the key (default key.txt): ";
		getline(cin, input);
		if (!input.empty())
		{
			exam_key_name = input;
		} else {
			exam_key_name = "key.txt";
		}
		
		// writes exam/key to selected filenames
		newExam.write_exam(exam_name);
		newExam.write_key(exam_key_name);

		cout << endl;
		cout << "Wrote exam to " << exam_name << endl;
		cout << "Wrote key to " << exam_key_name << endl;

	} else { 
		// if filename invalid ( length is 0 ), ends program
		pause_215(true);
		return 0;
	}

	//ends program
	pause_215(false);
	return 0;
}
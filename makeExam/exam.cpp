/* Barret Fisher
 * CS 215, Spring 2013
 * Programming Assignment 3
 * 3 April, 2013
 *
 * Implementation of the Exam class.
 */ 

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "exam.h"

Exam::Exam(int num_questions, int min_chapter, int max_chapter)
{
	e_numquestions = num_questions;
	e_minchapter = min_chapter;
	e_maxchapter = max_chapter;
}

Exam::~Exam()
{
	for (unsigned int i = 0; i < question_list.size(); i ++)
	{
		delete question_list[i];
	}
}



int Exam::read_questions(string filename)
{
	ifstream infile;

	infile.open(filename.c_str());

	while (infile.good())
	{
		string line;

		// read a line from the pool file
		getline(infile, line);

		if (line != "")
		{

			// get the pointer of the newly created object
			Question* currentPointer = parse_question(line);

			// check if the pointer is NULL
			if (currentPointer != NULL)
				question_list.push_back(currentPointer);
		}
	}

	// copy the content of question_list to shuffled_list (in case you don't want to shuffle the Question pointers)
	shuffled_list = question_list;
	infile.close();

	shuffle();

	while (shuffled_list.size() > e_numquestions)
	{
		shuffled_list.pop_back();
	}

	return shuffled_list.size();
}



void Exam::shuffle()
{
	// set the randomization seed
	srand((unsigned int) time(NULL));

	// get the number of questions in pool (vector)
	int numQuestionsinPool = question_list.size();

	// remove the elements from shuffled_list vector
	shuffled_list.clear();

	// populate the temporary vector with NULL's
	for (int i = 0; i < numQuestionsinPool; i ++)
		shuffled_list.push_back(NULL);

	for (int i = 0; i < numQuestionsinPool; i ++)
	{
		int index;

		// find a slot that is available (not filled with an existing pointer)
		while(1)
		{
			index = rand() % numQuestionsinPool;

			if (shuffled_list[index] == NULL)
				break; // a valid slot is found
		}

		shuffled_list[index] = question_list[i];
	}
}




void Exam::write_exam(string filename) const
{
	ofstream outfile;

	outfile.open(filename.c_str());

	for (unsigned int j = 0; j < shuffled_list.size(); j ++)
	{
		// output the question number
		outfile << j + 1 << ". ";

		// call the method on the current pointer
		shuffled_list[j] -> write(outfile);

		outfile << endl;
	}

	outfile.close();
}

void Exam::write_key(string filename) const
{
	ofstream outfile;

	outfile.open(filename.c_str());

	for (unsigned int j = 0; j < shuffled_list.size(); j ++)
	{
		outfile << j + 1 << ". ";

		shuffled_list[j] -> write_key(outfile);

		outfile << endl;
	}

	outfile.close();
}






// Split a string on the @ character.  Returns a vector of the parts, in order.
vector<string> Exam::split_string(string input)
{
	vector<string> pieces;

	// Start of the current field
	int field_start = 0;

	// Location of the next at sign.
	int next_at;
	do {
		// Find the @.  Returns the index, or string::npos if it wasn't
		// found.
		next_at = input.find('@', field_start);

		// If it wasn't found, add the last piece.
		if (next_at == string::npos)
			pieces.push_back(input.substr(field_start));
		// Or it was found, so add this piece
		else
			pieces.push_back(input.substr(field_start, next_at - field_start));

		// The next field starts just after the @
		field_start = next_at + 1;

		// If there was no @, we're done.
	} while(next_at != string::npos);

	return pieces;
}

// Convert a line from the question pool into a pointer to the
// correct kind of question object.
Question* Exam::parse_question(string line)
{
	string type, text;
	int points, chapter;

	vector<string> fields = split_string(line);

	type = fields[0];

	// Convert the integer fields.
	istringstream iss(fields[1]);
	iss >> points;
	iss.str(fields[2]);
	iss.clear();
	iss >> chapter;

	text = fields[3];

	for (int k = e_minchapter; k <= e_maxchapter; k++)
	{
		if (chapter == k)
		{
			// Now use the type to convert the rest.
			if (type == "short") {
				// Everything else is an answer.
				vector<string> answers;
				for (unsigned int i=4; i<fields.size(); i++)
					answers.push_back(fields[i]);
				return new ShortAnswerQ(points, chapter, text, answers);
			} else if (type == "long") {
				string answer = fields[4];
				return new LongAnswerQ(points, chapter, text, answer);
			} else if (type == "code") {
				vector<string> answers;
				for (unsigned int i=4; i<fields.size(); i++)
					answers.push_back(fields[i]);
				return new CodeQ(points, chapter, text, answers);
			} else if (type == "multiple") {
				int numchoices = stoi(fields[4]);
				string tocopy = fields[5];
				char correct = tocopy[0];	
				vector<string> choices;
				for (unsigned int i=6; i<fields.size(); i++)
					choices.push_back(fields[i]);
				return new MultipleChoiceQ(points, chapter, text, numchoices, correct, choices);
			}
		}
	}
	return NULL;
}
/* Barret Fisher
 * CS 215, Spring 2013
 * Programming Assignment 3
 * 3 April, 2013
 *
 * Implementation of the CodeQ class.
 */ 

#include "codeq.h"

CodeQ::CodeQ(int points, int chapter, string text, vector<string> answers)
	: Question(points, chapter, text)
{
	q_answers = answers;
}


void CodeQ::write(ostream &out) const
{
	// Write:
	// (N points) question
	// __________________________________________________________ etc

	Question::write(out);
	out << endl;
	out << "__________________________________________________________" << endl;
	out << "__________________________________________________________" << endl;
	out << "__________________________________________________________" << endl;
	out << "__________________________________________________________" << endl;
	out << "__________________________________________________________" << endl;
	out << "__________________________________________________________" << endl;
	out << endl;
	out << endl;
}

void CodeQ::write_key(ostream &out) const
{
	// Write:
	// (N points)
	// answer
	Question::write_key(out);
	out << endl;
	for (int i = 0; i < q_answers.size(); i++)
	{
		out << "    " << q_answers.at(i) << endl;
	}
	out << endl;
	out << endl;
}
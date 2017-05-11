/* Barret Fisher
 * CS 215, Spring 2013
 * Programming Assignment 3
 * 3 April, 2013
 *
 * Implementation of the LongAnswerQ class.
 */ 

#include "longanswerq.h"

LongAnswerQ::LongAnswerQ(int points, int chapter, string text, string answer)
	: Question(points, chapter, text)
{
	q_answer = answer;
}

void LongAnswerQ::write(ostream &out) const
{
	// Write:
	// (N points) question text
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

void LongAnswerQ::write_key(ostream &out) const
{
	// Write:
	// (N points)
	// answer
	Question::write_key(out);
	out << endl;
	out << "    " << q_answer << endl;
	out << endl;
	out << endl;
}
/* Barret Fisher
 * CS 215, Spring 2013
 * Programming Assignment 3
 * 3 April, 2013
 *
 * Implementation of the ShortAnswerQ class.
 */ 

#include "shortanswerq.h"

ShortAnswerQ::ShortAnswerQ(int points, int chapter, string text, vector<string> answers)
	: Question(points, chapter, text)
{
	q_answers = answers;
}



void ShortAnswerQ::write(ostream &out) const
{
	// Write:
	// (N points) question text
	// ______________________________

	Question::write(out);
	out << endl;
	out << "______________________________" << endl;
	out << endl;
	out << endl;

}

void ShortAnswerQ::write_key(ostream &out) const
{
	// Write:
	// (N points)
	// answer 1
	// answer 2
	// etc.

	Question::write_key(out);
	out << endl;
	if ( q_answers.size() > 1)
	{
		out << "    " << q_answers[0] << endl;
		for (int i=1; i < q_answers.size(); i++)
		{
			out << endl;
			out << "    ---or---" << endl;
			out << endl;
			out << "    " << q_answers[i] << endl;
		}
	} else
	{
		out << "    " << q_answers[0] << endl;
	}
	out << endl;
	out << endl;
}
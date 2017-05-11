/* Barret Fisher
 * CS 215, Spring 2013
 * Programming Assignment 3
 * 3 April, 2013
 *
 * Implementation of the MultipleChoiceQ class.
 */ 

#include "multiplechoiceq.h"

MultipleChoiceQ::MultipleChoiceQ(int points, int chapter, string text, int numchoices, char correct, vector<string> choices)
	: Question(points, chapter, text)
{
	q_numchoices = numchoices;
	q_correct = correct;
	q_choices = choices;
}

// Convert a letter to an index.  Returns 0 for 'a' or 'A', 1 for
// 'b' or 'B', and so on, up to 25 for 'z' or 'Z'.  Should be called
// only with ordinary ASCII letters.
int letter_to_index(char c)
{
	c = tolower(c);
	if (c < 'a' || c > 'z')
		return -1; // Invalid
	else
		return c - 'a';  // subtract the ASCII codes
}

// Convert an index to a lowercase letter.  Returns 'a' for 0, 'b' for 1,
// and so on.  Should be called only with values between 0 and 25 inclusive.
char index_to_letter(int i)
{
	return 'a' + i;
}


void MultipleChoiceQ::write(ostream &out) const
{
	// Write:
	// (N points) question
	// 
	Question::write(out);
	out << endl;
	for (int i = 0; i < q_numchoices; i++)
	{
		out << index_to_letter(i) << ". " << q_choices.at(i) << endl;
	}
	out << endl;
	out << "______" << endl;
	out << endl;
	out << endl;
}

void MultipleChoiceQ::write_key(ostream &out) const
{
	// Write:
	// (N points)
	// correct answer

	Question::write_key(out);
	out << endl;
	out << "    " << q_correct << ". " << q_choices.at(letter_to_index(q_correct)) << endl;
	out << endl;
	out << endl;
}
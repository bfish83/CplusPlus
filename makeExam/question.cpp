/* Barret Fisher
 * CS 215, Spring 2013
 * Programming Assignment 3
 * 3 April, 2013
 *
 * Implementation of the Question class.
 */ 

#include "question.h"

Question::Question(int points, int chapter, string text)
	: point_value(points), chapter_number(chapter), question_text(text)
{}

void Question::write(ostream &out) const
{
	write_point_value(out);
	
	out << " " << question_text << endl;
}

void Question::write_key(ostream &out) const
{
	write_point_value(out);
	out << endl;
}

// Private method!
void Question::write_point_value(ostream & out) const
{
	string pt_noun;
	if (point_value == 1)
		pt_noun = "point";
	else
		pt_noun = "points";

	out << "(" << point_value << " " << pt_noun << ")";
}
#ifndef QUESTION_H_INCLUDED
#define QUESTION_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>

using namespace std;

// Class Question
// Construct a question with a given point value, chapter number, and question text.
// Get the point value, chapter number, and question text.
// Write the question to a file stream.
// Write the question's key to a file stream.
class Question
{
public:

	//Default Constructor
	Question(int points, int chapter, string text);

	// virtual write methods that are expanded by sub-classes
	virtual void write(ostream &out) const;
	virtual void write_key(ostream &out) const;
	
private:
	void write_point_value(ostream & out) const;
	int point_value;
	int chapter_number;
	string question_text;
};

#endif
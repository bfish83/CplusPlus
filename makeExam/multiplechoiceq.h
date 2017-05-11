#ifndef MULTIPLECHOICEQ_H_INCLUDED
#define MULTIPLECHOICEQ_H_INCLUDED

#include "question.h"

// Class MultipleChoiceQ -- inherits from Question
// Construct a question with a given point value, chapter number, question text, 
//		number of choices, correct letter, vector of choices
// Write the question to a file stream.
// Write the question's key to a file stream.
class MultipleChoiceQ : public Question
{
public:

	/* MultipleChoiceQ
	 * Description: default constructor for class
	 * Inputs: int points, int chapter, string text, int numchoices, 
	 *		char correct, vector<string> choices);
	 *		(everything that makes up a MultipleChoice question)
	 * Outputs: none
	 */
	MultipleChoiceQ(int points, int chapter, string text, int numchoices, char correct, vector<string> choices);

	/* write
	 * Description: overides Question class write method
	 * Inputs: takes a pointer to outfile
	 * Outputs: writes exam data to file
	 */
	virtual void write(ostream &out) const;

	/* write_key
	 * Description: overides Question class write_key method
	 * Inputs: takes a pointer to outfile
	 * Outputs: writes exam key data to file
	 */
	virtual void write_key(ostream &out) const;

private:
	int q_numchoices;
	char q_correct;
	vector<string> q_choices;

};

#endif
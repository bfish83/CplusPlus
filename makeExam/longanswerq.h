#ifndef LONGANSWERQ_H_INCLUDED
#define LONGANSWERQ_H_INCLUDED

#include "question.h"

// Class LongAnswerQ -- inherits from Question
// Construct a question with a given point value, chapter number, question text, and correct answer.
// Write the question to a file stream.
// Write the question's key to a file stream.
class LongAnswerQ : public Question
{
public:

	/* LongAnswerQ
	 * Description: default constructor for class
	 * Inputs: int points, int chapter, string text, string answer
		 (everything that makes up a LongAnswer question)
	 * Outputs: none
	 */
	LongAnswerQ(int points, int chapter, string text, string answer);

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
	string q_answer;
};

#endif
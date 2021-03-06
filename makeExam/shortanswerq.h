#ifndef SHORTANSWERQ_H_INCLUDED
#define SHORTANSWERQ_H_INCLUDED

#include "question.h"

// Class ShortAnswerQ -- inherits from Question
// Construct a question with a given point value, chapter number, question text, and correct answers.
// Write the question to a file stream.
// Write the question's key to a file stream.
class ShortAnswerQ : public Question
{
public:

	/* ShortAnswerQ
	 * Description: default constructor for class
	 * Inputs: int points, int chapter, string text, vector<string> answers
		 (everything that makes up a ShortAnswer question)
	 * Outputs: none
	 */
	ShortAnswerQ(int points, int chapter, string text, vector<string> answers);

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

	vector<string> q_answers;

};

#endif
#ifndef EXAM_H_INCLUDED
#define EXAM_H_INCLUDED

#include "question.h"
#include "codeq.h"
#include "longanswerq.h"
#include "multiplechoiceq.h"
#include "shortanswerq.h"

/* Class 
 * Description: 
 * Inputs: 
 * Outputs: 
*/
/* Class Exam - creates exam class using sub-question classes
 * Description: Main function, takes input from user and has methods 
 *   to create class, read file, shuffle questions, write exam/key
 * Inputs: Functions use number of questions, min chapter, max chapter 
 *   to create exam and string filename to read file
 * Outputs: Write functions call question writes to create exam/key files
*/
class Exam {
public:

	/* Exam(int num_questions, int min_chapter, int max_chapter) - default constructor
	 * Description: Creates an exam class
	 * Inputs: int num_questions = number of questions exam to have, 
	 *   int min_chapter = miniumum chapter for questions, int max_chapter = max
	 *   chapter for questions
	 * Outputs: None
	*/
	Exam(int num_questions, int min_chapter, int max_chapter);

	/* ~Exam() - default destructor
	 * Description: Destroys exam object
	 * Inputs: None
	 * Outputs: None
	*/
	~Exam();

	/* int read_questions(string filename) - reads questions from file
	 * Description: takes a filename and reads line by line, assigning question pointers for each
	 * Inputs: string filename - the name of the file
	 * Outputs: returns an int of the number of questions in the final sorted list
	*/
	int read_questions(string filename);

	/* void shuffle() - shuffle function
	 * Description: shuffles list of questions
	 * Inputs: None
	 * Outputs: None
	 * Notes: function called by other functions
	*/
	void shuffle();

	/* void write_exam(string filename) const - calls write for questions
	 * Description: takes filename and writes to it the exam
	 * Inputs: string filename is the name of the file to be created/written to
	 * Outputs: none
	*/
	void write_exam(string filename) const;

	/* void write_key(string filename) const - calls write_key for questions
	 * Description: takes filename and writes to it the exam key
	 * Inputs: string filename is the name of the file to be created/written to
	 * Outputs: none
	*/
	void write_key(string filename) const;
	

private:
	int e_numquestions;
	int e_minchapter;
	int e_maxchapter;

	vector<Question*> question_list;
	vector<Question*> shuffled_list;

	vector<string> split_string(string input);
	Question* parse_question(string line);
};

#endif
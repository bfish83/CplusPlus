/* Barret Fisher
 * CS 215, Spring 2013
 * Programming assignment 2
 * 2 March, 2013
 *
 * Define and test a string215 class implementing character strings.
*/



#include <iostream>
#include <cstring>
#include "string215.h"
using namespace std;



/* stringLength(const char *input) - Returns int equal to length of input
 *
 * Description:
 *   This function was designed in lab 5 to return the length of a c string
 *
 * Inputs:
 *   Takes 1 input, a pointed to a c string
 *
 * Outputs:
 *   Outputs an int the length of the c string, minus null terminator
*/
int stringLength(const char *input) {
	int count = 0;
	while (input[count] != '\0') {
		count++;
	}
	return count;
}

/* *copy_string(const char *input) - Make and return a dynamically-allocated copy of the input C string.
 *
 * Description:
 *   This function was designed in lab 5 to to make a dynamic copy of a c string. 
 *   It calls stringLength() function to get the size then uses a loop to copy the data.
 *
 * Inputs:
 *   Takes pointer to c string as its input
 *
 * Outputs:
 *   Returns dynamic copy of c string
*/
char *copy_string(const char *input)
{
	int char_num = stringLength(input);
	char* new_string = new char[char_num + 1];

	for (int i = 0; i < char_num ; i++) {
		new_string[i] = input[i];
	}
	new_string[char_num] = '\0';
	return new_string;
}

/* equal_string(const char *first, const char *second) - Return true 
 *   if the two C strings contain the same sequence of characters.
 *
 * Description:
 *   This function was designed in lab 5. It compares two cstrings and compares
 *   them to make sure they are exactly the same.
 *
 * Inputs:
 *   Two inputs, both pointers to c strings
 *
 * Outputs:
 *   One output, a bool. True if the strings match, false otherwise.
*/
bool equal_string(const char *first, const char *second)
{
	int first_num = stringLength(first);
	int second_num = stringLength(second);
	if (first_num != second_num) {
		return false;
	} else {
		for (int i = 0; i <= first_num; i++) {
			if (*(first + i) != *(second + i)) {
				return false;
			}
		}
	}
	return true;
}

/* string215::string215() - default constructor for string215
 *
 * Description:
 *   This is the basic constructor our string215 class
 *   will use. Member functions of the class will utilize
 *   the constructor every time they are run. It assigns data
 *   to an empty string, ready to be utilized.
 *
 * Inputs:
 *   No imputs
 *
 * Outputs:
 *   No outputs, it sets data equal to empty string
*/
string215::string215()
{
	data = copy_string("");
}

/* string215::string215(const string215 &other) - copy constructor
 *
 * Description:
 *   Another basic constructor for string215. Takes string215 object 
 *   and makes a copy by calling copy_string function.
 *
 * Inputs:
 *   Takes 1 input, string215 address location for object
 *
 * Outputs:
 *   No output, takes value at object location and puts it in data.
*/
string215::string215(const string215 &other)
{
	data = copy_string(other.data);
}

/* string215::~string215() - destructor!
 *
 * Description:
 *  Takes string215 object and deallocates the memory it was using. 
 *  Basic destructor for string215. 
 *
 * Inputs:
 *   No inputs.
 *
 * Outputs:
 *   No output. Destructor is called automatically and deletes data.
*/
string215::~string215()
{
	delete[] data;
}

/* string215::length() const - Return the length of a string215, 
 *   not counting the null terminator.
 *
 * Description:
 *   Function calls subfunction stringLength to get length of string215 object.
 *
 * Inputs:
 *   No input.
 *
 * Outputs:
 *   Returns an int that is length of string215 object
*/
int string215::length() const
{
	int length = stringLength(data);
	return length;
}

/* string215::getchar(int index) const - Return the character at a given index.  
 *   Returns '\0' if the index is out of bounds.
 *
 * Description:
 *   Takes an int and tests to make sure string215 object is big enough 
 *   and if it is it then returns the char at that index location
 *
 * Inputs:
 *   Takes 1 input, an int
 *
 * Outputs:
 *   Will return the char at given index location or '\0' if out of bounds
*/
char string215::getchar(int index) const
{
	int count = length();
	if (index >= 0 && index < count) {
		return data[index];
	} else { return '\0'; }
}

/* string215::setchar(int index, char newchar) - Set the character at a given 
 *   index and returns true. If no change is made, it returns false.
 *
 * Description:
 *   Replaces a char in string215 object with a new char at specified location
 *
 * Inputs:
 *   Two. Takes an int for location and a char to replace the old char at that location.
 *
 * Outputs:
 *   Returns true if a change is made, false otherwise. 
*/
bool string215::setchar(int index, char newchar)
{
	int count = length();
	if (index >= 0 && index < count) {
		data[index] = newchar;
		return true;
	}
	return false;
}

/* string215::equals(const string215 &other) const - Check whether two strings 
 *   contain the same characters.
 *
 * Description:
 *   Calls subfunction equal_string with arguments string215 object and string215 other object.
 *   If the two string215s are equal it returns true, otherwise false.
 *
 * Inputs:
 *   Takes one parameter, address of string215 other object
 *
 * Outputs:
 *   Returns a true or false
*/
bool string215::equals(const string215 &other) const
{
	return equal_string(data, other.data);
}

/* string215::append(const string215 &suffix) - Add a suffix to the end of this string. 
 *   Allocates and frees memory.
 *
 * Description:
 *   Takes length of string215 object, length of string215 suffix, adds them together 
 *   and creates new c string of length total. Then copies all string215 object into 
 *   new cstring, copies suffix, adds null terminator. Then assigns new c string to old string215 object.
 *
 * Inputs:
 *   Takes 1 input, address of string215 suffix
 *
 * Outputs:
 *   No output. Just adds suffix to data in string215 object.
*/
void string215::append(const string215 &suffix)
{
	int first_length = length();
	int second_length = suffix.length();
	int total_length = first_length + second_length;

	char *new_data = new char[total_length + 1];

	for (int i = 0; i < first_length; i++) {
		new_data[i] = data[i];
	}
	for (int i = 0; i < second_length; i++) {
		new_data[i + first_length] = suffix.data[i];
	}
	new_data[total_length]  = '\0';
	data = new_data;
}

/* char* string215::c_str() const - Return a pointer to the raw character data (not a copy).
 *
 * Description:
 *   Makes a pointer to string215 object, returns the pointer.
 *
 * Inputs:
 *   No input.
 *
 * Outputs:
 *   Returns pointer to string215 object.
*/
const char* string215::c_str() const
{
	const char *new_data = data;
	return new_data;
}

/* string215::replace() - Replace the contents of a string215 with the
 *   contents of a C string.
 *
 * Description:
 *   Replace the contents of this string with a copy of the C string
 *   argument.  Allocates memory for the new string array, performs a
 *   deep copy of the input, and frees the old array.
 *
 * Inputs:
 *   const char *in_str - The C string to copy into this object.
 *   
 * Outputs:
 *   No return value.  The current string's contents are modified to be
 *   character-by-character identical with the C string.
*/
void string215::replace(const char *in_str)
{
	delete[] data;
	data = copy_string(in_str);
}

/* string215::string215(const char *in_str) - Create a string215 
 *   that is a (deep) copy of a C string.
 *
 * Description:
 *   Takes a c string and makes a deep copy of it using copy_string function.
 *
 * Inputs:
 *   C string to copy
 *
 * Outputs:
 *   None. Just makes string215 object copy of c string.
*/
string215::string215(const char *in_str)
{
	data = copy_string(in_str);
}


/* test_string215() - Test the string215 class.
*
* Description:
*   Run a number of tests of the various methods of the string215 class.
*
* Inputs:
*   No inputs.
*
* Outputs:
*   Prints a message about each failed test to cerr.  Returns the number of
*   failed tests.
*/
int test_string215()
{
	// Current test number.  Be sure to increment this before each test!
	int curr_test = 0;
	// Number of failed tests.
	int failed = 0;
	
	// Testing contents:
	// Tests 1-8 cover the constructors and c_str().
	// Tests 9-10 cover length().
	// Tests 11-12 cover getchar().
	// Tests 13-16 cover append().
	// Tests 17-20 cover setchar().
	// Tests 21-24 cover equals().
	// Tests 25-28 cover replace().

	// Test 1: the default constructor and c_str().  An empty string
	// should still be terminated with a '\0' (at position 0), and in
	// particular should not be represented by a null pointer.
	curr_test++;
	string215 empty;
	const char *cs = empty.c_str();
	if (cs == NULL || cs[0] != '\0') {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Test 2: does the C string constructor faithfully copy its input?
	curr_test++;
	char letters[] = "some characters here";
	string215 full(letters);

	if (strcmp(letters, full.c_str()) != 0) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Test 3: and did it do a deep copy?  The pointers should
	// differ.
	curr_test++;
	if (letters == full.c_str()) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Test 4: make sure c_str() isn't making a copy.  If we call
	// it twice in a row, it should return the same address.
	curr_test++;
	if (full.c_str() != full.c_str()) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Test 5: make sure we can copy an empty string.
	curr_test++;
	string215 empty_fromc("");
	cs = empty_fromc.c_str();
	if (cs[0] != '\0') {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Test 6: test that the copy constructor copies.
	curr_test++;
	string215 full_copy(full);
	if (strcmp(full_copy.c_str(), full.c_str()) != 0) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Test 7: and that it does a deep copy.
	curr_test++;
	if (full_copy.c_str() == full.c_str()) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Test 8: test the copy constructor on an empty string.
	curr_test++;
	string215 empty_copy(empty);
	cs = empty_copy.c_str();
	if (cs[0] != '\0' || cs == empty.c_str()) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Test 9: test the length method.
	curr_test++;
	if (full.length() != strlen(full.c_str())) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Test 10: also on an empty string.
	curr_test++;
	if (empty.length() != 0) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Test 11: test getchar for the first and last characters.
	curr_test++;
	string215 str("testing");
	if (str.getchar(0) != 't' || str.getchar(str.length() - 1) != 'g') {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Test 12: also on out-of-bounds indices.
	curr_test++;
	if (str.getchar(-1) != '\0' || str.getchar(str.length()) != '\0'
		|| str.getchar(9999) != '\0')
	{
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Test 13: test that append works in a simple case.
	curr_test++;
	string215 suffix("123");
	str.append(suffix);
	if (strcmp(str.c_str(), "testing123") != 0) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Test 14: and that it didn't modify its argument.
	curr_test++;
	if (strcmp(suffix.c_str(), "123") != 0) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Test 15: test that append works with an empty string
	curr_test++;
	string215 suffix2("");
	str.append(suffix2);
	if (strcmp(str.c_str(), "testing123") != 0) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Test 16: test that you can append TO an empty string.
	curr_test++;
	suffix2.append(str);
	if (strcmp(suffix2.c_str(), "testing123") != 0) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Test 17: simple test to change first char in string.
	curr_test++;
	str.setchar(0, 'n');
	if(strcmp(str.c_str(), "nesting123") != 0) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Test 18: simple test to change last char in string.
	curr_test++;
	str.setchar(9, '1');
	if(strcmp(str.c_str(), "nesting121") != 0) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Test 19: test to make sure no changes made on index out of bounds
	curr_test++;
	if (str.setchar(10, 'Z') == true) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}
	if (str.setchar(-1, 'Z') == true) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}
	
	// Test 20: test changing char in middle
	curr_test++;
	str.setchar(2, 't');
	if (strcmp(str.c_str(), "netting121") != 0) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Test 21: tests equal strings with equals
	curr_test++;
	string215 var1("equals");
	string215 var2("equals");
	if ( var1.equals(var2) == false ) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Test 22: tests unequal strings with equals
	curr_test++;
	string215 var3("nope");
	if ( var1.equals(var3) == true ) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Test 23: tests equals method with empty string
	curr_test++;
	string215 var4("");
	if ( var1.equals(var4) == true ) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Test 24: tests equals method with two empty strings
	curr_test++;
	string215 var5("");
	if ( var5.equals(var4) == false ) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	//Test 25: tests replace wth simple case
	curr_test++;
	string215 old("killmenow");
	char not_old[] = "live";
	old.replace(not_old);
	if (strcmp(old.c_str(),  "live") !=0 ) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	//Test 26: tests replace with empty string
	curr_test++;
	char not_older[] = "";
	old.replace(not_older);
	if (strcmp(old.c_str(),  "") !=0 ) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	//Test 27: tests replace with two empty strings
	curr_test++;
	char not_oldest[] = "";
	old.replace(not_oldest);
	if (strcmp(old.c_str(),  "") !=0 ) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	//Test 28: tests replace by 'filling' empty string
	curr_test++;
	char oldest[] = "full";
	old.replace(oldest);
	if (strcmp(old.c_str(),  "full") !=0 ) {
		cerr << "Test " << curr_test << " failed." << endl;
		failed++;
	}

	// Finally, return the number of failed tests
	return failed;
}

/* main() - runs test_string215() function, outputs results
 *
 * Description:
 *   All the work in this program is done in the class member functions. This main function 
 *   simply runs the testing function (which tests the class member functions) and outputs
 *   the results of the tests. Then calls pause function to exit.
 *
 * Inputs:
 *   None.
 *
 * Outputs:
 *   Runs test function and outputs to screen the results.
*/
int main()
{
	int failed = test_string215();

	if (failed == 0)
		cout << "All tests passed successfully." << endl;
	else
		cout << "Sorry, " << failed << " test(s) failed." << endl;

	pause_215(false);
	// Remember that returning zero from main indicates success, while
	// return anything else means that some kind of error occurred.
	return failed;
}


/* pause_215() - Wait for the user to press ENTER.
*
* Description: 
*   Optionally read and discard the remainder of the user's last
*   line of input.  Then, prompt the user to press ENTER, then
*   read and discard another line of input.
*
* Inputs:
*   bool have_newline:
*     True if the user has already entered a newline that the
*     program has not yet read.  If true, this function first
*     discards remaining input up to and including that newline.
*
*   Reads two lines from standard input if have_newline is true,
*   one line if it is false.  Lines are assumed to be less than
*   two hundred characters long.
*
* Outputs:
*   No return value.
*
*   Prints a prompt to standard output.
*
* Notes:
*   This function is intended to be used at the end of a program,
*   just before returning from main().  Reading another line of
*   input prevents the console window from closing immediately.
*
*   In general, have_newline should be true if the last user input
*   from cin used the extraction operator (>>), and false if there
*   has been no user input or if the last input used getline().
*/
void pause_215(bool have_newline)
{
	if (have_newline) {
		// Ignore the newline after the user's previous input.
		cin.ignore(200, '\n');
	}

	// Prompt for the user to press ENTER, then wait for a newline.
	cout << endl << "Press ENTER to continue." << endl;
	cin.ignore(200, '\n');
}
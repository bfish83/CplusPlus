/* Barret Fisher
 * CS 215, Spring 2013
 * Programming assignment 1
 * 5 February, 2013
 *
 * Compute and print a table of numerical values.
 */

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

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

/* two_to_n() - gives you back a 2 raised to the n
 * Description: Function computes 2 raised to the power of n
 * Inputs: Takes an int parameter num which is 2's exponent
 * Outputs: 2 to the n
 * Notes: function works!
 */
int two_to_n(int num)
{
	int value = 2;
	if (num > 1) {
		while (num > 1) {
			value = value * 2;
			num--;
		}
	} else if (num == 0) {
		value = 1;
	}
	return value;
}

/* factorial() - gives you back a number factorial
 * Description: A factorial is a number times one less than itself to the n times for n>0
 * Inputs: Takes an int parameter num which is the number to be factorialized
 * Outputs: The number's factorial
 * Notes: Output is a double but will probably be one number followed by dot and 0.
 */
double factorial(int num)
{
	int i = 0;
	double result = 1.0;
	while ( num != i ) {
		result = num * result;
		num -= 1;
	}
	return result;
}

/* stirling() - returns Stirling's approximation
 * Description: Function returns Stirling's approximation, which is an approximation for large factorials
 * Inputs: Has one int parameter num, which is the number to be approximated
 * Outputs: Outputs stirlings approximation using his formula
 * Notes: The return value is a double and will probably be large.
 */
double stirling(int num)
{
	double pi = atan2(0.0, -1.0);
	double e = exp(1.0);
	double new_num = sqrt(2 * pi * num) * pow( (num / e), num);
	return new_num;
}

/* fibonacci() - returns nth Fibonacci number
 * Description: Fibonacci's sequence, ie: 1 1 2 3 5 8 13 ... follows n3 = n1 + n2, n4 = n2 + n3, etc.
 * Inputs:  Int parameter num (the nth number)
 * Outputs: Outputs nth Fib number
 * Notes: Remember that 0 is the first positon (1), 1 is the 2nd (1), etc.
 */
int fibonacci(int num)
{
	const int SIZE = 32;
	int fib[SIZE] = {1,1};
	for (int i = 2; i < SIZE; i++) {
		fib[i] = fib[i-1] + fib[i-2];
	}
	return fib[num];
}

/* main() - Takes a number from 0-32 and outputs table of values
 * Description: Main function uses loops to call sub functions for each value in each row of the table. Table goes to n rows.
 * Inputs: int parameter number taken from user. It has to be between 0-32 inclusive or function gives error.
 * Outputs: Outputs table with n rows 0 to number, each row has n, 2 to the n, n factorial, stirling's approximation for n, and nth Fibonnaci's number
 * Notes: n factorial, despite being a double, is only outputting as an integer. can't figure that one out.
 */
int main()
{
	int number = 1;
	cout << "Please enter a positive integer between 0 and 32: ";
	cin >> number;
	if (number < 0 || number > 32) {
		cout << "You entered " << number << ", that number is not between 0 and 32. Exiting..." << endl;
	}
	else {
		cout << endl;
		cout << setw(3) << "n" << setw(12) << "2^n" << setw(12) << "n!" << setw(12) << "Stirling" << setw(12) << "Fib" << endl;
		cout << "--- ----------- ----------- ----------- -----------" << endl;
		for (int i = 0 ; i <= number ; i++) {
			cout << setw(3) << i << setw(12) << two_to_n(i) << setw(12) << setprecision(3) << factorial(i) << setw(12) << stirling(i) << setw(12) << fibonacci(i) << endl;
		}
	}

	pause_215(true);

	return 0;
}
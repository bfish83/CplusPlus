README
CS 315-001 Spring 2015
Program Assignment 1, Milestone 3
February, 2015
name: Barret Lee Fisher

Synopsis: This program tackles the problem of smoothing any sequence of ints.

To compile: g++ --std=c++0x pa1.cpp

Input for this program should follow the specs.

To run:
./a.out < ./tests/test_edge05.in

(filenames are on the range test_edge00.in - test_edge10.in)
where test_edge05.in can be replaced with any other test file. The only output that
will be presented is an integer which returns the smallest d such that the
sequence is d-smooth, followed by the number of comparisons for the test.

Use the command:
./test.sh 
to run ALL tests included in subdirectory tests.

A typescript file, "script.txt," (generated with the UNIX script command) is provided to show use
of all included test files and the source file.

Included Files: //adjust as necessary
README - current file
pa1.cpp - source code for milestone 3 algorithm with result and comparison
count output to console
test.sh - shell script to generate and run tests for experimental analysis
script.txt - sample session showing commands, inputs, and outputs
pa1_exp_analysis.txt - txt file with experimental analysis report
tests - tests directory has test files used in experimental analysis

Bugs and Extras:
No bugs have been found to date.

Algorithm Description:
The algorithm takes input an index value for the size of the sequence followed by each sequence value. After all sequence values are input the algorithm finds the smallest D value such that another sequence can be created with all values 1.) increasing and 2.) within D range of the first sequence. This is called smoothing. Output is the D value and the number of comparisons made to find the D value. It works by using an implementation of binary search: all values of the original sequence are summed to find the maximum d value, then it starts halfway between 0 and maximum, attempting to create a sequence that matches the parameters with the attempted D value. If the attempt works, it sets the D value to max and cuts it in half again. If it doesn't work it sets the minimum value to the D value and goes between min and max again. It does this over and over until min and max surround the smallest possible D value. It exits the while loop when it attempts to set the minimum value to D and it is already the same value, this means it has already attempted this D value and failed, therefore the actual D value is precisely one to the right of the last attempted D. To make sure a sequence is not already smooth it checks first to see if the input sequence is already strictly increasing, in which case it bypasses the compare function and sets D to 0 as the smoothed sequence is an exact copy of the original.

The theoretical running time of my algorithm is O(nlogn).

Algorithm Example:
Consider the following input sequence.
5
25
11
2
13
20

Length is 5
Output d is equal to 13
The smoothed sequence is 12, 13, 14, 15, 16

My algorithm sums the numbers in the sequence to find max (in this case 71), and divides it in half to attempt using 35. 35 works so it then tries 17, which also works. It then tries 8, which doesnt work, so it is now moving between 8 and 17. It tries 12, which doesnt work, then tries 14 which does. It lastly tries 13 which works, and exits when it tries to set minimum to 13 where it already is set.

Testing: 

Test files are stored in the tests directory.
Results can be found in the script.txt file and in the experimental analysis.

Test analysis can be found in the Experimental Analysis document
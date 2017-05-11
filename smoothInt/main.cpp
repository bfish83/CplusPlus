/* Barret Fisher
 * CS 315
 * Programming Assignment 1
 * Spring 2015
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void pause()
{
	cin.ignore(315, '\n');
	cout << endl << "Press ENTER to continue." << endl;
	cin.ignore(315, '\n');
}

bool isIncreasing(vector<int>& tSequence)
{
	for (int i = 1; i < tSequence.size(); i++)
	{
		if (tSequence[i] <= tSequence[i-1])
			return false;
	}
	return true;
}

bool buildSequence(vector<int>& tSequence, vector<int>& wSequence, int dValue)
{
	wSequence[0] = tSequence[0] - dValue;
	for (int i = 1; i < wSequence.size(); i++)
	{
		wSequence[i] = tSequence[i] - dValue;
		while ( wSequence[i-1] >= wSequence[i] )
		{
			wSequence[i]++;
		}
		if ( (tSequence[i] + dValue) < wSequence[i] )
			return false;
	}
	return true;
}

int main(int argc, char * argv[])
{
	// get size of T sequence
	int size;
	cin >> size;
	
	// fill T sequence with values AND get total of all values
	int max = 0;
	vector<int> tSequence(size);
	for (int i = 0; i < size; i++)
	{
		int value;
		cin >> value;
		tSequence[i] = value;
		max = max + abs(value);
	}

	// create W sequence
	vector<int> wSequence(size);

	// setup variables
	bool searching = true;
	bool works = true;
	int counter = 0;
	int min = 0;
	int dValue = 0;

	// check to see if sequence already smooth
	if (isIncreasing(tSequence))
	{
		wSequence = tSequence;
		counter++;
		searching = false;
	}

	// find D value
	while (searching)
	{
		dValue = ( (max - min) / 2) + min;
		works = buildSequence(tSequence, wSequence, dValue);
		counter++;
		if (works)
		{
			max = dValue;
		}
		else if (min == dValue)
		{
			dValue++;
			works = buildSequence(tSequence, wSequence, dValue);
			counter++;
			if (works)
				searching = false;
		}
		else
		{
			min = dValue;
		}
	}

	// output
	cout << dValue << endl;
	
	//for (int i=0; i < wSequence.size();i++)
	//	cout << wSequence[i] << endl;

	cout << "Number of comparisons: " << counter << endl; // <-- number of iterations

	//pause();
	return 0;
}

// File: connected.h
// Author: Barret Fisher
// Description: simple class to check connectivity in graph

// connected class

#include "connected.h"
using namespace std;

connected::connected()
{
	count = 0;
	check = false;
}

connected::connected(int n)
{
	for (int i=1; i <= n; i++)
	{
		vertices[i] = i;
	}
}

void connected::add(int x, int y)
{
	edges[count][0] = (x,y);
	count++;
	combine(x,y);
}

void connected::combine(int x, int y)
{
	edges[count][0] = (x,y);
	count++;
}

bool connected::complete()
{
	return check;
}
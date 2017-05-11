// File: connected.h
// Author: Barret Fisher
// Description: simple class to check connectivity in graph

// connected class

#include <vector>
using namespace std;

class connected 
{
	public:
		connected();
		connected(int n);

		void add(int x, int y);
		void combine(int x, int y);
		bool complete();

	private:
		vector<int> vertices;
		vector<vector<int>> edges;
		int count;
		bool check;
};

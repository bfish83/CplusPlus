/* Barret Fisher
 * CS 315
 * Programming Assignment 2
 * Spring 2015
*/

//Incomplete version for pa2 cs315 Spring 2015  - level m2
//
// File: main.cpp
// Author: developed for CS315 CS-UK JWJ
// Description:  This program finds the minimal
// spanning tree using Kruskal's algorithm.
// Input and output are as specified by the
// instructor.
//Note: for our project the input is an UNDIRECTED graph

#include <cstdlib> // exit
#include <map>
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include "graph.h"
#include "edge.h"
#include "unionfind.h"

using namespace std;

int weight=0;

int main(int argc, char * argv[])
{

	priority_queue<edge> edges_pq;

  ///////////////////////////////////////////////////
  // open text file for reading
  if(argc != 2)
  {
    // Hint to user about how to use command line
     fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
	 exit(1);
  }

  ifstream in;
  in.open(argv[1]);  //open input stream.

//  ifstream in("mst2.in");

  if(!in)         //check for open success.
  {
    cout << "no input file read !!" << endl;
    exit(1);
  }
  ///////////////////////////////////////////////////

	//graph info
	int s;		//graph size
	char t;		//graph type

	int required;

//Read input and create graph
//TODO: read the number of required cities
//TODO: read the cities and index them to know their indices in the matrix
	in >> s; //size
	in >> required; //required connections


	string str;
	map<string, int> indexer;
	map <string, int> :: iterator it;

	int nextidx = 1;
	while( nextidx <= s )
	{
		in >> str;
		if (indexer.find(str) == indexer.end())
			indexer[str] = nextidx++;
	}


	t = UNDIRECTED; //needed for our undirected graphs
	graph m(s, t);  //construct see graph.h and graph.cpp

	m.read(in);

//  	in.close();

	graph kruskal_tree(s, t);

//Kruskal's algorithm
//TODO: add the required edges

//set PQ
	for(int i=1; i <= s; i++){
		for (int j=i; j <= s; j++){
			if (m.edge(i,j)){
				edge e(i, j, m.edge_weight(i,j));
				edges_pq.push(e);
			}
		}
	}


//Build the subnetwork

	unionfind un(m.size()+1);
	int kruskal_size=0;

	//add required edges to subnetwork
	for (int i = 0; i < (required*2); i+=2)
	{
		string temp1;
		string temp2;
		int loc1 = 0;
		int loc2 = 0;

		in >> temp1;
		in >> temp2;

		for (const auto& entry: indexer) {
			if (entry.first == temp1)
			{
				loc1 = entry.second;
			}
			if (entry.first == temp2) {
				loc2 = entry.second;
			}
		}
		
		if ( (0 < loc1) && (loc1 <= s) && (0 < loc2) && (loc2 <= s) )
		{
			if ( loc1 > loc2) {
				un.unions(loc2,loc1);
				weight += m.edge_weight(loc2,loc1);
				kruskal_size++;
			} else {
				un.unions(loc1,loc2);
				weight += m.edge_weight(loc1,loc2);
				kruskal_size++;
			}
		} else {
			cout << "Required connection of " << temp1 << " to " << temp2 << " does not exist." << endl;
		}
	}

	edge edge_temp;
	while( !edges_pq.empty() )
	{
		edge_temp=edges_pq.top();

		if(un.find(edge_temp.get_from()) == un.find(edge_temp.get_to()))
			edges_pq.pop();
		else {
			un.unions(un.find(edge_temp.get_from()), un.find(edge_temp.get_to()));
			weight += edge_temp.get_weight();
			kruskal_size++;
		}
	}

//TODO: print the number of edges
	//m.printer(); //print the graph (see graph.h and graph.cpp

	if (kruskal_size < (s-1) )
		cout << "IMPOSSIBLE" << endl;
	else {
		cout << kruskal_size << endl;
		cout << weight << endl;
	}

	return 0;
}

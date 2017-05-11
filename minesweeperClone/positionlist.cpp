/* Barret Fisher
 * CS 215, Spring 2013
 * Programming Assignment 4
 * 19 April, 2013
 *
 * Implementation of the PositionList class.
 */ 
#include <cstdlib>
#include "positionlist.h"
using namespace std;


// Initialize a node with no next node and the given position.
Node::Node(Position p)
	: next(NULL), pos(p)
{}


// Initialize an empty list.
PositionList::PositionList()
{
	first = NULL;
}


// Initialize a copy of a list using the copy_nodes helper function.
PositionList::PositionList(const PositionList &original)
{
	first = copy_nodes(original.first);
}


// Clean up this list by freeing all its nodes.
PositionList::~PositionList()
{
	while( first != NULL )
	{
		pop_front();
	}
}


// Deep copy the contents of another list into this one.  Replace the old
// contents of this list, freeing those nodes.  Returns the implicit
// parameter by reference (return *this;)
PositionList &PositionList::operator=(const PositionList &other)
{
	if (this == &other)
		return *this;

	while(first != NULL)
	{
		pop_front();
	}
	
	first = copy_nodes(other.first);
	return *this;
}


// Returns true if this list is empty.
bool PositionList::empty() const
{
	if (first == NULL)
	{
		return true;
	} else {
		return false;
	}
}


// Calculate the size of the list (number of nodes).
int PositionList::size() const 
{
	int i = 0;
	for (Node *curr = first; curr != NULL; curr = curr->next) {
		i++;
	}
	return i;
}


// Find and return the index-th element in the list, counting from 0.
// If the index was out of bounds, return the Position (-1, -1).
Position PositionList::get(int index) const
{
	Node *now = first;
	for (int i=0; i < index; i++)
	{
		if (now == NULL)
		{
			return Position(-1, -1);
		}
		now = now -> next;
	}
	if (now == NULL)
	{
		return Position(-1, -1);
	} else {
		return now -> pos;
	}
}


// Add a new Position object to the beginning of the list.
void PositionList::push_front(Position pos)
{
	Node *new_object = new Node(pos);
	new_object -> next = first;
	first = new_object;
}


// Remove the first element, freeing its node.
void PositionList::pop_front()
{
	Node *temp = first;
	first = temp -> next;
	delete temp;
}


// Recursively make a deep copy of a node and all the nodes that follow.
// Returns the copy.  The input may be NULL, in which case nothing is
// copied and the function returns NULL.
Node *PositionList::copy_nodes(const Node *in) const
{
	if (in == NULL)
	{
		return NULL;
	} else {
		Node *copy = new Node(in -> pos);
		copy -> next = copy_nodes(in -> next);
		return copy;
	}
}
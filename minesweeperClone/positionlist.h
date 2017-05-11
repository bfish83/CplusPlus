// CS 215, Spring 2013
// Programming assignment 4
// 4 April, 2013
#ifndef POSITIONLIST_H_INCLUDED
#define POSITIONLIST_H_INCLUDED

#include "position.h"

/* Class Node - Implements Node class for PositionList
 * Description: Class representing a node in a PositionList
 * Inputs: Takes a position P
 * Outputs: New node
*/
class Node
{
public:
	/* Node(Position p) - creates new node
     * Description: Create a new node with no next node and position p.
     * Inputs: position p
     * Outputs: none
    */
	Node(Position p);
private:
	// A pointer to the next node in the linked list.
	Node *next;

	// The Position being stored in this node.
	Position pos;

	// The Node class is intended for the internal use of
	// PositionList, so give that class access to our
	// private data members.
	friend class PositionList;
};


/* Class PositionList - List of positions on 2d board
 * Description: Stores list of x and y coordinates
 * Inputs: None
 * Outputs: None
*/
class PositionList
{
public:
	/* PositionList() - default constructor 
     * Description: Initialize empty list
     * Inputs: None
     * Outputs: None
    */
	PositionList();

	/* PositionList(const PositionList &original) - 
     * Description: Initialize a list as a deep copy of another.
     * Inputs: Takes a positionlist
     * Outputs: Initializes new positionlist
    */
	PositionList(const PositionList &original);

	/* ~PositionList() - default destructor
     * Description: Clean up this list by freeing all its nodes.
     * Inputs: none
     * Outputs: none
    */
	~PositionList();

	/* PositionList &operator=(const PositionList &other) - Deep copy the 
	 *   contents of another list into this one. 
     * Description: Replace the old contents of this list, freeing those nodes.  
	 *   Returns the implicit parameter by reference (return *this;)
     * Inputs: Takes another list
     * Outputs: Turns it into this list
	 * Notes: This method implements assignment:   poslist = otherposlist;
    */
	PositionList &operator=(const PositionList &other);

	/* bool empty() - checks if list empty
     * Description: Returns true if this list is empty.
     * Inputs: None
     * Outputs: True or false
    */ 
	bool empty() const;

	/* size() - Calculates list size
     * Description: Calculate the size of the list (number of nodes)
     * Inputs: None
     * Outputs: An int, the size
    */
	int size() const;
	
	/* get(int index) - Finds element in list
     * Description: Find and return the index-th element in the list, counting 
	 *   from 0. If the index was out of bounds, return the Position (-1, -1).
     * Inputs: int index
     * Outputs: Position of index
    */
	Position get(int index) const;

	/* push_front(Position pos) - Adds new position object
     * Description: Add a new Position object to the beginning of the list.
     * Inputs: Position pos
     * Outputs: None
    */
	void push_front(Position pos);

	/* pop_front() - Removes first element from list
     * Description: Remove the first element, freeing its node.
     * Inputs: None
     * Outputs: None
    */
	void pop_front();

private:
	// Recursively make a deep copy of a node and all the nodes that follow.
	// Returns the copy.  The input may be NULL, in which case nothing is
	// copied and the function returns NULL.
	// This function will be used by the copy constructor and by operator= .
	Node *copy_nodes(const Node *in) const;

	Node *first;
};

#endif

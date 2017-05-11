// CS 215, Spring 2013
// Programming assignment 4
// 4 April, 2013
#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED

/* Class Position - Represents position on 2D board
 * Description: Stores an x and y coordinate, with methods 
 * to return and set each coordinate, and a method to test 
 * whether the position falls within a given width and height.
 * Inputs: 
 * Outputs: 
*/
class Position
{
public:
	/* Position() - default constructor
     * Description: Create a Position object for the origin (0, 0).
     * Inputs: None
     * Outputs: None
    */
	Position();

	/* Position(int xc, int yc) - Position object
     * Description: Create a Position object for the position (xc, yc).
     * Inputs: X-coordinate and y-coordinate
     * Outputs: 
    */
	Position(int xc, int yc);

	/* int x(), int(y) - x,y getters
     * Description: Getters for x and y coordinates.
     * Inputs: None
     * Outputs: x,y coordinates
    */
	int x() const;
	int y() const;

	/* set_x(int new_x), set_y(int new_y) - x,y setters
     * Description: Setters for x and y coordinates.
     * Inputs: New x,y position
     * Outputs: None
    */
	void set_x(int new_x);
	void set_y(int new_y);

	/* in_bounds(int width, int height) - checks bounds
     * Description: Returns true if this position's coordinates 
	 *   are within the given bounds: 0 <= x < width and
	 *   0 <= y < height .
     * Inputs: Width, height
     * Outputs: True or False
    */
	bool in_bounds(int width, int height) const;

private:
	int xcoord;
	int ycoord;
};

#endif

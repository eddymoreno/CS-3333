
#ifndef MAZEMAPPER_H
#define MAZEMAPPER_H

#include <vector>
#include <string>

using namespace std;

class Mazemapper
{
	// For the mandatory running times below, assume that 
	// C++ STL operations for queue, unordered_set, and map are 
	// O(1) time (they are for average-case, but not worst-case).
	//
	// For the mandatory running times below, 
	// s is the length of the string representing the maze,
	// i.e. (maze width + 1) * maze height
	// 
	// For a complete description of the maze string 
	// and maze solution formats, see the assignment pdf.

	public:
		// Creates a new Mazemapper using the maze 
		// represented by the parameter string.
		//
		// Example:
		//
		// # #############
		// #  #          #
		// # ## #### ## ##
		// #    ##       #  
		// ####### #######
		//
		// Must run in O(s) time.
		Mazemapper(string maze);

		// Returns whether the maze has exactly two exits 
		// (i.e., ' ' chars on the boundary) and is rectangular
		// (i.e., consists of a string with at least one '\n' character 
		// and all '\n' characters evenly spaced. 
		// 
		// Must run in O(1) time.
		bool valid();

		// Returns the width of the maze.
		// If the maze is not valid (valid() returns false), returns -1.
		// 
		// Must run in O(1) time.
		int width();

		// Returns the width of the maze.
		// If the maze is not valid (valid() returns false), returns -1.
		// 
		// Must run in O(1) time.
		int height();

		// Returns whether the maze is valid and 
		// there is a path between the two exits.
		//
		// Must run in O(s) time. 
		bool solvable();

		// Returns a string representing a shortest 
		// (minimum length) solution to the maze.
		// If the maze is not valid or has no solution, returns "".
		//
		// Example solution to constructor maze example:
		//
		// #o#############
		// #o #oooooo    #
		// #o##o####o## ##
		// #oooo##ooo    #  
		// #######o#######
		//
		// Must run in O(s) time.
		string solution();

	private: 
		// A helper class representing a vertex in 
		// an adjacency-list-based graph.
		class Vertex
		{
			public:
				// Grid location of the vertex
				int r; 
				int c;
				// List of neighboring vertices
				vector<Vertex*> neighs;
		};

		// List of all vertices.	
		vector<Vertex*> V;	
	
		// Pointers to vertices at exits.
		Vertex* start;
		Vertex* end;

		// Maze dimensions
		int _width;
		int _height;
};

#endif 


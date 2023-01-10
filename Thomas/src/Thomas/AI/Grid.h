

#ifndef GRID_H
#define GRID_H

//#include "../Math/Vector2D.h"
//#include "../AI//Node.hpp"
//
//#include "../Math/Vector2D.h"
//
//#include "../AI/Node.hpp"

#include "Thomas/AI/Node.h"
#include "Thomas/Math/Vector2D.h"
#include "Thomas/AI/AStarPathfindingObstacle.h"
namespace Thomas
{
	//Forward Declaration
	//class Node;
	//class Vec2;

    class Grid
    {
    public:

		//2D vector to represent the grid
		std::vector<std::vector<Node*>> nodeGrids;

		//Size of the grid
        Vec2 gridWorldSize;

		//Radius of the node.(Half-Width)
        float nodeRadius;

		//Diameter of the node. (Width)
        float nodeDiameter;

		//Width is the number of nodes that made up the width of the grid
        int gridWidth;

		//Height is the number of nodes that made up the height of the grid
        int gridHeight;

		//Origin of the grid
		Vec2 origin;
		
		//Default Constructor
		//Grid() : nodeGrids{}, gridWorldSize{}, nodeRadius{ 0.f }, nodeDiameter{ 1.f }, gridWidth{ 1 }, gridHeight{ 1 }, origin{ 0.f,0.f } {}

		//Constructor initialises the grid's size(x:width, y:height) and the radius of the nodes and the corresponding diameter
	    //We will also get grid width and grid height which is the number of nodes for that made up the width and height of the grid
		//Grid(Vec2 gridWorldSize, float nodeRadius);

		//The destructor will clear the grid of Node *
		//~Grid();

		//This allows the user to get the Node in the grid using bottom left coordinates by converting them to row major order coordinate index
		//Node* GetNodeFromGrid(int x, int y);

		////This allows the user to get the const Node in the grid using bottom left coordinates by converting them to row major order coordinate index
		//Node* GetNodeFromGrid(int x, int y) const;

		//This will add the neighbours of the parameter node to a 
		//vector of Node * neighbours which is a member variable of the parameter node
		//We are using the bottom left coordinate system in the calculation
		//void AddNeighbours(Node * node);

		//void AddObstacles(AStarPathfindingObstacle obstacle);

		////We will create a Grid which is represented as a vector of vector of Node *
		//void CreateGrid();
		//
		////This function will take the world position of the object and then return the corresponding Node's coordinate index in the grid
		//Vec2 WorldPositionToNodeIndex(Vec2 position);

		////This function will take the world position of the object and return the corresponding Node in the grid
		//Node* WorldPositionToNode(Vec2 position);

    };

	
	
	



}

#endif
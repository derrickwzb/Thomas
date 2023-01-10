#include "thpch.h"
#include "Thomas/AI/Grid.h"

#include "Thomas/Math/Vector2D.h"

#include "Thomas/AI/Node.h"
//#include <iostream>


namespace Thomas
{

	//Constructor initialises the grid's size(x:width, y:height) and the radius of the nodes and the corresponding diameter
	//We will also get grid width and grid height which is the number of nodes for that made up the width and height of the grid
	//Grid::Grid(Vec2 pGridWorldSize, float pNodeRadius)
	//{
	//	gridWorldSize = pGridWorldSize;
	//	nodeRadius = pNodeRadius;
	//	nodeDiameter = nodeRadius * 2;
	//	
	//	//Number of nodes that make up the width of the grid
	//	gridWidth = (int)(pGridWorldSize.x / nodeDiameter);

	//	//Number of nodes that made up the height of the grid
	//	gridHeight = (int)(pGridWorldSize.y / nodeDiameter);
	//}

	//This allows the user to get the Node in the grid using bottom left coordinates by converting them to row major order coordinate index
	

	//The destructor will clear the grid of Node *
	//Grid::~Grid()
	//{
	//	/*for (auto it : nodeGrids)
	//	{
	//		for (Node * node: it)
	//		{
	//			delete node;
	//		}


	//	}*/
	//	nodeGrids.clear();
	//}
	
}
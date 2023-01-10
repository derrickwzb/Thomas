

#include "thpch.h"
#include "Thomas/AI/Grid.h"

#include "Thomas/Math/Vector2D.h"

#include "Thomas/AI/Node.h"
//#include <iostream>
#ifndef GRIDSYSTEM_H
#define GRIDSYSTEM_H

namespace Thomas
{
	class GridSystem
	{
	public:
		void SetGridParameters(Grid & grid, Vec2 pGridWorldSize, float pNodeRadius);
		//This allows the user to get the Node in the grid using bottom left coordinates by converting them to row major order coordinate index
		Node* GetNodeFromGrid(Grid & grid, int x, int y);

		//This allows the user to get the const Node in the grid using bottom left coordinates by converting them to row major order coordinate index
		Node* GetNodeFromGrid(Grid & grid, int x, int y) const;

		//This will add the neighbours of the parameter node to a 
		//vector of Node * neighbours which is a member variable of the parameter node
		//We are using the bottom left coordinate system in the calculation
		void AddNeighbours(Grid& grid, Node* node);

		void AddObstacles(Grid & grid, AStarPathfindingObstacle obstacle);

		//We will create a Grid which is represented as a vector of vector of Node *
		void CreateGrid(Grid & grid);

		//This function will take the world position of the object and then return the corresponding Node's coordinate index in the grid
		Vec2 WorldPositionToNodeIndex(Grid & grid, Vec2 position);

		//This function will take the world position of the object and return the corresponding Node in the grid
		Node* WorldPositionToNode(Grid & grid, Vec2 position);

	};

	static GridSystem gridSystem;
	


}

#endif
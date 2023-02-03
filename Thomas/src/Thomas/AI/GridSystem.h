/******************************************************************************/
/*!
\file   GridSystem.cpp
\author Keith Lua
\par    email: weijiekeith.lua\@digipen.edu
\par    DigiPen login: weijiekeith.lua
\par    Course: CSD-2125 HLP3
\date   3/2/2023
\brief
	This file is the interface of the Grid System

*/
/******************************************************************************/


#pragma once

#include "thpch.h"
#include "Thomas/AI/Grid.h"

#include "Thomas/Math/Vector2D.h"

#include "Thomas/AI/Node.h"


namespace Thomas
{
	class GridSystem
	{
	public:

		//A vector containing the obstacles in the scnene
		std::vector<AStarPathfindingObstacle*> obstacles;

		void SetGridParameters(Grid & grid, Vec2 pGridWorldSize, float pNodeRadius);


		//This allows the user to get the Node in the grid using bottom left coordinates by converting them to row major order coordinate index
		Node* GetNodeFromGrid(Grid & grid, int x, int y);

		//This allows the user to get the const Node in the grid using bottom left coordinates by converting them to row major order coordinate index
		Node* GetNodeFromGrid(Grid & grid, int x, int y) const;


		//This will add the neighbours to the grid
		void AddNeighboursToGrid(Grid& grid);

		//This will add the neighbours of the parameter node to a 
		//vector of Node * neighbours which is a member variable of the parameter node
		void AddNeighbours(Grid& grid, Node* node);

		//This function adds obstacle to the grid
		void AddObstacleToGrid(Grid & grid, AStarPathfindingObstacle & obstacle);

		//We will create a Grid which is represented as a vector of vector of Node *
		void CreateGrid(Grid & grid);

		//This function will take the world position of the object and then return the corresponding Node's coordinate index in the grid
		Vec2 WorldPositionToNodeIndex(Grid & grid, Vec2 position);

		//This function removes obstacle from the grid
		void RemoveObstacleFromGrid(Grid & grid, AStarPathfindingObstacle& obstacle);

		//This function updates obstacle from the grid
		void UpdateObstacleInGrid(Grid& grid, AStarPathfindingObstacle& obstacle);

		//This function clears the grid
		void ClearGrid(Grid& grid);

		//This function will take the world position of the object and return the corresponding Node in the grid
		Node* WorldPositionToNode(Grid & grid, Vec2 position);

	};

	//So that it can be accessed globally.
	extern GridSystem gridSystem;
	


}


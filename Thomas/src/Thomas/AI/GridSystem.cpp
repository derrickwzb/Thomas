/******************************************************************************/
/*!
\file   GridSystem.cpp
\author Keith Lua
\par    email: weijiekeith.lua\@digipen.edu
\par    DigiPen login: weijiekeith.lua
\par    Course: CSD-2125 HLP3
\date   3/2/2023
\brief
	This file is the implementation of a Grid System with functions that
	manipulates the Grid.

*/
/******************************************************************************/



#include "thpch.h"
#include "Thomas/AI/Grid.h"
#include "AStarPathfindingObstacle.h"
#include "Thomas/Math/Vector2D.h"
#include "Thomas/Scene/Entity.h"
#include "Thomas/AI/Node.h"
#include "Thomas/AI/GridSystem.h"

namespace Thomas
{
	GridSystem gridSystem;
	//initialises the grid's size(x:width, y:height) and the radius of the nodes and the corresponding diameter
	//We will also get grid width and grid height which is the number of nodes for that made up the width and height of the grid
	void GridSystem::SetGridParameters(Grid & grid, Vec2 pGridWorldSize, float pNodeRadius)
	{
		grid.gridWorldSize = pGridWorldSize;
		grid.nodeRadius = pNodeRadius;
		grid.nodeDiameter = pNodeRadius * 2.0f;

		//Number of nodes that make up the width of the grid
		grid.gridWidth = (int)(pGridWorldSize.x / grid.nodeDiameter);
		
		//Number of nodes that made up the height of the grid
		grid.gridHeight = (int)(pGridWorldSize.y / grid.nodeDiameter);


	}




	//This allows the user to get the Node in the grid using bottom left coordinates by converting them to row major order coordinate index
	Node* GridSystem::GetNodeFromGrid(Grid & grid, int x, int y)
	{
		//int convertedY = grid.gridHeight - 1 - y;

		return grid.nodeGrids[y][x];
	}

	//This allows the user to get the const Node in the grid using bottom left coordinates by converting them to row major order coordinate index
	Node* GridSystem::GetNodeFromGrid(Grid & grid, int x, int y) const
	{
		//int convertedY = grid.gridHeight - 1 - y;
		return grid.nodeGrids[y][x];
	}

	//This will add the neighbours to the grid
	void GridSystem::AddNeighboursToGrid(Grid & grid)
	{
		for (auto const& row : grid.nodeGrids)
		{
			for (auto const& elem : row)
			{
				gridSystem.AddNeighbours(grid, elem);

			}

		}
	}


	//This will add the neighbours of the parameter node to a 
	//vector of Node * neighbours which is a member variable of the parameter node
	void GridSystem::AddNeighbours( Grid & grid, Node* node)
	{
		//The index above the current node
		int top = node->gridY - 1;

		//The index left of the current node
		int left = node->gridX - 1;

		//The index right of the current node
		int right = node->gridX + 1;

		//The index below the current node
		int bottom = node->gridY + 1;


		//Checking if top index is within range
		if (top  >= 0)
		{
			//Checking if left is  within range
			if (left  >= 0)
			{
				//Top Left Node
				Node* neighbourNodeTopLeft = GetNodeFromGrid(grid, left, top);
				node->neighbours.push_back(neighbourNodeTopLeft);



			}
			Node* neighbourNodeTop = GetNodeFromGrid(grid, node->gridX, top);
			node->neighbours.push_back(neighbourNodeTop); //Top

			//Checking if right is within range
			if (right < grid.gridWidth)
			{
				//Top Right Node
				Node* neighbourNodeTopRight = GetNodeFromGrid(grid, right, top);
				node->neighbours.push_back(neighbourNodeTopRight);

			}
		}
		//Checking if left is within range
		if (left >= 0)
		{
			//Left Node
			Node* neighbourNodeLeft = GetNodeFromGrid(grid, left, node->gridY);
			node->neighbours.push_back(neighbourNodeLeft);
		}

		//Checking if right is within range
		if (right < grid.gridWidth)
		{
			//Right Node
			Node* neighbourNodeRight = GetNodeFromGrid(grid, right, node->gridY);
			node->neighbours.push_back(neighbourNodeRight);
		}

		//Checking if bottom is within range
		if (bottom < grid.gridHeight)
		{
			//Checking if left is within range
			if (left >= 0)
			{
				//Bottom Left Node
				Node* neighbourNodeBottomLeft = GetNodeFromGrid(grid, left, bottom);
				node->neighbours.push_back(neighbourNodeBottomLeft);
			}

			Node* neighbourNodeBottom = GetNodeFromGrid(grid, node->gridX, bottom);
			node->neighbours.push_back(neighbourNodeBottom);

			//Checking if right is within range
			if (right < grid.gridWidth)
			{
				//Bottom Right Node
				Node* neighbourNodeBottomRight = GetNodeFromGrid(grid, right, bottom);
				node->neighbours.push_back(neighbourNodeBottomRight); //Bottom Right
			}
		}
	}

	void GridSystem::AddObstacleToGrid(Grid & grid, AStarPathfindingObstacle & obstacle)
	{
		std::cout << "AddObstacleToGrid" << "\n";
		if (obstacle.hasChanged == true)
		{
			
			std::cout << "SizeOfObstacle: " << obstacles.size() << "\n";
			obstacle.prevPosition = obstacle.position;
			obstacle.hasChanged = false;

		}
		


		for (auto row : grid.nodeGrids)
		{
			for (Node* node : row)
			{
				if (node->gridY <= (int)(WorldPositionToNodeIndex(grid, obstacle.position + obstacle.size / 2).y) && node->gridY >= (int)(WorldPositionToNodeIndex(grid, obstacle.position - obstacle.size / 2).y)

					&& node->gridX <= (int)(WorldPositionToNodeIndex(grid, obstacle.position + obstacle.size / 2).x) && node->gridX >= (int)(WorldPositionToNodeIndex(grid, obstacle.position - obstacle.size / 2).x))
				{

					node->obstacleIDs.push_back(obstacle.ID);

					std::cout << "Node Index (" << node->gridX<< "," << node->gridY<< ") ID: " << obstacle.ID << " |";
					std::cout << "Node World Position(" << node->position.x << "," << node->position.y << ") ID: " << obstacle.ID << "\n";
					std::cout << "Object Position(" << obstacle.position.x << "," << obstacle.position.y << ") ID: " << obstacle.ID << "\n";
					node->blocked = true;

				}

			}
		}
		std::cout << "\n";
	}

	//This function removes obstacle from the grid
	void GridSystem::RemoveObstacleFromGrid(Grid& grid, AStarPathfindingObstacle& obstacle)
	{
		std::cout << "RemoveObstacleFromGrid" << "\n";

		for (auto row : grid.nodeGrids)
		{
			for (auto node : row)
			{
				if (node->blocked == true)
				{
					if (!node->obstacleIDs.empty())
					{
						for (size_t i = 0; i < node->obstacleIDs.size(); ++i)
						{
							if (node->obstacleIDs[i] == obstacle.ID)
							{
								std::cout << "(" << node->gridX << "," << node->gridY << ") ID: " << node->obstacleIDs[i] << "\n";
								std::vector<int>::iterator it = node->obstacleIDs.begin();
								node->obstacleIDs.erase(it + i);
							}
						}
					}


					if (node->obstacleIDs.empty())
					{
						node->blocked = false;

					}
				}
			}
		}
		for (size_t i = 0; i < gridSystem.obstacles.size(); ++i)
		{
			if (gridSystem.obstacles[i]->ID == obstacle.ID)
			{
				std::vector<AStarPathfindingObstacle*>::iterator it = gridSystem.obstacles.begin();
				gridSystem.obstacles.erase(it + i);
			}

		}
	}

	//We will create a Grid which is stored as a vector of vector of Node *
	void GridSystem::CreateGrid(Grid & grid)
	{
		std::cout << "CreateGrid" << "\n";
		for (int y = 0; y < grid.gridHeight; ++y)
		{
			std::vector<Node*> rowGrids{};
			for (int x = 0; x < grid.gridWidth; ++x)
			{
				//We will initialise their global positions which takes into account the grid origin
				Vec2 globalPosition{ (float)(grid.nodeRadius + (x * grid.nodeDiameter)),(float)(grid.nodeRadius +  (y * grid.nodeDiameter)) };
				//We will initialize their coordinate index in bottom left coordinate system
				Node* node = new Node(false, (grid.origin + globalPosition), x, y);

				std::cout << "(" << node->position.x << "," << node->position.y << ") ";

				//Adding the nodes in the the row vector
				rowGrids.push_back(node);

			}

			std::cout << "\n";
			//Adding the row vector into the node grids vector to create a 2D array
			grid.nodeGrids.push_back(rowGrids);
		}
	    std::cout << "\n";
	}

	//This function will take the world position of the object and then return the corresponding Node's coordinate index in the grid
	Vec2 GridSystem::WorldPositionToNodeIndex(Grid & grid, Vec2 position)
	{
		//The relative x and y index of the Node in bottom left coordinate system
		int relativeDistX = (int)((position.x - grid.origin.x) / grid.nodeDiameter);
		int relativeDistY = (int)((position.y - grid.origin.y) / grid.nodeDiameter);

		//The Node index in the grid (bottom left coordinate system)
		Vec2 NodeIndex{ (float)relativeDistX , (float)relativeDistY };
		return NodeIndex;
	}

	//This function will take the world position of the object and return the corresponding Node in the grid
	Node* Thomas::GridSystem::WorldPositionToNode(Grid & grid, Vec2 position)
	{
		//std::cout << "Origin (" << grid.origin.x << "," << grid.origin.y << ")\n";
		int relativeDistX = (int)((position.x - grid.origin.x) / grid.nodeDiameter);

		//The relative coordinate index of the Node in bottom left coordinate system
		int relativeDistY = (int)((position.y - grid.origin.y) / grid.nodeDiameter);

		if (relativeDistX < 0)
		{
			return nullptr;
		}

		if (relativeDistX >= grid.gridWidth)
		{
			return nullptr;
		}

		if (relativeDistY < 0)
		{
			return nullptr;
		}


		if (relativeDistY >= grid.gridHeight)
		{
			return nullptr;
		}


		//The Node in the grid in bottom left coordinate system
		return GetNodeFromGrid(grid, (int)relativeDistX, (int)relativeDistY);

	}

	//This function updates obstacle from the grid
	void GridSystem::UpdateObstacleInGrid(Grid& grid, AStarPathfindingObstacle& obstacle)
	{
		std::cout << "UpdateObstacleInGrid" << "\n";
		if (obstacle.position.x != obstacle.prevPosition.x && obstacle.position.y != obstacle.prevPosition.y)
		{
			
			RemoveObstacleFromGrid(grid, obstacle);
			
			obstacle.hasChanged = true;
			AddObstacleToGrid(grid, obstacle);
		}
		


	}

	//This function clears the grid
	void GridSystem::ClearGrid(Grid & grid)
	{
		std::cout << "ClearGrid" << "\n";
		if (!grid.nodeGrids.empty())
		{
			for (auto const& iterator : grid.nodeGrids)
			{
				for (Node* node : iterator)
				{
					delete node;
				}
			}
		}
		grid.nodeGrids.clear();
	}

}
#include "thpch.h"
#include "Thomas/AI/Grid.h"

#include "Thomas/Math/Vector2D.h"

#include "Thomas/AI/Node.h"
//#include <iostream>
#include "Thomas/AI/GridSystem.h"

namespace Thomas
{

	//Constructor initialises the grid's size(x:width, y:height) and the radius of the nodes and the corresponding diameter
	//We will also get grid width and grid height which is the number of nodes for that made up the width and height of the grid
	// 
	void GridSystem::SetGridParameters(Grid & grid, Vec2 pGridWorldSize, float pNodeRadius)
	{
		grid.gridWorldSize = pGridWorldSize;
		grid.nodeRadius = pNodeRadius;
		grid.nodeDiameter = pNodeRadius * 2;

		//Number of nodes that make up the width of the grid
		grid.gridWidth = (int)(pGridWorldSize.x / grid.nodeDiameter);

		//Number of nodes that made up the height of the grid
		grid.gridHeight = (int)(pGridWorldSize.y / grid.nodeDiameter);
	}


	//This allows the user to get the Node in the grid using bottom left coordinates by converting them to row major order coordinate index
	Node* GridSystem::GetNodeFromGrid(Grid & grid, int x, int y)
	{
		int convertedY = grid.gridHeight - 1 - y;
		return grid.nodeGrids[convertedY][x];
	}

	//This allows the user to get the const Node in the grid using bottom left coordinates by converting them to row major order coordinate index
	Node* GridSystem::GetNodeFromGrid(Grid & grid, int x, int y) const
	{
		int convertedY = grid.gridHeight - 1 - y;
		return grid.nodeGrids[convertedY][x];
	}

	//This will add the neighbours of the parameter node to a 
	//vector of Node * neighbours which is 0a member variable of the parameter node
	//We are using the bottom left coordinate system in the calculation
	void GridSystem::AddNeighbours( Grid & grid, Node* node)
	{
		//The index above the current node
		int top = node->gridY + 1;

		//The index left of the current node
		int left = node->gridX - 1;

		//The index right of the current node
		int right = node->gridX + 1;

		//The index below the current node
		int bottom = node->gridY - 1;

		//std::cout << "(" << node->gridX << "," <<  node->gridY << ")";

		//Checking if top index is within range
		if (top < grid.gridHeight)
		{
			//Checking if left is  within range
			if (left >= 0)
			{
				//Top Left Node
				Node* neighbourNodeTopLeft = GetNodeFromGrid(grid, left, top);
				//std::cout << "(" << neighbourNodeTopLeft->gridX << "," << neighbourNodeTopLeft->gridY << ") ";
				node->neighbours.push_back(neighbourNodeTopLeft);



			}
			Node* neighbourNodeTop = GetNodeFromGrid(grid, node->gridX, top);
			//std::cout << "(" << neighbourNodeTop->gridX << "," << neighbourNodeTop->gridY << ") ";
			node->neighbours.push_back(neighbourNodeTop); //Top

			//Checking if right is within range
			if (right < grid.gridWidth)
			{
				//Top Right Node
				Node* neighbourNodeTopRight = GetNodeFromGrid(grid, right, top);
				//std::cout << "(" << neighbourNodeTopRight->gridX << "," << neighbourNodeTopRight->gridY << ") ";
				node->neighbours.push_back(neighbourNodeTopRight);

			}
		}
		//Checking if left is within range
		if (left >= 0)
		{
			//Left Node
			Node* neighbourNodeLeft = GetNodeFromGrid(grid, left, node->gridY);
			//std::cout << "(" << neighbourNodeLeft->gridX << "," << neighbourNodeLeft->gridY << ") ";
			node->neighbours.push_back(neighbourNodeLeft);
		}

		//Checking if right is within range
		if (right < grid.gridWidth)
		{
			//Right Node
			Node* neighbourNodeRight = GetNodeFromGrid(grid, right, node->gridY);
			//std::cout << "(" << neighbourNodeRight->gridX << "," << neighbourNodeRight->gridY << ") ";
			node->neighbours.push_back(neighbourNodeRight);
		}

		//Checking if bottom is within range
		if (bottom >= 0)
		{
			//Checking if left is within range
			if (left >= 0)
			{
				//Bottom Left Node
				Node* neighbourNodeBottomLeft = GetNodeFromGrid(grid, left, bottom);
				//std::cout << "(" << neighbourNodeBottomLeft->gridX << "," << neighbourNodeBottomLeft->gridY << ") ";
				node->neighbours.push_back(neighbourNodeBottomLeft);
			}

			Node* neighbourNodeBottom = GetNodeFromGrid(grid, node->gridX, bottom);
			//std::cout << "(" << neighbourNodeBottom->gridX << "," << neighbourNodeBottom->gridY << ") ";
			node->neighbours.push_back(neighbourNodeBottom);

			//Checking if right is within range
			if (right < grid.gridWidth)
			{
				//Bottom Right Node
				Node* neighbourNodeBottomRight = GetNodeFromGrid(grid, right, bottom);
				//std::cout << "(" << neighbourNodeBottomRight->gridX << "," << neighbourNodeBottomRight->gridY << ") ";
				node->neighbours.push_back(neighbourNodeBottomRight); //Bottom Right
			}
		}
		//std::cout << "\n";
	}

	void GridSystem::AddObstacles(Grid & grid, AStarPathfindingObstacle obstacle)
	{
		for (auto row : grid.nodeGrids)
		{
			for (Node* node : row)
			{
				if (node->gridY <= (int)WorldPositionToNodeIndex(grid, obstacle.position - obstacle.size / 2).y && node->gridY >= (int)WorldPositionToNodeIndex(grid, obstacle.position - obstacle.size / 2).y

					&& node->gridX <= (int)WorldPositionToNodeIndex(grid, obstacle.position - obstacle.size / 2).x && node->gridX >= (int)WorldPositionToNodeIndex(grid, obstacle.position - obstacle.size / 2).x)
				{
					node->blocked = true;
					std::cout << "Blocked Position: (" << node->position.x << "," << node->position.y << ")\n";
					//std::cout << 
					 //break;
				}

			}
		}
	}

	//We will create a Grid which is stored as a vector of vector of Node *
	void GridSystem::CreateGrid(Grid & grid)
	{

		for (int y = 0; y < grid.gridHeight; ++y)
		{
			std::vector<Node*> rowGrids{};
			for (int x = 0; x < grid.gridWidth; ++x)
			{
				//We will initialise their global positions which takes into account the grid origin
				Vec2 globalPosition{ (float)(grid.nodeRadius + (x * grid.nodeDiameter)),(float)(grid.nodeRadius + ((grid.gridHeight - 1 - y) * grid.nodeDiameter)) };
				//std::cout << "(" << globalPosition.x << "," << globalPosition.y << ")";
				//We will initialize their coordinate index in bottom left coordinate system
				Node* node = new Node(false, (grid.origin + globalPosition), x, (grid.gridHeight - 1 - y));
				//std::cout << "(" << node->gridX << "," << node->gridY << ")";
				//Adding the nodes in the the row vector
				rowGrids.push_back(node);

			}

			//std::cout << "\n";
			//Adding the row vector into the node grids vector to create a 2D array
			grid.nodeGrids.push_back(rowGrids);
		}
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
		std::cout << "Origin (" << grid.origin.x << "," << grid.origin.y << ")\n";
		int relativeDistX = (int)((position.x - grid.origin.x) / grid.nodeDiameter);

		//The relative coordinate index of the Node in bottom left coordinate system
		int relativeDistY = (int)((position.y - grid.origin.y) / grid.nodeDiameter);

		//std::cout << "World Position: (" << position.x << "," << position.y << ")\n";
		//std::cout << "Origin: (" << origin.x << "," << origin.y << ")\n";

		//std::cout << "NodeDiameter: " << nodeDiameter << "\n";
		//std::cout << "(X: " << relativeDistX << ", Y: " << relativeDistY << ") \n";
		//The Node in the grid in bottom left coordinate system
		return GetNodeFromGrid(grid, (int)relativeDistX, (int)relativeDistY);

	}

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
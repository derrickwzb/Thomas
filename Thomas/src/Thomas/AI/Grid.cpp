#include "thpch.h"
#include "Thomas/AI/Grid.h"

#include "Thomas/Math/Vector2D.h"

#include "Thomas/AI/Node.h"
//#include <iostream>


namespace Thomas
{

	//Constructor initialises the grid's size(x:width, y:height) and the radius of the nodes and the corresponding diameter
	//We will also get grid width and grid height which is the number of nodes for that made up the width and height of the grid
	Grid::Grid(Vec2 pGridWorldSize, float pNodeRadius)
	{
		gridWorldSize = pGridWorldSize;
		nodeRadius = pNodeRadius;
		nodeDiameter = nodeRadius * 2;
		
		//Number of nodes that make up the width of the grid
		gridWidth = (int)(pGridWorldSize.x / nodeDiameter);

		//Number of nodes that made up the height of the grid
		gridHeight = (int)(pGridWorldSize.y / nodeDiameter);
	}

	//This allows the user to get the Node in the grid using bottom left coordinates by converting them to row major order coordinate index
	Node* Grid::GetNodeFromGrid(int x, int y)
	{
		int convertedY = gridHeight - 1 - y;
		return nodeGrids[convertedY][x];
	}
	
	//This allows the user to get the const Node in the grid using bottom left coordinates by converting them to row major order coordinate index
	Node* Grid::GetNodeFromGrid(int x, int y) const
	{
		int convertedY = gridHeight - 1 - y;
		return nodeGrids[convertedY][x];
	}

	//This will add the neighbours of the parameter node to a 
	//vector of Node * neighbours which is 0a member variable of the parameter node
	//We are using the bottom left coordinate system in the calculation
	void Grid::AddNeighbours(Node * node)
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
		if (top < gridHeight)
		{
			//Checking if left is  within range
			if (left >= 0)
			{
				//Top Left Node
				Node* neighbourNodeTopLeft = GetNodeFromGrid(left, top);
				//std::cout << "(" << neighbourNodeTopLeft->gridX << "," << neighbourNodeTopLeft->gridY << ") ";
				node->neighbours.push_back(neighbourNodeTopLeft); 
				


			}
			Node* neighbourNodeTop = GetNodeFromGrid(node->gridX, top);
			//std::cout << "(" << neighbourNodeTop->gridX << "," << neighbourNodeTop->gridY << ") ";
			node->neighbours.push_back(neighbourNodeTop); //Top

			//Checking if right is within range
			if (right < gridWidth)
			{
				//Top Right Node
				Node* neighbourNodeTopRight = GetNodeFromGrid(right, top);
				//std::cout << "(" << neighbourNodeTopRight->gridX << "," << neighbourNodeTopRight->gridY << ") ";
				node->neighbours.push_back(neighbourNodeTopRight); 

			}
		}
		//Checking if left is within range
		if (left >= 0)
		{
			//Left Node
			Node* neighbourNodeLeft = GetNodeFromGrid(left, node->gridY);
			//std::cout << "(" << neighbourNodeLeft->gridX << "," << neighbourNodeLeft->gridY << ") ";
			node->neighbours.push_back(neighbourNodeLeft);
		}

		//Checking if right is within range
		if (right < gridWidth)
		{
			//Right Node
			Node* neighbourNodeRight = GetNodeFromGrid(right, node->gridY);
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
				Node* neighbourNodeBottomLeft = GetNodeFromGrid(left, bottom);
				//std::cout << "(" << neighbourNodeBottomLeft->gridX << "," << neighbourNodeBottomLeft->gridY << ") ";
				node->neighbours.push_back(neighbourNodeBottomLeft); 
			}

			Node* neighbourNodeBottom = GetNodeFromGrid(node->gridX, bottom);
			//std::cout << "(" << neighbourNodeBottom->gridX << "," << neighbourNodeBottom->gridY << ") ";
			node->neighbours.push_back(neighbourNodeBottom); 

			//Checking if right is within range
			if (right < gridWidth)
			{
				//Bottom Right Node
				Node* neighbourNodeBottomRight = GetNodeFromGrid(right, bottom);
				//std::cout << "(" << neighbourNodeBottomRight->gridX << "," << neighbourNodeBottomRight->gridY << ") ";
				node->neighbours.push_back(neighbourNodeBottomRight); //Bottom Right
			}
		}
		//std::cout << "\n";
	}
	
	//We will create a Grid which is stored as a vector of vector of Node *
	void Grid::CreateGrid()
	{

		for (int y = 0; y < gridHeight; ++y)
		{
			std::vector<Node*> rowGrids{};
			for (int x = 0; x < gridWidth; ++x)
			{
				//We will initialise their global positions which takes into account the grid origin
				Vec2 globalPosition{ (float)(nodeRadius + (x * nodeDiameter)),(float)(nodeRadius + ((gridHeight - 1 - y) * nodeDiameter)) };
				//std::cout << "(" << globalPosition.x << "," << globalPosition.y << ")";
				//We will initialize their coordinate index in bottom left coordinate system
				Node* node = new Node(false, (origin + globalPosition), x, (gridHeight - 1 - y));
				//std::cout << "(" << node->gridX << "," << node->gridY << ")";
				//Adding the nodes in the the row vector
				rowGrids.push_back(node);

			}

			std::cout << "\n";
			//Adding the row vector into the node grids vector to create a 2D array
			nodeGrids.push_back(rowGrids);
		}
	}

	//This function will take the world position of the object and then return the corresponding Node's coordinate index in the grid
	Vec2 Grid::WorldPositionToNodeIndex(Vec2 position)
	{
		//The relative x and y index of the Node in bottom left coordinate system
		int relativeDistX = (int)((position.x - origin.x) / nodeDiameter);
		int relativeDistY = (int)((position.y - origin.y) / nodeDiameter);

		//The Node index in the grid (bottom left coordinate system)
		Vec2 NodeIndex{ (float)relativeDistX , (float)relativeDistY };
		return NodeIndex;
	}

	//This function will take the world position of the object and return the corresponding Node in the grid
	Node* Thomas::Grid::WorldPositionToNode(Vec2 position)
	{
		int relativeDistX = (int)((position.x - origin.x) / nodeDiameter);
		
		//The relative coordinate index of the Node in bottom left coordinate system
		int relativeDistY = (int)((position.y - origin.y) / nodeDiameter);

		//std::cout << "World Position: (" << position.x << "," << position.y << ")\n";
		//std::cout << "Origin: (" << origin.x << "," << origin.y << ")\n";

		//std::cout << "NodeDiameter: " << nodeDiameter << "\n";
		//std::cout << "(X: " << relativeDistX << ", Y: " << relativeDistY << ") \n";
		//The Node in the grid in bottom left coordinate system
		return GetNodeFromGrid((int)relativeDistX, (int)relativeDistY);

	}

	//The destructor will clear the grid of Node *
	Grid::~Grid()
	{
		/*for (auto it : nodeGrids)
		{
			for (Node * node: it)
			{
				delete node;
			}


		}*/
		//nodeGrids.clear();
	}
	
}
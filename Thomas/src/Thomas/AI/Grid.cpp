
#include "Grid.hpp"
#include <iostream>
#include "Node.hpp"

namespace Thomas
{
	Grid::Grid(Vec2 pGridWorldSize, float pNodeRadius)
	{
		gridWorldSize = pGridWorldSize;
		nodeRadius = pNodeRadius;
		nodeDiameter = nodeRadius * 2;
		gridWidth = (int)(gridWorldSize.x / nodeDiameter);
		gridHeight = (int)(gridWorldSize.y / nodeDiameter);
	}

	Node* Grid::GetNodeFromGrid(int x, int y)
	{
		int convertedY = gridHeight - 1 - y;
		return nodeGrids[convertedY][x];
	}
	
	Node* Grid::GetNodeFromGrid(int x, int y) const
	{
		int convertedY = gridHeight - 1 - y;
		return nodeGrids[convertedY][x];
	}

	void Grid::AddNeighbours(Node * node)
	{

		int top = node->gridY + 1;
		int left = node->gridX - 1;
		int right = node->gridX + 1;
		int bottom = node->gridY - 1;
		if (top < gridHeight)
		{
			if (left >= 0)
			{

				node->neighbours.push_back(GetNodeFromGrid(left, top) ); //Top Left
			}
			node->neighbours.push_back(GetNodeFromGrid(node->gridX, top)); //Top

			if (right < gridWidth)
			{
				node->neighbours.push_back(GetNodeFromGrid(right, top)); //Top Right

			}
		}
		if (left >= 0)
		{
			node->neighbours.push_back(GetNodeFromGrid(left, node->gridY));//Left
		}
		if (right < gridWidth)
		{
			//Node * node = nodes[xIndex][right];
			node->neighbours.push_back(GetNodeFromGrid(right, node->gridY));//Right
		}
		if (bottom >= 0)
		{
			if (left >= 0)
			{
				node->neighbours.push_back(GetNodeFromGrid(left, bottom)); //Bottom Left
			}
			node->neighbours.push_back(GetNodeFromGrid(node->gridX, bottom)); //Bottom

			if (right < gridWidth)
			{
				node->neighbours.push_back(GetNodeFromGrid(right, bottom)); //Bottom Right
			}
		}

	}
	

	void Grid::CreateGrid()
	{

		for (int y = 0; y < gridHeight; ++y)
		{
			std::vector<Node*> rowGrids{};
			for (int x = 0; x < gridWidth; ++x)
			{
				Vec2 globalPosition{ (float)(nodeRadius + (x * nodeDiameter)),(float)(nodeRadius + ((gridHeight - 1 - y) * nodeDiameter)) };
			
				//std::cout << "( " << y << "," << x << ") ";


				Node* node = new Node(false, (origin + globalPosition), x, (gridHeight - 1 - y));
			
				std::cout << "(" << node->gridX << ": " << globalPosition.x << ", " << node->gridY << ": " << globalPosition.y << ") ";
				



				rowGrids.push_back(node);

			}
			nodeGrids.push_back(rowGrids);
			std::cout << "\n";
		}
	}

	Node* Grid::WorldPostionToNode(Vec2 position)
	{
		float relativeDistX = (position.x - origin.x) / nodeDiameter;
		float relativeDistY = (position.y - origin.y) / nodeDiameter;
		
		return GetNodeFromGrid((int)relativeDistX, (int)relativeDistY);

	}
}
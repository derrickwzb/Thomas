
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

	Node* Grid::GetActualNode(int actualX, int actualY)
	{
		return nodeGrids[actualY][actualX];
	}

	Node* Grid::GetActualNode(int actualX, int actualY) const
	{
		return nodeGrids[actualY][actualX];
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

		std::cout << "(" << node->gridX << "," <<  node->gridY << ")";
		if (top < gridHeight)
		{
			if (left >= 0)
			{
				Node* neighbourNodeTopLeft = GetNodeFromGrid(left, top);
				std::cout << "(" << neighbourNodeTopLeft->gridX << "," << neighbourNodeTopLeft->gridY << ") ";
				node->neighbours.push_back(neighbourNodeTopLeft); //Top Left
				


			}
			Node* neighbourNodeTop = GetNodeFromGrid(node->gridX, top);
			std::cout << "(" << neighbourNodeTop->gridX << "," << neighbourNodeTop->gridY << ") ";
			node->neighbours.push_back(neighbourNodeTop); //Top

			if (right < gridWidth)
			{
				Node* neighbourNodeTopRight = GetNodeFromGrid(right, top);
				std::cout << "(" << neighbourNodeTopRight->gridX << "," << neighbourNodeTopRight->gridY << ") ";
				node->neighbours.push_back(neighbourNodeTopRight); //Top Right

			}
		}
		if (left >= 0)
		{

			Node* neighbourNodeLeft = GetNodeFromGrid(left, node->gridY);
			std::cout << "(" << neighbourNodeLeft->gridX << "," << neighbourNodeLeft->gridY << ") ";
			node->neighbours.push_back(neighbourNodeLeft);//Left
		}
		if (right < gridWidth)
		{
			Node* neighbourNodeRight = GetNodeFromGrid(right, node->gridY);
			std::cout << "(" << neighbourNodeRight->gridX << "," << neighbourNodeRight->gridY << ") ";
			node->neighbours.push_back(neighbourNodeRight);//Right
		}
		if (bottom >= 0)
		{
			if (left >= 0)
			{
				Node* neighbourNodeBottomLeft = GetNodeFromGrid(left, bottom);
				std::cout << "(" << neighbourNodeBottomLeft->gridX << "," << neighbourNodeBottomLeft->gridY << ") ";
				node->neighbours.push_back(neighbourNodeBottomLeft); //Bottom Left
			}

			Node* neighbourNodeBottom = GetNodeFromGrid(node->gridX, bottom);
			std::cout << "(" << neighbourNodeBottom->gridX << "," << neighbourNodeBottom->gridY << ") ";
			node->neighbours.push_back(neighbourNodeBottom); //Bottom

			if (right < gridWidth)
			{
				Node* neighbourNodeBottomRight = GetNodeFromGrid(right, bottom);
				std::cout << "(" << neighbourNodeBottomRight->gridX << "," << neighbourNodeBottomRight->gridY << ") ";
				node->neighbours.push_back(neighbourNodeBottomRight); //Bottom Right
			}
		}
		std::cout << "\n";
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
			
				std::cout << "(i" << y << "|x" << node->gridX << ", j" << x << "|y" << node->gridY << " " << ") ";
				



				rowGrids.push_back(node);

			}
			nodeGrids.push_back(rowGrids);
			std::cout << "\n";
		}
	}

	Vec2 Grid::WorldPositionToNodeIndex(Vec2 position)
	{
		int relativeDistX = (int)((position.x - origin.x) / nodeDiameter);
		int relativeDistY = (int)((position.y - origin.y) / nodeDiameter);
		Vec2 NodeIndex{ (float)relativeDistX , (float)relativeDistY };
		return NodeIndex;
	}

	Node* Grid::WorldPositionToNode(Vec2 position)
	{
		float relativeDistX = (position.x - origin.x) / nodeDiameter;
		float relativeDistY = (position.y - origin.y) / nodeDiameter;
		
		return GetNodeFromGrid((int)relativeDistX, (int)relativeDistY);

	}

	Grid::~Grid()
	{
		
		/*for (int y = 0; y < gridHeight; ++y)
		{
			for (int x = 0; x < gridWidth; ++x)
			{
				Node * node = GetNodeFromGrid(x, y);
				delete(node);

			}

		}*/

		nodeGrids.clear();
	}
	
}
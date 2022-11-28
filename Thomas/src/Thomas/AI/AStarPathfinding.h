
#ifndef ASTAR_HPP
#define ASTAR_HPP
#include "thpch.h"
//#include <algorithm>

#include "Thomas/AI/Node.h"
#include "Thomas/AI/Grid.h"
#include "Thomas/Math/Vector2D.h"




namespace Thomas {
	//class Node;
	//class Grid;
	//class Vec2;

	class AStarPathfinding
	{
	public:

		//This is the shortest path to the target position
		std::vector<Node*> path;

		//This are the nodes that we have yet to visit
		std::vector<Node*> openSet;

		//This are the nodes that have been visited
		std::vector<Node*> closedSet;

		//This is the pointer to the node grid
		Grid * grid;
		
		//This is the constructor
		AStarPathfinding() : path{}, openSet{}, closedSet{}, grid{ nullptr } {};

		//This is the destructor that will clear the vectors for the path, closed set and open set
		~AStarPathfinding();

		//This is the A Star Pathfinding algorithm
		void AStarPathSearch(Vec2 startPos, Vec2 endPos);

		//Get the distance between the nodes and assign the costs
		int GetDistance(Node* nodeA, Node* nodeB);

		//We will create the path from the start node to the end node
		void RetracePath(Node * startNode, Node * endNode);

		//We will reset the path search by clearing the vectors for the path, closed set and open set
		void ResetPathSearch();

	};
	bool lowestFcost(const Node* first, const Node* second)
	{
		return (*first).Fcost < (*second).Fcost;
	}

	//Functor to find if node exist in the grid
	class Contains
	{
		Node* nodeToFind;

	public:
		Contains(Node* node) : nodeToFind(node) {}

		bool operator()(const Node* node) const
		{
			return (*node == *nodeToFind);
		}
	};

	//This is the A Star Pathfinding algorithm that will find the shortest path to the end position
	void  AStarPathfinding::AStarPathSearch(Vec2 startPos, Vec2 endPos)
	{
		Node* start = grid->WorldPositionToNode(startPos);
		Node* end = grid->WorldPositionToNode(endPos);
		openSet.push_back(start);
		
		//While the open set is not empty or there no nodes that has not been visited
		while (openSet.size() >0)
		{
			//The current node is the first node in the open set
			Node* current = openSet.front();

			//We will search the open set for a node that has the lowest Fcost or equal Fcost to current node
			//as well as has the lower Hcost compared to the current node
			for (int i = 0; i < openSet.size(); ++i)
			{
				if (openSet[i]->Fcost < current->Fcost || openSet[i]->Fcost == current->Fcost && openSet[i]->Hcost < current->Hcost)
				{
					current = openSet[i];
				}
			}

			//Check if the current node exist in the open set
			auto currentIterator = std::find_if(openSet.begin(), openSet.end(), Contains(current));

			//Remove it from the open set
			openSet.erase(currentIterator);

			//Then add it to the closed set containing the visited nodes
			closedSet.push_back(current);

			//If the current node is the same as the end node
			if (current == end)
			{
				//We will create a path from the start to end
				RetracePath(start, end);
				return;
			}

			//We will check the neighbours of the current Node
			for (Node * neighbour : current->neighbours)
			{
				//If the closed set contains the neighbour or if it is blocked, we will ignore them
				auto closedSetContains = std::find_if(closedSet.begin(), closedSet.end(), Contains(neighbour));
				if (neighbour->blocked == true || closedSetContains != closedSet.end())
				{
					continue;
				}

				//We will calculate the cost of traveling from the starting node to the current node to that neighbour node 
				int newMovementCostToNeighbour = current->Gcost + GetDistance(current, neighbour);

				//If the open set does not contain the neighbour or 
				//If the cost to travel from the starting node to the current node to that neighbour node 
				//is lower than the cost 
				auto openSetDoesNotContains = std::find_if(openSet.begin(), openSet.end(), Contains(neighbour));
				if (newMovementCostToNeighbour < neighbour->Gcost || openSetDoesNotContains == openSet.end())
				{
					neighbour->Gcost = newMovementCostToNeighbour;
					neighbour->Hcost = GetDistance(neighbour, end);
					neighbour->parent = current;
					if (openSetDoesNotContains == openSet.end())
					{
						openSet.push_back(neighbour);

					}
				}
			}

		}
	}

	//We will create the path from the start node to the end node
	void AStarPathfinding::RetracePath(Node * startNode, Node * endNode)
	{
		std::vector<Node*> tempPath{};
		Node * currentNode = endNode;
		while (currentNode != startNode)
		{
			tempPath.push_back(currentNode);
			currentNode = currentNode->parent;

		}
		std::reverse(tempPath.begin(), tempPath.end());
		path = tempPath;
	}

	//Get the distance between the nodes and assign the costs
	int AStarPathfinding::GetDistance(Node* nodeA, Node* nodeB)
	{
		int distX = abs(nodeA->gridX - nodeB->gridX);
		int distY = abs(nodeA->gridY - nodeB->gridY);
		if (distX > distY)
		{
			return 14 * distY + 10 * (distX - distY);

		}
		return 14 * distX + 10 * (distY - distX);
	}

	//We will reset the path search by clearing the vectors for the path, closed set and open set
	void AStarPathfinding::ResetPathSearch()
	{
		path.clear();
		openSet.clear();
		closedSet.clear();
	}

	//This is the destructor that will clear the vectors for the path, closed set and open set
	AStarPathfinding::~AStarPathfinding()
	{


		

		closedSet.clear();

		openSet.clear();

		path.clear();

	


	

	}

}
#endif

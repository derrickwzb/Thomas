#pragma once
#include <algorithm>
#include "Node.hpp"
#include "Grid.hpp"
namespace Thomas {

	class AStarPathfinding
	{


	public:
		std::vector<Node*> path;
		std::vector<Node*> openSet;
		std::vector<Node*> closedSet;
		Grid * grid;
		
		AStarPathfinding() : path{}, openSet{}, closedSet{}, grid{ nullptr } {};
		~AStarPathfinding();
		void AStarPathSearch(Vec2 startPos, Vec2 endPos);
		int GetDistance(Node* nodeA, Node* nodeB);
		void RetracePath(Node * startNode, Node * endNode);
		void ResetPathSearch();

	};
	bool lowestFcost(const Node* first, const Node* second)
	{
		return (*first).Fcost < (*second).Fcost;
	}

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

	void  AStarPathfinding::AStarPathSearch(Vec2 startPos, Vec2 endPos)
	{
		Node* start = grid->WorldPositionToNode(startPos);
		Node* end = grid->WorldPositionToNode(endPos);
		openSet.push_back(start);
		
		while (openSet.size() >0)
		{
			Node* current = openSet.front();
			for (int i = 0; i < openSet.size(); ++i)
			{
				if (openSet[i]->Fcost < current->Fcost || openSet[i]->Fcost == current->Fcost && openSet[i]->Hcost < current->Hcost)
				{
					current = openSet[i];
				}
			}

			auto currentIterator = std::find_if(openSet.begin(), openSet.end(), Contains(current));
			openSet.erase(currentIterator);
			closedSet.push_back(current);

			if (current == end)
			{
				RetracePath(start, end);
				return;
			}


			for (Node * neighbour : current->neighbours)
			{
				auto closedSetContains = std::find_if(closedSet.begin(), closedSet.end(), Contains(neighbour));
				if (neighbour->blocked == true || closedSetContains != closedSet.end())
				{
					continue;
				}

				int newMovementCostToNeighbour = current->Gcost + GetDistance(current, neighbour);
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

	void AStarPathfinding::ResetPathSearch()
	{
		path.clear();
		openSet.clear();
		closedSet.clear();
	}

	AStarPathfinding::~AStarPathfinding()
	{
		closedSet.clear();

		openSet.clear();

		path.clear();

	}

















}

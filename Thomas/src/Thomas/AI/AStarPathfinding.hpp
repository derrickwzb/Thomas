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
	//int FindHeuristicCost(Node const& lhs, Node const& rhs)
	//{
	//	//Vec2 lhsNodePos{ (float)lhs.gridX, (float)lhs.gridY };
	//	//Vec2 rhsNodePos{ (float)rhs.gridX, (float)rhs.gridY };
	//	//int distance = (int)(Vector2DDistance(rhsNodePos, lhsNodePos));
	//	// 
	//	// 
	//	//int distance = abs(lhs.xIndex - rhs.xIndex) + abs(lhs.yIndex - rhs.yIndex);

	//	//sqrt(rhs.position.x)

	//	//return distance;
	//}
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
			
			//std::sort(openSet.begin(), openSet.end(), lowestFcost);
			Node* current = openSet.front();
			for (int i = 0; i < openSet.size(); ++i)
			{
				if (openSet[i]->Fcost < current->Fcost || openSet[i]->Fcost == current->Fcost && openSet[i]->Hcost < current->Hcost)
				{
					current = openSet[i];
				}
			}

			//if (current == end)
			//{
			//	Node* temp = current;
			//	path.push_back(temp);
			//	while (temp->previous)
			//	{
			//		path.push_back(temp->previous);
			//		temp = temp->previous;

			//	}
			//	return true;
			//}

			/*auto begin = openSet.begin();
			openSet.erase(begin);*/
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

				//auto searchResultClosedSet = std::find_if(closedSet.begin(), closedSet.end(), Contains(current->neighbours[i]));
				//int tempGcost = 0;
				////If closed set does not contain the neighbour and if the neighbour is not blocked
				//if (searchResultClosedSet == closedSet.end() && current->neighbours[i]->blocked == false) 
				//{
				//	
				//	tempGcost = current->Gcost + 1;
				//	

				//	auto searchResultOpenSet = std::find_if(openSet.begin(), openSet.end(), Contains(current->neighbours[i]));
				//	bool newPath = false;
				//	if (searchResultOpenSet != openSet.end()) //If open set contains the neighbour
				//	{
				//		if (tempGcost < current->neighbours[i]->Gcost)
				//		{
				//			current->neighbours[i]->Gcost = tempGcost;
				//			newPath = true;
				//		}
				//	}
				//	else
				//	{
				//		current->neighbours[i]->Gcost = tempGcost;
				//		newPath = true;
				//		openSet.push_back(current->neighbours[i]);

				//	}
				//	if (newPath)
				//	{
				//		current->neighbours[i]->Hcost = FindHeuristicCost(*(current->neighbours[i]), *end);
				//		current->neighbours[i]->Fcost = current->neighbours[i]->Gcost + current->neighbours[i]->Hcost;
				//		current->neighbours[i]->parent = current;

				//	}

				//}
			}

		}


		//return false;
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

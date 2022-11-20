#pragma once
#include <algorithm>
#include "Node.hpp"

namespace Thomas {

	class AStarPathfinding
	{


	public:
		std::vector<Node*> path{};
		std::vector<Node*> openSet{};
		std::vector<Node*> closedSet{};

		AStarPathfinding() {};
		bool AStarPathSearch(Node* start, Node* end);
		void ResetPathSearch();

	};
	bool lowestFcost(const Node* first, const Node* second)
	{
		return (*first).Fcost < (*second).Fcost;
	}
	int FindHeuristicCost(Node const& lhs, Node const& rhs)
	{
		Vec2 lhsNodePos{ (float)lhs.gridY, (float)lhs.gridX };
		Vec2 rhsNodePos{ (float)rhs.gridY, (float)rhs.gridX };
		int distance = (int)(Vector2DDistance(lhsNodePos, rhsNodePos));
		//int distance = abs(lhs.xIndex - rhs.xIndex) + abs(lhs.yIndex - rhs.yIndex);

		return distance;
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

	bool AStarPathfinding::AStarPathSearch(Node* start, Node* end)
	{
		
		openSet.push_back(start);
		
		while (!openSet.empty())
		{
			
			std::sort(openSet.begin(), openSet.end(), lowestFcost);
			Node* current = openSet.front();

			if (current == end)
			{
				//path.push_back(current);
				Node* temp = current;
				path.push_back(temp);
				while (temp->previous)
				{
					path.push_back(temp->previous);
					temp = temp->previous;

				}
				return true;
			}

			auto begin = openSet.begin();
			openSet.erase(begin);

			closedSet.push_back(current);

			for (int i = 0; i < current->neighbours.size(); ++i)
			{
				auto searchResultClosedSet = std::find_if(closedSet.begin(), closedSet.end(), Contains(current->neighbours[i]));
				int tempGcost = 0;
				//If closed set does not contain the neighbour and if the neighbour is not blocked
				if (searchResultClosedSet == closedSet.end() && current->neighbours[i]->blocked == false) 
				{
					
					tempGcost = current->Gcost + 1;
					

					auto searchResultOpenSet = std::find_if(openSet.begin(), openSet.end(), Contains(current->neighbours[i]));
					bool newPath = false;
					if (searchResultOpenSet != openSet.end()) //If open set contains the neighbour
					{
						if (tempGcost < current->neighbours[i]->Gcost)
						{
							current->neighbours[i]->Gcost = tempGcost;
							newPath = true;
						}
					}
					else
					{
						current->neighbours[i]->Gcost = tempGcost;
						newPath = true;
						openSet.push_back(current->neighbours[i]);

					}
					if (newPath)
					{
						current->neighbours[i]->Hcost = FindHeuristicCost(*(current->neighbours[i]), *end);
						current->neighbours[i]->Fcost = current->neighbours[i]->Gcost + current->neighbours[i]->Hcost;
						current->neighbours[i]->previous = current;

					}

				}
			}

		}


		return false;
	}

	void AStarPathfinding::ResetPathSearch()
	{
		path.clear();
		openSet.clear();
		closedSet.clear();
	}



















}

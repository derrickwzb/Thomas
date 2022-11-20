#include <list>
#include "Node.hpp"
namespace Thomas 
{
	void AStarPathfinding(Node start, Node end)
	{
		std::list<Node> openSet;
		openSet.push_back(start);
		std::list<Node> closeSet; //visited Nodes
		while (!openSet.empty)
		{
			openSet.sort(lowestFcost);
			Node currentNode = openSet.front();
			openSet.pop_front();
			closeSet.push_back(currentNode);

			if (currentNode == end)
			{
				//Construct Path
			}




		}



	}
}
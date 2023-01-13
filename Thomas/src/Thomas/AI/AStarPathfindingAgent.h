


#include "thpch.h"
#include "Thomas/Scene/Entity.h"
#include "Thomas/AI/Node.h"
#ifndef ASTARPATHFINDINGAGENT_H
#define ASTARPATHFINDINGAGENT_H


namespace Thomas
{


	class AStarPathfindingAgent
	{
	public:
		//Transform* seeker;

		bool found;
		//Entity& target;
		//int counter; 

		std::vector<Node*> path;

		//This are the nodes that we have yet to visit
		std::vector<Node*> openSet;

		//This are the nodes that have been visited
		std::vector<Node*> closedSet;


		//void SetDestination

		//This is the pointer to the node grid
		//Grid* grid;

	};

}

#endif



//#include <algorithm>

#pragma once

//#ifndef ASTARPATHFINDING_H
//#define ASTARPATHFINDING_H
#include "thpch.h"
#include "Thomas/AI/Node.h"
#include "Thomas/AI/Grid.h"
#include "Thomas/Math/Vector2D.h"
#include "Thomas/Scene/Scene.h"
#include "Thomas/Scene/Entity.h"

//#include "Thomas/AI/AStarPathfindingObstacle.h"
//#include "Thomas/AI/GridSystem.h"
namespace Thomas 
{
	//class Node;
	//class Grid;
	//class Vec2;

	class AStarPathfinding
	{
	public:

		//Transform * seeker;
		//Transform * target;

		//This is the shortest path to the target position
		//std::vector<Node*> path;

		////This are the nodes that we have yet to visit
		//std::vector<Node*> openSet;

		////This are the nodes that have been visited
		//std::vector<Node*> closedSet;
		//bool start
		bool found = false;
		////This is the pointer to the node grid
		Grid* grid;

		
		//
		//This is the constructor
		//AStarPathfinding() : grid{ nullptr } {};

		//This is the destructor that will clear the vectors for the path, closed set and open set
		//~AStarPathfinding();

		//void Start(Scene* m_Context);


		void Update(Scene* m_Context, Timestep timestep);


		//This is the A Star Pathfinding algorithm
		void AStarPathSearch(Vec2 startPos, Vec2 endPos, AStarPathfindingAgent& agent);

		//Get the distance between the nodes and assign the costs
		int GetDistance(Node* nodeA, Node* nodeB);

		//We will create the path from the start node to the end node
		void RetracePath(Node* startNode, Node* endNode, AStarPathfindingAgent& agent);

		//We will reset the path search by clearing the vectors for the path, closed set and open set
		void ResetPathSearch(AStarPathfindingAgent& agent);

		void SetAgentDestination(Vec2 start, Vec2 des, AStarPathfindingAgent& agent);

		//void SetAgentDestination(Grid & grid, Vec2 start, Transform& des, AStarPathfindingAgent& agent);

		//void ObstacleToGrid(AStarPathfindingObstacle& obstacle);
		

	};

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

	  extern AStarPathfinding aStarSystem;

}
//#endif

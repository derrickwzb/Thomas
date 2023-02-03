/******************************************************************************/
/*!
\file   AStarPathfinding.h
\author Keith Lua
\par    email: weijiekeith.lua\@digipen.edu
\par    DigiPen login: weijiekeith.lua
\par    Course: CSD-2125 HLP3
\date   3/2/2023
\brief
	This file is the interface of the AStarPathfinding System, it contains the
	class definition and prototype function declaration.

*/
/******************************************************************************/


#pragma once


#include "thpch.h"
#include "Thomas/AI/Node.h"
#include "Thomas/AI/Grid.h"
#include "Thomas/Math/Vector2D.h"
#include "Thomas/Scene/Scene.h"
#include "Thomas/Scene/Entity.h"


namespace Thomas 
{

	class AStarPathfinding
	{
	public:

		////This is the pointer to the node grid
		Grid* grid;


		//This function updates the AStarPathfinding Agents and the Grid in the scene
		void Update(Scene* m_Context, Timestep timestep);


		//This is the A Star Pathfinding algorithm
		void AStarPathSearch(Vec2 startPos, Vec2 endPos, AStarPathfindingAgent& agent);

		//Get the distance between the nodes and assign the costs
		int GetDistance(Node* nodeA, Node* nodeB);

		//We will create the path from the start node to the end node
		void RetracePath(Node* startNode, Node* endNode, AStarPathfindingAgent& agent);

		//We will reset the path search by clearing the vectors for the path, closed set and open set
		void ResetPathSearch(AStarPathfindingAgent& agent);

		//This will create the shortest path of Node from the start to end and store it in the agent
		void SetAgentDestination(Vec2 start, Vec2 des, AStarPathfindingAgent& agent);
		

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

	//So that it can be accessed globally.
	extern AStarPathfinding aStarSystem;

}


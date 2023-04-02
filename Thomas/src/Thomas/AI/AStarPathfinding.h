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

		bool once = false;

		//This function updates the AStarPathfinding Agents and the Grid in the scene
		/*!*************************************************************************
		****
		\brief
			This updates the AStarPathfinding agents and the Grid in the scene.
			It moves the agents towards the player.

		\param m_Context
			The scene where the AStarPathfinding is being used

		\param timestep
			This is to used timestep to update the entities

		****************************************************************************
		***/
		void Update(Scene* m_Context, Timestep timestep);


		//This is the A Star Pathfinding algorithm
		/*!*************************************************************************
		****
		\brief
			This finds the shortest path from the start position to the end position
			creates the path and copies the path into the agents.

		\param startPos
			The position of the agent

		\param endPos
			The position of where the player is at

		\param agent
			The the enemy component that store that enemy data for movement

		****************************************************************************
		***/
		void AStarPathSearch(Vec2 startPos, Vec2 endPos, AStarPathfindingAgent* agent);

		void ResetPathSearchAllAgentsInScene(Scene* scene);


		//Get the distance between the nodes and assign the costs
		/*!*************************************************************************
		****
		\brief
			This returns the distance between the two node

		\param nodeA
			The lhs node

		\param nodeB
			This rhs node

		****************************************************************************
		***/
		int GetDistance(Node* nodeA, Node* nodeB);

		//We will create the path from the start node to the end node

		/*!*************************************************************************
		****
		\brief
			This creates the path from the start node to the end node and copies the
			path into the agent

		\param startNode
			The node we use as the start of the path

		\param endNode
			The node we use as the end of the path

		\param agent
		The component that stores the data for the movement of the entity

		****************************************************************************
		***/
		void RetracePath(Node* startNode, Node* endNode, AStarPathfindingAgent* agent);

		/*!*************************************************************************
		****
		\brief
			This reset the path search by clearing the vectors for the path, closed
			set and open set

		\param agent
			The component that stores the data for the movement of the entity

		****************************************************************************
		***/
		void ResetPathSearch(AStarPathfindingAgent* agent);

		//This will create the shortest path of Node from the start to end and store it in the agent

		/*!*************************************************************************
		****
		\brief
			This finds the shortest path from the start position to the end position
			creates the path and copies the path into the agents.

		\param startPos
			The position of the agent

		\param endPos
			The position of where the player is at

		\param agent
			The the enemy component that store that enemy data for movement

		****************************************************************************
		***/
		void SetAgentDestination(Vec2 start, Vec2 des, AStarPathfindingAgent* agent);
		
		//~AStarPathfinding();
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


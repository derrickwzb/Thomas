/******************************************************************************/
/*!
\file   AStarPathfindingAgent.h
\author Keith Lua
\par    email: weijiekeith.lua\@digipen.edu
\par    DigiPen login: weijiekeith.lua
\par    Course: CSD-2125 HLP3
\date   3/2/2023
\brief
	This file is the implementation of a AStarPathfindingAgent Component

*/
/******************************************************************************/


#pragma once

#include "thpch.h"
#include "Thomas/Scene/Entity.h"
#include "Thomas/AI/Node.h"
#include "Thomas/Scene/Components.h"
//#include "Thomas/AI/AStarPathfinding.h"


namespace Thomas
{

	class AStarPathfindingAgent
	{
	public:

		//This counter will increase when agent reaches a Node in  the path vector
		int indexSpawnedFrom;
		int counter = 0; 

		bool enabled = true;
		//Location of original/previous location of the target.
		Vec2 previousTargetLocation;
		float angleOfRotation = 0.f;
		Vec2 currentDirection = { 0,1 };
		Vec2 actualDirection;
		//Flag to mark when a target is found.
		bool found = false;

		//A boolean switch to store the previous location of the player for comparison.
		bool prevExists;

		//Toggles the path finding 
		bool pathfindingEnabled;

		//The pointer to the target's transform
		Transform* target;

		//The velocity of the agent
		Vec2 velocity; 

		//This are the nodes that form the shortest path
		std::vector<Node*> path;

		//This are the nodes that we have yet to visit
		std::vector<Node*> openSet;

		//This are the nodes that have been visited
		std::vector<Node*> closedSet;


		
	};

}


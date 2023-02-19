/******************************************************************************/
/*!
\file   AStarPathfinding.cpp
\author Keith Lua
\par    email: weijiekeith.lua\@digipen.edu
\par    DigiPen login: weijiekeith.lua
\par    Course: CSD-2125 HLP3
\date   3/2/2023
\brief
	This file is the implementation of the AStarPathfinding System

*/
/******************************************************************************/

#pragma once

#include "thpch.h"
#include "Thomas/AI/AStarPathfinding.h"
#include "Thomas/AI/Node.h"
#include "Thomas/AI/Grid.h"
#include "Thomas/Math/Vector2D.h"
#include "Thomas/Scene/Entity.h"
#include "Thomas/Scene/Scene.h"
#include "Thomas/Renderer/Graphics.h"
#include "Thomas/AI/GridSystem.h"
namespace Thomas 
{
	AStarPathfinding aStarSystem;

	bool lowestFcost(const Node* first, const Node* second)
	{
		return (*first).Fcost < (*second).Fcost;
	}

	

	//This function updates the AStarPathfinding Agents and the Grid in the scene
	void AStarPathfinding::Update(Scene* m_Context, Timestep timestep)
	{
		std::map<EntityID, Signature>& entities = m_Context->m_Registry->GetEntities();

		if (aStarSystem.grid != nullptr)
		{
			
			if (gridSystem.obstacles.empty() && once == false)
			{
				std::cout << "TEST----------------------------------------------\n";
				for (auto const& e0 : entities)
				{
					Entity entity0{ e0.first , m_Context };

					if (entity0.HasComponent<AStarPathfindingObstacle>())
					{
						auto& obstacleData = entity0.GetComponent<AStarPathfindingObstacle>();
						

						gridSystem.AddObstacleToGrid(*aStarSystem.grid, obstacleData);


					}

				}
				once = true;
			}
			else
			{
				for (auto const& e0 : entities)
				{
					Entity entity{ e0.first , m_Context };
					if (entity.HasComponent<AStarPathfindingObstacle>())
					{
						AStarPathfindingObstacle& obstacleData = entity.GetComponent<AStarPathfindingObstacle>();
						obstacleData.position = entity.GetComponent<Box_collider>().box_trans.translation;
					}

				}

				//std::cout << "gridSystem.obstacles Size: "  << gridSystem.obstacles.size() << "\n";
				for (AStarPathfindingObstacle * obs : gridSystem.obstacles)
				{
					//std::cout << "Previous Position: (" << obs->prevPosition.x << "," << obs->prevPosition.y << ") \n";
					if (obs->prevPosition.x != obs->position.x || obs->prevPosition.y != obs->position.y)
					{
						
						std::cout << "Current Position: (" << obs->position.x << "," << obs->position.y << ") \n";
						obs->hasChanged = true;

						std::cout << "Has Changed? " << obs->hasChanged << "\n";
						gridSystem.RemoveObstacleFromGrid(*aStarSystem.grid, *obs);
						gridSystem.AddObstacleToGrid(*aStarSystem.grid, *obs);
					}
				}
			}
		}
		if (aStarSystem.grid != nullptr)
		{
			
			for (auto const& e2 : entities)
			{
				Entity entity2{ e2.first , m_Context };

				if (entity2.HasComponent<AStarPathfindingAgent>())
				{
					auto& agentData = entity2.GetComponent<AStarPathfindingAgent>();
					auto& agentTransformData = entity2.GetComponent<Transform>(); 
					auto& agentColliderTransformData = entity2.GetComponent<Box_collider>();
					for (auto const& e3 : entities)
					{
						Entity entity3{ e3.first , m_Context };


						if (entity3.HasComponent<ObjectType>())
						{
							auto& objectTypeData = entity3.GetComponent<ObjectType>();
							if (objectTypeData.type == ObjectTypeID::player)
							{
								
								auto& playerTransformData = entity3.GetComponent<Transform>();
								agentData.target = &playerTransformData;
								break;
							}
							else
							{
								//agentData.target = nullptr;
							}
						}
						
					}
					if (agentData.pathfindingEnabled == true)
					{
						if (agentData.target)
						{
							Transform targetTransformData = *agentData.target;

							if (agentData.path.empty() || agentData.counter == agentData.path.size() - 1)
							{
								AStarPathSearch(Vec2(agentTransformData.translation), Vec2(targetTransformData.translation), agentData);
							}
							if (!agentData.path.empty())
							{

								Vec2 direction = agentData.path[agentData.counter]->position - agentTransformData.translation;
								Vector2DNormalize(direction, direction);
								int distanceToWaypoint = (int)Vector2DDistance(agentTransformData.translation, agentData.path[agentData.counter]->position);
								agentTransformData.translation.x += direction.x * (timestep);
								agentTransformData.translation.y += direction.y * (timestep);


								agentColliderTransformData.box_trans.rotation = agentTransformData.rotation;

								agentColliderTransformData.box_trans.translation = agentTransformData.translation;
								if (distanceToWaypoint <= 0 && agentData.counter < agentData.path.size() - 1)
								{
									++agentData.counter;
								}


							}
						}
					}
				}
			}
		}

	}



	//This is the A Star Pathfinding algorithm that will find the shortest path to the end position
	void  AStarPathfinding::AStarPathSearch(Vec2 startPos, Vec2 endPos, AStarPathfindingAgent & agent)
	{
		
		ResetPathSearch(agent);
		agent.counter = 0;
		Node* start = gridSystem.WorldPositionToNode(*grid, startPos);
		Node* end = gridSystem.WorldPositionToNode(*grid, endPos);

		if (start == nullptr)
		{
			return;
		}

		if (end == nullptr)
		{
			return;
		}

		


		agent.openSet.push_back(start);

		//While the open set is not empty or there no nodes that has not been visited
		while (agent.openSet.size() > 0)
		{
			//The current node is the first node in the open set
			Node* current = agent.openSet.front();

			//We will search the open set for a node that has the lowest Fcost or equal Fcost to current node
			//as well as has the lower Hcost compared to the current node
			for (int i = 0; i < agent.openSet.size(); ++i)
			{
				if (agent.openSet[i]->Fcost < current->Fcost || agent.openSet[i]->Fcost == current->Fcost && agent.openSet[i]->Hcost < current->Hcost)
				{
					current = agent.openSet[i];
				}
			}

			//Check if the current node exist in the open set
			auto currentIterator = std::find_if(agent.openSet.begin(), agent.openSet.end(), Contains(current));

			//Remove it from the open set
			agent.openSet.erase(currentIterator);

			//Then add it to the closed set containing the visited nodes
			agent.closedSet.push_back(current);

			//If the current node is the same as the end node
			if (current == end)
			{
				//We will create a path from the start to end
				RetracePath(start, end, agent);
				return;
			}

			//We will check the neighbours of the current Node
			for (Node* neighbour : current->neighbours)
			{
				//If the closed set contains the neighbour or if it is blocked, we will ignore them
				auto closedSetContains = std::find_if(agent.closedSet.begin(), agent.closedSet.end(), Contains(neighbour));
				if (neighbour->blocked == true || closedSetContains != agent.closedSet.end())
				{
					continue;
				}

				//We will calculate the cost of traveling from the starting node to the current node to that neighbour node 
				int newMovementCostToNeighbour = current->Gcost + GetDistance(current, neighbour);

				//If the open set does not contain the neighbour or 
				//If the cost to travel from the starting node to the current node to that neighbour node 
				//is lower than the cost 
				auto openSetDoesNotContains = std::find_if(agent.openSet.begin(), agent.openSet.end(), Contains(neighbour));
				if (newMovementCostToNeighbour < neighbour->Gcost || openSetDoesNotContains == agent.openSet.end())
				{
					neighbour->Gcost = newMovementCostToNeighbour;
					neighbour->Hcost = GetDistance(neighbour, end);
					neighbour->parent = current;
					if (openSetDoesNotContains == agent.openSet.end())
					{
						agent.openSet.push_back(neighbour);

					}
				}
			}

		}
	}

	//We will create the path from the start node to the end node
	void AStarPathfinding::RetracePath(Node* startNode, Node* endNode, AStarPathfindingAgent & agent)
	{
		std::vector<Node*> tempPath{};
		Node* currentNode = endNode;
		while (currentNode != startNode)
		{
			currentNode->state = Node::State::PATH;
			tempPath.push_back(currentNode);
			currentNode = currentNode->parent;

		}
		std::reverse(tempPath.begin(), tempPath.end());
		agent.path = tempPath;
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
	void AStarPathfinding::ResetPathSearch(AStarPathfindingAgent & agent)
	{

		agent.path.clear();
		agent.openSet.clear();
		agent.closedSet.clear();
		agent.counter = 0;
	}

	//This will create the shortest path of Node from the start to end and store it in the agent
	void AStarPathfinding::SetAgentDestination(Vec2 start, Vec2 des, AStarPathfindingAgent& agent)
	{
		AStarPathSearch(start, des, agent);
	}

}

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

	bool once = false;

	void AStarPathfinding::Update(Scene* m_Context, Timestep timestep)
	{
		std::map<EntityID, Signature>& entities = m_Context->m_Registry->GetEntities();

		if (aStarSystem.grid != nullptr)
		{

			if (gridSystem.obstacles.empty() && once == false)
			{
				for (auto const& e0 : entities)
				{
					Entity entity0{ e0.first , m_Context };

					if (entity0.HasComponent<AStarPathfindingObstacle>())
					{
						auto& obstacleData = entity0.GetComponent<AStarPathfindingObstacle>();
						gridSystem.obstacles.push_back(&obstacleData);

						gridSystem.AddObstacleToGrid(*aStarSystem.grid, obstacleData);


					}

				}
				once = true;
			}
			else
			{
				/*for (auto const& e0 : entities)
				{
					Entity entity0{ e0.first , m_Context };

					if (entity0.HasComponent<AStarPathfindingObstacle>())
					{
						auto& obstacleData = entity0.GetComponent<AStarPathfindingObstacle>();
						gridSystem.obstacles.push_back(obstacleData);

						gridSystem.AddObstacleToGrid(*aStarSystem.grid, obstacleData);


					}

				}*/
			}



			

			
			
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
								agentData.target = nullptr;
								//continue;
							}
						}
						
					}
					if (agentData.pathfindingEnabled == true)
					{
						if (agentData.target != nullptr)
						{
							//std::cout << "---------------------------------------------------------------------------------------------------------";
							Transform targetTransformData = *agentData.target;
							Vec2 prev;

							if (agentData.found == false)
							{
								//agentData.counter = 0;

								if (agentData.prevExists == false)
								{
									prev = targetTransformData.translation;
									agentData.prevExists = true;
								}

								AStarPathSearch(Vec2(agentTransformData.translation), Vec2(targetTransformData.translation), agentData);
								agentData.found = true;
								if (agentData.counter == agentData.path.size() || agentData.path.empty())
								{
									agentData.counter = 0;
									agentData.found = false;
								}
								for (int i = 0; i < agentData.path.size(); ++i)
								{
									//std::cout << "Path(" << agentData.path[i]->gridX << "," << agentData.path[i]->gridY << ")\n";
								}
								//std::cout << "Prev(" << prev.x << "," << prev.y << ")\n";
								//std::cout << "current( " << targetTransformData.translation.x << "," << targetTransformData.translation.y << ")\n";


							}

							//	//std::cout << "Prev(" << prev.x << "," << prev.y << ")\n";
							//	//std::cout << "current( " << targetTransformData.translation.x << "," << targetTransformData.translation.y << ")\n";
							//	if (agentData.path.size() > 0)
							//	{
							//		found = true;
							//	}
							//	else
							//	{
							//		found = false;
							//	}
							//}

							float distanceToPlayer = Vector2DDistance(agentTransformData.translation, targetTransformData.translation);
							//Vec2 lastPosition;
							bool atLastPosition = false;
							if (!agentData.path.empty())
							{

								Vec2 velocity;

								int distanceToWaypoint = 0;
								if (agentData.counter < agentData.path.size())
								{
									Vec2 direction = agentData.path[agentData.counter]->position - agentTransformData.translation;
									//std::cout << "Path(" << agentData.path[agentData.counter]->gridX << "," << agentData.path[agentData.counter]->gridY << ")\n";
									Vector2DNormalize(direction, direction);

									Vec2 velocity = direction;

									distanceToWaypoint = (int)Vector2DDistance(agentTransformData.translation, agentData.path[agentData.counter]->position);

									agentTransformData.translation.x += velocity.x * (timestep);
									agentTransformData.translation.y += velocity.y * (timestep);
									agentColliderTransformData.box_trans.translation = agentTransformData.translation;
								}



								//std::cout << "Distance To Way Point: " <<  distanceToWaypoint << "\n";
								if (distanceToWaypoint <= std::numeric_limits<float>::epsilon() && agentData.counter < agentData.path.size())
								{

									//velocity.x = 0;
									//velocity.y = 0;
									//std::cout << distanceToWaypoint;
									//std::cout << "Size: "<< agentData.path.size() << "\n";
									++agentData.counter;

									if (targetTransformData.translation.x != prev.x && targetTransformData.translation.y != prev.y)
									{
										agentData.found = false;
										agentData.prevExists = false;
									}
									//std::cout << "Counter: " << agentData.counter << "\n";
								}
								else
								{
									if (agentData.counter == agentData.path.size())
									{
										agentData.found = false;

									}
								}


							}
							else
							{
							
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
		//std::cout << "Start Pos: (" << startPos.x << "," << startPos.y << ")\n";
		Node* start = gridSystem.WorldPositionToNode(*grid, startPos);
		//std::cout << "Start Pos: (" << startPos.x << "," << startPos.y << ")\n";
		//std::cout << "Start Node: (" << start->position.x << "," << start->position.y << ")\n";
		Node* end = gridSystem.WorldPositionToNode(*grid, endPos);

		if (start == nullptr)
		{
			return;
		}

		if (end == nullptr)
		{
			return;
		}

		

		//std::cout << "End Pos: (" << endPos.x << "," << endPos.y << ")\n";
		//std::cout << "End Node: (" << end->position.x << "," << end->position.y << ")\n";
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
				//ResetPathSearch(agent);
				RetracePath(start, end, agent);
				//ResetPathSearch(agent);
				return;
				//return;
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
			tempPath.push_back(currentNode);
			currentNode = currentNode->parent;

		}
		std::reverse(tempPath.begin(), tempPath.end());
		agent.path = tempPath;
	}

	//Get the distance between the nodes and assign the costs
	int AStarPathfinding::GetDistance(Node* nodeA, Node* nodeB)
	{
		/*if (nodeA != nullptr || nodeB != nullptr)
		{

		}*/
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
		//agent.counter = 0;
	}

	void AStarPathfinding::SetAgentDestination(Vec2 start, Vec2 des, AStarPathfindingAgent& agent)
	{
		AStarPathSearch(start, des, agent);
	}

	/*void AStarPathfinding::SetAgentDestination(Grid & grid, Vec2 start, Transform& des, AStarPathfindingAgent& agent)
	{
		agent.target = &des;
		Vector2D d = agent.target->translation;
		AStarPathSearch(grid, start, d, agent);
	}*/
	//void AStarPathfinding::ObstacleToGrid(AStarPathfindingObstacle& obstacle)
	//{
	//	for (auto row : grid->nodeGrids)
	//	{
	//		for (Node* node : row)
	//		{
	//			if (node->gridY <= (int)grid->WorldPositionToNodeIndex(obstacle.position - obstacle.size/2 ).y && node->gridY >= (int)grid->WorldPositionToNodeIndex(obstacle.position - obstacle.size / 2).y
	//				
	//				&& node->gridX <= (int)grid->WorldPositionToNodeIndex(obstacle.position - obstacle.size / 2).x && node->gridX >= (int)grid->WorldPositionToNodeIndex(obstacle.position - obstacle.size / 2).x)
	//			{
	//				node->blocked = true;
	//				std::cout << "Blocked Position: (" << node->position.x << "," << node->position.y << ")\n";
	//			   //std::cout << 
	//				//break;
	//			}
	//			
	//		}
	//	}

	//	//grid 
	//	//grid->WorldPositionToNodeIndex(obstacle.position + obstacle.size / 2);

	//}
	//This is the destructor that will clear the vectors for the path, closed set and open set
	//AStarPathfinding::~AStarPathfinding()
	//{
		//closedSet.clear();

		//openSet.clear();

		//path.clear();

	//}


}

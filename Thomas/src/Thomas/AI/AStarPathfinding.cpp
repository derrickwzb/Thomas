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
	/*void AStarPathfinding::Update()
	{
		AStarPathfinding::AStarPathSearch(seeker, target);
	}*/

	//void AStarPathfinding::Start(Scene * m_Context)
	//{
	//	std::map<EntityID, Signature>& entities = m_Context->m_Registry->GetEntities();
	//	for (auto const& e : entities)
	//	{
	//		Entity entity{ e.first , m_Context };
	//		//Grid grid;
	//		if (entity.HasComponent<Grid>())
	//		{
	//			//std::cout << "Grid----------------------------------";
	//			auto& mapTransform = entity.GetComponent<Transform>();
	//			auto& gridComponent = entity.GetComponent<Grid>();

	//			//grid = { Vec2(mapTransform.global_max.x - mapTransform.global_min.x, mapTransform.global_max.y - mapTransform.global_min.y), grid.nodeRadius };
	//			/*gridComponent = { Vec2(mapTransform.scaling.x ,  mapTransform.scaling.y), 0.125f };
	//			gridComponent.origin = { mapTransform.translation.x - (mapTransform.scaling.x / 2), mapTransform.translation.y - (mapTransform.scaling.y / 2) };*/
	//			//std::cout << " gridSize: " << gridComponent.nodeGrids.size() << "\n";


	//			//if (gridComponent.nodeGrids.size() == 0)
	//			//{

	//			//	gridComponent.CreateGrid();
	//			//	for (auto const& e3 : entities)
	//			///	{
	//			//		Entity entity3{ e3.first , m_Context };
	//			//		if (entity3.HasComponent<AStarPathfindingObstacle>())
	//		/*			{
	//						auto& obstacle = entity3.GetComponent<AStarPathfindingObstacle>();
	//						gridComponent.AddObstacles(obstacle);
	//					}

	//				}*/

	//				int counter = 0;
	//				for (auto row : gridComponent.nodeGrids)
	//				{
	//					for (auto elem : row)
	//					{
	//						//std::cout << counter++ << " ";
	//						gridComponent.AddNeighbours(elem);

	//					}

	//				}

	//				grid = &gridComponent;
	//			}
	//			for (auto const& e2 : entities)
	//			{
	//				Entity entity2{ e2.first , m_Context };
	//				auto& seeker = entity2.GetComponent<Transform>();
	//				if (entity2.HasComponent<AStarPathfindingAgent>())
	//				{
	//					//auto & astar = entity.GetComponent<AStarPathfindingAgent>();


	//					if (entity2.GetComponent<AStarPathfindingAgent>().target)
	//					{
	//					     
	//						auto& targetToFind = entity2.GetComponent<AStarPathfindingAgent>().target;
	//						std::cout << "Target Position (" << targetToFind->translation.x << "," << targetToFind->translation.y << ")\n";
	//						auto& seekerAgent = entity2.GetComponent<AStarPathfindingAgent>();
	//						std::cout << "Seeker Position (" << seeker.translation.x << "," << seeker.translation.y << ")\n";
	//						aStarSystem.AStarPathSearch(seeker.translation, targetToFind->translation, seekerAgent);
	//						for (Node* node : entity2.GetComponent<AStarPathfindingAgent>().path)
	//						{
	//							std::cout << "Path (" << node->position.x << "," << node->position.y << ") ";
	//						}
	//					}
	//					
	//				}
	//			}
	//		}
	//	}
	//  
	//	
	//}

	////void AStarPathfinding::SetAgentDestination(Vec2 des, AS)
	void AStarPathfinding::Update(Scene* m_Context, Timestep timestep)
	{
		std::map<EntityID, Signature>& entities = m_Context->m_Registry->GetEntities();

		//for (auto const& e : entities) {
			//Entity entity{ e.first , m_Context };

		//std::cout << "In Function: " << &grid << std::endl;
		//std::cout << aStarSystem.grid << std::endl;
		if (aStarSystem.grid != nullptr)
		{


			for (auto const& e0 : entities)
			{
				Entity entity0{ e0.first , m_Context };
				if (entity0.HasComponent<AStarPathfindingObstacle>())
				{
					auto& obstacleData = entity0.GetComponent<AStarPathfindingObstacle>();
					gridSystem.AddObstacleToGrid(*aStarSystem.grid, obstacleData);
					

				}
				//break;

			}
			
			for (auto const& e2 : entities)
			{
				Entity entity2{ e2.first , m_Context };

				if (entity2.HasComponent<AStarPathfindingAgent>())
				{
					auto& agentData = entity2.GetComponent<AStarPathfindingAgent>();
					auto& agentTransformData = entity2.GetComponent<Transform>(); 
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
							}
							
							/*else
							{
									
								continue;
							}*/
						}
					}
					if(agentData.target != nullptr)
					{
						Transform targetTransformData = *agentData.target;

						AStarPathSearch(agentTransformData.translation, targetTransformData.translation, agentData);
							//std
						if (!agentData.path.empty())
						{
							Vec2 direction = agentData.path[0]->position - agentTransformData.translation;
							Vector2DNormalize(direction, direction);
							int distanceFromWaypoint = int(  10 * Vector2DDistance(agentTransformData.translation, agentData.path[0]->position));
							std::cout << "Distance: " << distanceFromWaypoint << "\n";
							std::cout << "Current Position: " << "(" << agentTransformData.translation.x << "," << agentTransformData.translation.y << ")\n";
							std::cout << "Waypoint Position: " << "(" << agentData.path[0]->position.x << "," << agentData.path[0]->position.y << ")\n";
								//std::cout << counterPath << " ";
							std::cout << "Path Size: " << agentData.path.size() << "\n";

							if (distanceFromWaypoint > 0)
							{
								Vec2 velocity = direction * 10.0f;
								agentTransformData.translation.x += velocity.x * static_cast<float>(timestep);
								agentTransformData.translation.y += velocity.y * static_cast<float>(timestep);

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
		//agent.counter = 0;
		std::cout << "Start Pos: (" << startPos.x << "," << startPos.y << ")\n";
		Node* start = gridSystem.WorldPositionToNode(*grid, startPos);
		//std::cout << "Start Pos: (" << startPos.x << "," << startPos.y << ")\n";
		std::cout << "Start Node: (" << start->position.x << "," << start->position.y << ")\n";
		Node* end = gridSystem.WorldPositionToNode(*grid, endPos);
		//std::cout << "End Pos: (" << endPos.x << "," << endPos.y << ")\n";
		std::cout << "End Node: (" << end->position.x << "," << end->position.y << ")\n";
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

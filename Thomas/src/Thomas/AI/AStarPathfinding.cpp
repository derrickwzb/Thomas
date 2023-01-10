
#include "thpch.h"
#include "Thomas/AI/AStarPathfinding.h"
#include "Thomas/AI/Node.h"
#include "Thomas/AI/Grid.h"
#include "Thomas/Math/Vector2D.h"
#include "Thomas/Scene/Entity.h"
#include "Thomas/Scene/Scene.h"
#include "Thomas/Renderer/Graphics.h"
namespace Thomas 
{


	bool lowestFcost(const Node* first, const Node* second)
	{
		return (*first).Fcost < (*second).Fcost;
	}
	/*void AStarPathfinding::Update()
	{
		AStarPathfinding::AStarPathSearch(seeker, target);
	}*/

	void AStarPathfinding::Start()
	{

	}

	//void AStarPathfinding::SetAgentDestination(Vec2 des, AS)
	void AStarPathfinding::Update(Scene* m_Context, Timestep timestep)
	{
		//auto start = std::chrono::steady_clock::now();
		std::map<EntityID, Signature>& entities = m_Context->m_Registry->GetEntities();

		for (auto const& e : entities)
		{
			Entity entity{ e.first , m_Context };
			//Grid grid;
			if (entity.HasComponent<Grid>())
			{
				//std::cout << "Grid----------------------------------";
				auto& mapTransform = entity.GetComponent<Transform>();
				auto& gridComponent = entity.GetComponent<Grid>();

				//grid = { Vec2(mapTransform.global_max.x - mapTransform.global_min.x, mapTransform.global_max.y - mapTransform.global_min.y), grid.nodeRadius };
				gridComponent = { Vec2(mapTransform.scaling.x ,  mapTransform.scaling.y ), 0.125f };
				gridComponent.origin = {mapTransform.translation.x - (mapTransform.scaling.x/2), mapTransform.translation.y - (mapTransform.scaling.y / 2) };
				//std::cout << " gridSize: " << gridComponent.nodeGrids.size() << "\n";
				if (gridComponent.nodeGrids.size() == 0)
				{
					gridComponent.CreateGrid();
					int counter = 0;
					for (auto row : gridComponent.nodeGrids)
					{
						for (auto elem : row)
						{
							//std::cout << counter++ << " ";
							gridComponent.AddNeighbours(elem);

						}

					}
					//std::cout << " gridSizeAfterCreateGrid: " << gridComponent.nodeGrids.size() << "\n";
					//std::cout << "Map Width: " << mapTransform.scaling.x << "\n";
				 //   std::cout << "Map Height: " << mapTransform.scaling.y << "\n";
					//std::cout << "Map Min: (" << gridComponent.origin.x << "," << gridComponent.origin.y << ")\n";

				}
				//std::cout << " gridSizeAfterCreateGrid: " << gridComponent.nodeGrids.size() << "\n";

				for (auto const& e2 : entities)
				{
					Entity entity2{ e2.first , m_Context };
					if (entity2.HasComponent<AStarPathfindingAgent>())
					{
						//auto & astar = entity.GetComponent<AStarPathfindingAgent>();
						grid = &gridComponent;
						auto & seeker = entity2.GetComponent<Transform>();
						if (entity2.GetComponent<AStarPathfindingAgent>().target)
						{
							//std::cout << "-----------------\n";
							auto & targetToFind = entity2.GetComponent<AStarPathfindingAgent>().target;
							auto& seekerAgent = entity2.GetComponent<AStarPathfindingAgent>();

							//std::cout << "Enemy Position: (" << seeker.translation.x  << "," << seeker.translation.y << ")\n";
							//std::cout << "Target Positon: (" << targetToFind->translation.x << "," << targetToFind->translation.y<< ")\n";
							//if (path.begin() == path.end())
							//{
							//	ResetPathSearch();
							//	//AStarPathSearch(Vec2(seeker.translation.x, seeker.translation.y), Vec2(targetToFind->translation.x, targetToFind->translation.y));
							//}
							//Vec2 current;

							AStarPathSearch( Vec2(seeker.translation.x,seeker.translation.y), Vec2(targetToFind->translation.x, targetToFind->translation.y), seekerAgent );
							std::cout << "Counter: " << seekerAgent.counter << "\n";
							if (seekerAgent.path.empty())
								continue;
							//for (std::vector<Node*>::iterator startPath = path.begin(); startPath != path.end(); ++startPath)
							//{
							    //int counter = 0;
								Vec2 currentPos = Vec2(seeker.translation.x, seeker.translation.y);
								assert(*(seekerAgent.path.begin() + seekerAgent.counter));
								Vec2 direction = (*(seekerAgent.path.begin() + seekerAgent.counter))->position - currentPos;
								Vector2DNormalize(direction, direction);
								int distance = (int)(Vector2DDistance((*(seekerAgent.path.begin() + seekerAgent.counter))->position, currentPos) * 100);

								/*std::cout << "Current Position (" << currentPos.x << "," << currentPos.y << ")\n";
								std::cout << "Path (" << (*startPath)->position.x << "," << (*startPath)->position.y << ")\n";
								std::cout << "Direction (" << direction.x << "," << direction.y << ")\n";*/
								if (distance > 0)
								{
									distance = Vector2DDistance((*(seekerAgent.path.begin() + seekerAgent.counter))->position, currentPos) * 100;
									std::cout << "Current Position (" << currentPos.x << "," << currentPos.y << ")\n";
									//std::cout << "Path (" << (*startPath)->position.x << "," << (*startPath)->position.y << ")\n";
									//std::cout << "Direction (" << direction.x << "," << direction.y << ")\n";
									//std::cout << "Distance: " << distance << "\n";
									currentPos.x += (direction.x * static_cast<float>(timestep));
									currentPos.y += (direction.y * static_cast<float>(timestep));
									

									seeker.translation.x = currentPos.x;
									seeker.translation.y = currentPos.y;
									if (seekerAgent.counter == seekerAgent.path.size() - 1)
									{
										ResetPathSearch(seekerAgent);
									}
									//counter++;
								}
								else //reach a node
								{
									if (seekerAgent.counter == seekerAgent.path.size() - 1)
									{
										ResetPathSearch(seekerAgent);
										seekerAgent.counter = -1;
									}
									/*if (seekerAgent.path.begin() + seekerAgent.counter != seekerAgent.path.end())
									{
										++seekerAgent.counter;
									}
									else
									{
										seekerAgent.counter = 0;
									}*/
									
									++seekerAgent.counter;// = (seekerAgent.counter + 1) % seekerAgent.path.size();

								}

							//}

							//if(Vector2DDistance)
							//std::cout << 

							///std::cout << "Path " << path.size() << "\n";
						}
					}
				}

				//for(en)
				
				//transform.global_max = 

			}

			/*if (entity.HasComponent<AStarPathfinding>())
			{
				auto astar = entity.GetComponent<AStarPathfinding>();
				astar.grid = &grid;
			}*/

		}
		//auto stop = std::chrono::steady_clock::now();
		//std::chrono::duration<double> duration = (stop - start);
		//Physic_timetaken = duration.count();
	}



	//This is the A Star Pathfinding algorithm that will find the shortest path to the end position
	void  AStarPathfinding::AStarPathSearch(Vec2 startPos, Vec2 endPos, AStarPathfindingAgent & agent)
	{
		ResetPathSearch(agent);
		Node* start = grid->WorldPositionToNode(startPos);
		//std::cout << "Start Pos: (" << startPos.x << "," << startPos.y << ")\n";
		//std::cout << "Start Node: (" << start->position.x << "," << start->position.y << ")\n";
		Node* end = grid->WorldPositionToNode(endPos);
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
		agent.counter = 0;
	}

	void AStarPathfinding::SetAgentDestination(Vec2 start, Vec2 des, AStarPathfindingAgent& agent)
	{
		AStarPathSearch(start, des, agent);
	}

	void AStarPathfinding::SetAgentDestination(Vec2 start, Transform& des, AStarPathfindingAgent& agent)
	{
		agent.target = &des;
		Vector2D d = agent.target->translation;
		AStarPathSearch(start, d, agent);
	}
	//This is the destructor that will clear the vectors for the path, closed set and open set
	AStarPathfinding::~AStarPathfinding()
	{
		//closedSet.clear();

		//openSet.clear();

		//path.clear();

	}


}

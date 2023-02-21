


#include "thpch.h"

#include "Thomas/AI/SpawnSystem.h"

namespace Thomas
{
	SpawnSystem spawnSystem;
	bool start = false;
	void SpawnSystem::SpawnEnemy(Scene * scene, Timestep timestep)
	{
		//if(spawner.startSpawn)
		//spawner.spawnLocation = { 0,0 };
		std::map<EntityID, Signature>& entities = scene->m_Registry->GetEntities();
		//std::cout << "Spawners: " << spawnSystem.spawnLocations.size() << "\n";
		/*for (auto const& e0 : entities)
		{
			Entity entity0{ e0.first , scene };

			if (entity0.HasComponent<Spawner>())
			{
				auto& obstacleData = entity0.GetComponent<Spawner>();


				
				spawnLocations.push_back(&obstacleData);
				std::cout << spawnLocations.size();
				

			}

		}*/

		for (auto const& e0 : entities)
		{
			Entity entity0{ e0.first , scene };
			if (entity0.HasComponent<Spawner>())
			{
				Spawner spawner = entity0.GetComponent<Spawner>();
				
				spawner.spawnLocation = Vec2(entity0.GetComponent<Transform>().translation);
				
				if (spawner.startSpawn == false)
				{
					//std::cout << "-----------------------------------------";
					//spawnLocations[i]->currentSpawnerTimeLeft = spawnLocations[i]->spawnTimeInterval;
					//spawnLocations[i]->startSpawn = false;
					//spawnLocations[i]->spawning = true;

					spawner.currentSpawnerTimeLeft = spawner.spawnTimeInterval;
					spawner.startSpawn = true;
					spawner.spawning = true;
				}
			}
		}
		
		for (int i = 0; i < spawnLocations.size(); ++i)
		{
			
			if(spawnLocations[i]->spawning == true)
			{
				if (spawnLocations[i]->currentSpawnerTimeLeft > 0)
				{
					spawnLocations[i]->currentSpawnerTimeLeft -= 1 * timestep;
					std::cout << "Spawner " << i << " TIme left : " << spawnLocations[i]->currentSpawnerTimeLeft << "\n";
				}
				else
				{

					
					if (spawnLocations[i]->enemyCount == spawnLocations[i]->maxEnemies)
					{
						spawnLocations[i]->spawning = false;
					}
					else
					{
						++spawnLocations[i]->enemyCount;
						//spawnLocations[i]->startSpawn = true;
						spawnLocations[i]->currentSpawnerTimeLeft = spawnLocations[i]->spawnTimeInterval;

						Entity enemy = scene->CreateEnemyEntity();
						//int randomNumber = rand() % spawnLocations.size();
						if (spawnLocations[i]->spawning == true)
						{
							enemy.GetComponent<Transform>().translation.x = spawnLocations[i]->spawnLocation.x;
							enemy.GetComponent<Transform>().translation.y = spawnLocations[i]->spawnLocation.y;

							enemy.GetComponent<Box_collider>().box_trans.translation.x = spawnLocations[i]->spawnLocation.x;
							enemy.GetComponent<Box_collider>().box_trans.translation.y = spawnLocations[i]->spawnLocation.y;
						}
						if (aStarSystem.grid)
						{
							enemy.AddComponent<AStarPathfindingAgent>();
							enemy.GetComponent<AStarPathfindingAgent>().pathfindingEnabled = true;
						}
						enemies.push_back(&enemy);
						
						//std::cout << "Size Of Enemies: " << enemies.size() << "\n";
					}
					
				}
			}

		}
		//for(int i = 0; i < )
		
	}





}
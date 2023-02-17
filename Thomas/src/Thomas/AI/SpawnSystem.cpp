


#include "thpch.h"

#include "Thomas/AI/SpawnSystem.h"

namespace Thomas
{
	SpawnSystem spawnSystem;
	void SpawnSystem::SpawnEnemy(Scene * scene, Timestep timestep)
	{
		//if(spawner.startSpawn)
		//spawner.spawnLocation = { 0,0 };
		std::map<EntityID, Signature>& entities = scene->m_Registry->GetEntities();

		for (auto const& e0 : entities)
		{
			Entity entity0{ e0.first , scene };

			if (entity0.HasComponent<Spawner>())
			{
				auto& obstacleData = entity0.GetComponent<Spawner>();


				spawnLocations.push_back(&obstacleData);


			}

		}

		
		for (Spawner* spawner : spawnLocations)
		{
			if (spawner->startSpawn == true)
			{
				if (spawner->currentSpawnerTimeLeft > 0)
				{
					spawner->currentSpawnerTimeLeft -= 0.1 * timestep;
					std::cout << "Spawner TIme left: " << spawner->currentSpawnerTimeLeft << "\n";
				}
				else
				{
					Entity enemy = scene->CreateEnemyEntity();
					int randomNumber = rand() % spawnLocations.size();
					enemy.GetComponent<Transform>().translation.x = spawnLocations[randomNumber]->spawnLocation.x;
					
					enemy.GetComponent<Transform>().translation.y = spawnLocations[randomNumber]->spawnLocation.y;

					enemy.GetComponent<Box_collider>().box_trans.translation.x = spawnLocations[randomNumber]->spawnLocation.x;
					enemy.GetComponent<Box_collider>().box_trans.translation.y = spawnLocations[randomNumber]->spawnLocation.y;
					if (aStarSystem.grid)
					{
						enemy.AddComponent<AStarPathfindingAgent>();
						enemy.GetComponent< AStarPathfindingAgent>().pathfindingEnabled = true;
					}
					enemies.push_back(&enemy);
					std::cout << "Size Of Enemies: " << enemies.size() << "\n";
					if (enemies.size() == spawner->maxEnemies)
					{
						spawner->startSpawn = false;
					}
					spawner->currentSpawnerTimeLeft = spawner->spawnTimeInterval;
				}
			}
		}
		
		
	}





}
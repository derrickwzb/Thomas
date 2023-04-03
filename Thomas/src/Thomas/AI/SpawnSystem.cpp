/******************************************************************************/
/*!
\file   SpawnSystem.cpp
\author Keith Lua
\par    email: weijiekeith.lua\@digipen.edu
\par    DigiPen login: weijiekeith.lua
\par    Course: CSD-2125 HLP3
\date   3/4/2023
\brief

	This file is the implementation of the Spawner System, it has functions
	that is responsible for the spawning of enemies.

*/
/******************************************************************************/


#include "thpch.h"

#include "Thomas/AI/SpawnSystem.h"

namespace Thomas
{
	SpawnSystem spawnSystem;
	bool start = false;
	void SpawnSystem::SpawnEnemy(Scene* scene, Timestep timestep)
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

	
		for (int i = 0; i < spawnLocations.size(); ++i)
		{
			for (int j = 0; j < spawnLocations[i]->enemies.size(); ++j)
			{
				if (spawnLocations[i]->enemies[j]->enabled == false)
				{
					spawnLocations[i]->enemies.erase(spawnLocations[i]->enemies.begin() + j);
					--spawnLocations[i]->enemyCount;
					//std::cout << "Enemy Count" << spawnLocations[i]->enemyCount << "\n";
				}
			}
		}
		

		for (auto const& e0 : entities)
		{
			Entity entity0{ e0.first , scene };
			if (entity0.HasComponent<Spawner>())
			{
				Spawner & spawner = entity0.GetComponent<Spawner>();
				
				spawner.spawnLocation = Vec2(entity0.GetComponent<Transform>().translation);
				
				if (spawner.startSpawn == false)
				{

					spawner.currentSpawnerTimeLeft = spawner.spawnTimeInterval;
					
					//std::cout << "State: " << spawner.startSpawn << "\n";
					//std::cout << "Size OF Spawners: " << spawnLocations.size();
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
					//std::cout << "Spawner " << i << " TIme left : " << spawnLocations[i]->currentSpawnerTimeLeft << "\n";
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
						enemy.GetComponent<AStarPathfindingAgent>().indexSpawnedFrom = i;
						enemy.GetComponent<Box_collider>().box_tog = 0;
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
						spawnLocations[i]->enemies.push_back(&enemy.GetComponent<AStarPathfindingAgent>());
						//std::cout << "--------------------------------------------------G---------------------------------------------------\n";
						
						//std::cout << "Size Of Enemies: " << enemies.size() << "\n";
					}
					
				}
			}
			else
			{
				if (spawnLocations[i]->enemyCount < spawnLocations[i]->maxEnemies)
				{
					spawnLocations[i]->spawning = true;
					spawnLocations[i]->currentSpawnerTimeLeft = spawnLocations[i]->spawnTimeInterval;
				}
			}
		}
		//for(int i = 0; i < )
		
	}




	void SpawnSystem::ClearEnemies()
	{
		for (int i = 0; i < spawnLocations.size(); ++i)
		{
			spawnLocations[i]->enemies.clear();

		}
	}


}

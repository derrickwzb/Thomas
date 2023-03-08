#pragma once
#include "ScriptUtils.h"


struct Enemy : Thomas::ScriptableEntity
{
	void OnCreate()
	{

	}

	void OnUpdate()
	{
		std::cout << "-------------------------ENEMY----------------------------------------------\n";

		if (g_IsPaused == false)
		{
			//std::cout << " State" << g_IsPaused << "\n";
			auto& combat_data = GetComponent<Thomas::CombatComponent>();
			//std::cout << "-------------------------ENEMY----------------------------------------------\n";
			if (combat_data.health > 0)
			{
				std::cout << "-------------------------ENEMY----------------------------------------------\n";
				GetComponent<Thomas::AStarPathfindingAgent>().pathfindingEnabled = true;
			}
			else
			{
				//--spawnSystem.spawnLocations[objs.GetComponent<AStarPathfindingAgent>().indexSpawnedFrom]->enemyCount;
				GetComponent<Thomas::AStarPathfindingAgent>().pathfindingEnabled = false;
			}
		}
		
		else {

			GetComponent<Thomas::AStarPathfindingAgent>().pathfindingEnabled = false;

		}

	}

	void OnDestroy()
	{

	}
};
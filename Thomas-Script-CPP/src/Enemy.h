#pragma once
#include "ScriptUtils.h"


struct Enemy : Thomas::ScriptableEntity
{
	void OnCreate()
	{

	}

	void OnUpdate()
	{
		auto& combat_data = GetComponent<Thomas::CombatComponent>();
		if (combat_data.health > 0)
		{
			GetComponent<Thomas::AStarPathfindingAgent>().pathfindingEnabled = true;
		}
		else
		{
			//--spawnSystem.spawnLocations[objs.GetComponent<AStarPathfindingAgent>().indexSpawnedFrom]->enemyCount;
			GetComponent<Thomas::AStarPathfindingAgent>().pathfindingEnabled = false;
		}

	}

	void OnDestroy()
	{

	}
};
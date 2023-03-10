#pragma once
#include "ScriptUtils.h"

std::string enemyType{};

struct Enemy : Thomas::ScriptableEntity
{



	void OnCreate()
	{
		enemyType = GetComponent<Thomas::Texture>().filename;
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		//std::cout << "-------------------------ENEMY IS PAUSED----------------------------------------------\n";

		//std::cout << "-------------------------ENEMY----------------------------------------------\n";

		if (g_IsPaused == false)
		{
			auto& combat_data = GetComponent<Thomas::CombatComponent>();
			




			if (combat_data.health > 0)
			{
				GetComponent<Thomas::AStarPathfindingAgent>().pathfindingEnabled = true;
			}
			else
			{

				
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
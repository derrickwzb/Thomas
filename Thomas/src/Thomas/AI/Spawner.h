

#pragma once
#include "thpch.h"
#include "Thomas/Math/Vector2D.h"

namespace Thomas 
{

	class Spawner
	{
	public:

		std::vector<AStarPathfindingAgent *> enemies;
		Vec2 spawnLocation;
		float spawnTimeInterval = 2.f;
		float currentSpawnerTimeLeft;
		bool startSpawn = false;
		bool spawning = false;
		int maxEnemies = 3;
		int enemyCount = 0;



	};

}
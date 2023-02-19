

#pragma once
#include "thpch.h"
#include "Thomas/Math/Vector2D.h"

namespace Thomas 
{

	class Spawner
	{
	public:


		Vec2 spawnLocation;
		float spawnTimeInterval = 2.f;
		float currentSpawnerTimeLeft;
		bool startSpawn = false;
		bool spawning = false;
		int maxEnemies = 5;
		int enemyCount = 0;



	};

}


#pragma once
#include "thpch.h"
#include "Thomas/Math/Vector2D.h"

namespace Thomas 
{

	class Spawner
	{
	public:

		Vec2 spawnLocation;
		float spawnTimeInterval = 20.0f;
		float currentSpawnerTimeLeft;
		bool startSpawn = false;
		int maxEnemies = 5;



	};

}
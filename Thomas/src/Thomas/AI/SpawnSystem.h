#pragma once
#include "Thomas/Scene/Scene.h"
#include "Thomas/Scene/Entity.h"
#include "Thomas/AI/Spawner.h"
#include "thpch.h"


namespace Thomas
{

	class SpawnSystem
	{
	public:
		
		
		std::vector<Spawner*> spawnLocations;
		int totalEnemies;
		void SpawnEnemy(Scene * scene, Timestep timestep);
		





	};
	extern SpawnSystem spawnSystem;
}
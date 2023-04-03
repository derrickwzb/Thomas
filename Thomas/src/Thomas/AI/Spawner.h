/******************************************************************************/
/*!
\file   Spawner.h
\author Keith Lua
\par    email: weijiekeith.lua\@digipen.edu
\par    DigiPen login: weijiekeith.lua
\par    Course: CSD-2125 HLP3
\date   3/4/2023
\brief
	This file is the implementation of a Spawner  component
	and it contains variables related to spawning .

*/
/******************************************************************************/

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
/******************************************************************************/
/*!
\file   SpawnSystem.h
\author Keith Lua
\par    email: weijiekeith.lua\@digipen.edu
\par    DigiPen login: weijiekeith.lua
\par    Course: CSD-2125 HLP3
\date   3/4/2023
\brief
	This file is the interface of the Spawn System, it contains the
	class definition and prototype function declaration.

*/
/******************************************************************************/

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
		void ClearEnemies();






	};
	extern SpawnSystem spawnSystem;
}
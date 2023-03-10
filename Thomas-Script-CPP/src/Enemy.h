/******************************************************************************/
/*!
\file		Enemy.h
\author 	Derrick Woo
\par    	email: d.woo@digipen.edu
\date   	10/3/2023
\brief		This file contains the functions and declarations of enemy script.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include "ScriptUtils.h"

//std::string enemyType{};

struct Enemy : Thomas::ScriptableEntity
{



	void OnCreate()
	{
		//enemyType = GetComponent<Thomas::Texture>().filename;
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		auto& combat_data = GetComponent<Thomas::CombatComponent>();
		(void)ts;

		if (g_IsPaused == false)
		{
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

		if (g_gameStateCurr == GameState::Level3) {
			if (combat_data.health <= 0) {
				g_gameStateNext = GameState::Win;
			}
		}
	}

	void OnDestroy()
	{

	}
};
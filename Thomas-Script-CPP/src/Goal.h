/******************************************************************************/
/*!
\file		PlayerUI.h
\author 	Chen XinPeng
\email:		c.xinpeng@digipen.edu
\date   	10/3/2023
\brief		This file contains the functions and declarations of goal script.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include "ScriptUtils.h"
#include "Managers/GameManager.h"


struct Goal : Thomas::ScriptableEntity
{
	void OnCreate()
	{
		TH_CORE_INFO("Goal Script Instantiated");
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		(void)ts;
		auto& obj_data = GetComponent<Thomas::ObjectType>();

		if (obj_data.win_collide == true) {
			if (g_gameStateCurr == GameState::Level1)
			{
				g_gameStateNext = GameState::Level2;
			}
			else if (g_gameStateCurr == GameState::Level2) {
				g_gameStateNext = GameState::Level3;
			}
			else if (g_gameStateCurr == GameState::Level3) {
				g_gameStateNext = GameState::Win;
			}
			
			g_GameTimer = 0.f;
			g_points = 0;
		}
	}

	void OnDestroy()
	{

	}
};
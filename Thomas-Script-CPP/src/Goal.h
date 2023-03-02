#pragma once
#include "ScriptUtils.h"
#include "AllScripts.h"


struct Goal : Thomas::ScriptableEntity
{
	void OnCreate()
	{
		TH_CORE_INFO("Goal Script Instantiated");
	}

	void OnUpdate()
	{
		auto& obj_data = GetComponent<Thomas::ObjectType>();

		if (g_points < 2) {
			obj_data.win_collide = false;
		}
		else if (g_points >= 2) {
			obj_data.win_collide = true;
		}

		if (obj_data.win_collide == true && g_points == 10) {
			g_gameStateNext = GameState::Level2;
			g_GameTimer = 0.f;

			g_points = 0;
		}
	}

	void OnDestroy()
	{

	}
};
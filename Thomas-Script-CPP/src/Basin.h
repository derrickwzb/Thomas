#pragma once
#include "ScriptUtils.h"
#include "Managers/GameManager.h"
#include "Puddle.h"

struct Basin : Thomas::ScriptableEntity
{

	void OnCreate()
	{
		TH_CORE_INFO("Basin Script Instantiated");
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		(void)ts;
		auto& type_data = GetComponent<Thomas::ObjectType>();
		if (type_data.basin_collide == true) {
			if (g_puddle_collide == true) {
				if (Thomas::Input::IsKeyPressed(TH_KEY_E)) {
					g_puddle_collide = false;
				}
			}
		}
	}

	void OnDestroy()
	{
	}

};
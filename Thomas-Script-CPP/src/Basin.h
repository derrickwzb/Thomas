#pragma once
#include "ScriptUtils.h"
#include "Managers/GameManager.h"
#include "Player.h"

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
		auto& parts = GetComponent<Thomas::Additional_Parts>();
		if (type_data.basin_collide == true) {
			std::cout << "Basin contacted" << std::endl;
			if (g_puddle_collide == true) {
				parts.parts_Transform[0].alpha_val = 1.f;
				if (Thomas::Input::IsKeyPressed(TH_KEY_E)) {
					g_puddle_collide = false;
				}
			}
			else
				parts.parts_Transform[0].alpha_val = 0.f;
		}
	}

	void OnDestroy()
	{
	}

};
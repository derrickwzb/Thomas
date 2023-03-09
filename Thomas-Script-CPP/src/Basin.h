#pragma once
#include "ScriptUtils.h"
#include "Managers/GameManager.h"

struct Basin : Thomas::ScriptableEntity
{

	void OnCreate()
	{
		TH_CORE_INFO("Basin Script Instantiated");
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		auto& type_data = GetComponent<Thomas::ObjectType>();
		if (type_data.basin_collide == true) {
			if (Thomas::Input::IsKeyPressed(TH_KEY_E)) {
				std::cout << "CLEAR" << std::endl;
			}
		}
	}

	void OnDestroy()
	{
	}

};
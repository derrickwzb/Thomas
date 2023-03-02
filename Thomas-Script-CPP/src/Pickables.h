#pragma once
#include "ScriptUtils.h"
#include "Player.h"


struct Pickables : Thomas::ScriptableEntity
{
	void OnCreate()
	{
		TH_CORE_INFO("Pickables Script Instantiated");
	}
	void OnUpdate()
	{
		auto& type = GetComponent<Thomas::ObjectType>();
		if (type.pickup_collide == true) {
			if (Thomas::Input::IsKeyPressed(TH_KEY_E)) {
				g_points += 1;
			}
		}
	}

	void OnDestroy()
	{

	}
};
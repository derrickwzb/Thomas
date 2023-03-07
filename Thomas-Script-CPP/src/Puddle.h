#pragma once
#include "ScriptUtils.h"
#include "Managers/GameManager.h"

static bool g_puddle_collide = false;

struct Puddle : Thomas::ScriptableEntity
{
	void OnCreate()
	{
		TH_CORE_INFO("Puddle Script Instantiated");
	}

	void OnUpdate()
	{
		auto& type_data = GetComponent<Thomas::ObjectType>();
		
		if (type_data.puddle_collide == true) {
			g_puddle_collide = true;
		}
		else {
			g_puddle_collide = false;
		}
	}

	void OnDestroy()
	{

	}
};
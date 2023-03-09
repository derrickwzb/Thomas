#pragma once
#include "ScriptUtils.h"
#include "Managers/GameManager.h"

static bool g_puddle_collide = false;
static int g_corruption_points{};

struct Puddle : Thomas::ScriptableEntity
{
	void OnCreate()
	{
		TH_CORE_INFO("Puddle Script Instantiated");
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		auto& type_data = GetComponent<Thomas::ObjectType>();
		auto& trans = GetComponent<Thomas::Transform>();
		auto& text = GetComponent<Thomas::Texture>();
		
		if (type_data.puddle_collide == true) {
			g_puddle_collide = true;
			trans.alpha_val = 1.f;
			text.animation_but = 1;
			g_corruption_points++;
			//type_data.destroy_pickup = true;
		}
		else {
			g_puddle_collide = false;
		}
	}

	void OnDestroy()
	{

	}
};
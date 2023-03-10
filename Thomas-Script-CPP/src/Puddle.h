#pragma once
#include "ScriptUtils.h"
#include "Managers/GameManager.h"

static bool g_puddle_collide = false;
static int g_corruption_points{};
static int timer = 0;

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
		
		if (g_gameStateNext == GameState::Level2) {
			g_puddle_collide = false;
		}
		if (type_data.puddle_collide == true) {
			g_puddle_collide = true;
			trans.alpha_val = 1.f;
			text.animation_but = 1;
			g_corruption_points++;
			timer++;
			if (timer > 10) {
				timer = 0;
				type_data.destroy_pickup = true;
			}
		}
	}

	void OnDestroy()
	{

	}
};
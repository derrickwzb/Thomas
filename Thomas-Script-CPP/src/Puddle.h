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

	void OnUpdate(Thomas::Timestep ts)
	{
		auto& type_data = GetComponent<Thomas::ObjectType>();
		auto& trans = GetComponent<Thomas::Transform>();
		auto& text = GetComponent<Thomas::Texture>();
		
		if (type_data.puddle_collide == true) {
			std::cout << text.filename << std::endl;
			g_puddle_collide = true;
			for (float i{}; i < 1.f; i += 0.01f) {
				trans.alpha_val = i;
				text.animation_but = 1;
			}
			for (float j{ 1.f }; j > 0.f; j -= 0.01f) {
				trans.alpha_val = j;
				text.animation_but = 1;
			}
			text.animation_but = 2;
		}
		else {
			g_puddle_collide = false;
		}
	}

	void OnDestroy()
	{

	}
};
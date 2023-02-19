#pragma once
#include "Thomas/Scene/Entity.h"
#include "Thomas/Scene/Components.h"
#include "Thomas/Renderer/Transform.h"
#include "Thomas.h"

struct Player : Thomas::ScriptableEntity
{
	void OnCreate()
	{
		TH_CORE_INFO("Player Script Instantiated");
	}

	void OnUpdate()
	{
		
		if (Thomas::Input::IsKeyPressed(TH_KEY_W)) {
			TH_CORE_INFO("keypressed");
		}

		auto& trans = GetComponent<Thomas::Transform>().translation;
	}

	void OnDestroy()
	{

	}
};

void Test();
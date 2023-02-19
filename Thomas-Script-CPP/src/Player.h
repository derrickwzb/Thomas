#pragma once
#include "Thomas/Scene/Entity.h"
#include "Thomas.h"

struct Player : Thomas::ScriptableEntity
{
	void OnCreate()
	{
		std::cout << "test";
	}

	void OnUpdate()
	{
		
		if (Thomas::Input::IsKeyPressed(TH_KEY_W)) {
			TH_CORE_INFO("keypressed");
		}
	}

	void OnDestroy()
	{

	}
};

void Test();
#pragma once
#include "ScriptUtils.h"

struct Cheat_Mode : Thomas::ScriptableEntity
{
	void OnCreate()
	{

	}

	void OnUpdate()
	{
		
		if (cheatMode == true) {
			
			bool cheatActivated = cheatMode;
			if (cheatActivated)
			{
				auto& combat = GetComponent<Thomas::CombatComponent>();
				combat.health = 1000000000;
				combat.attack = 1000000000;
				cheatActivated = !cheatActivated;
			}
		}
		else
		{
			auto& combat = GetComponent<Thomas::CombatComponent>();
			combat.health = 1;
			combat.attack = 1;
		}

	}

	void OnDestroy()
	{

	}
};
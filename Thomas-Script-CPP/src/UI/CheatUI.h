#pragma once
#include "../ScriptUtils.h"
//#include "Thomas/Scene/Entity.h"
struct CheatUI : Thomas::ScriptableEntity
{
	void OnCreate()
	{
		TH_CORE_INFO("Chaeat Mode Script Instantiated");
	}

	void OnUpdate()
	{
		
		if (cheatMode == true) {
			
			
			bool cheatActivated = cheatMode;
			if (cheatActivated)
			{
				
				auto& combat = GetComponent<Thomas::CombatComponent>();
				std::cout << "Health  " << combat.health << "\n";
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
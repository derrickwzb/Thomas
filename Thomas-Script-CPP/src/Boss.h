#pragma once
#include "ScriptUtils.h"
//#include "Managers/GameManager.h"

struct Boss : Thomas::ScriptableEntity
{
	void OnCreate()
	{
		TH_CORE_INFO("Boss Script Instantiated");
	}

	void OnUpdate(Thomas::Timestep ts)
	{

	}

	void OnDestroy()
	{

	}
};
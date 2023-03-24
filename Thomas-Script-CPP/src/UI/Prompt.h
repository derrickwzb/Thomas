/******************************************************************************/
/*!
\file		Prompt.h
\author 	Derrick Woo
\par    	email: d.woo@digipen.edu
\date   	24/3/2023
\brief		This file contains the functions and declarations of Prompt script.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include "../ScriptUtils.h"

float g_PromptTimer;

class Prompt : public Thomas::ScriptableEntity
{
public:
	void OnCreate()
	{
		TH_CORE_INFO("Prompt Script Instantiated.");
		g_PromptTimer = 0.f;
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		auto g_player = GetScene()->GetEntityByName("player");
		//bind position wip


		if (g_PromptTimer > 5.0f)
		{
			auto texture = GetComponent<Thomas::Texture>();
			//change texture to empty. wip
			g_PromptTimer = 0.f;
		}
		g_PromptTimer += ts;
	}

	void OnDestroy()
	{

	}

};

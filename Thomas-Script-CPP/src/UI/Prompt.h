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
#include "../Player.h"

static float g_PromptTimer;
static int g_Sequence;

class Prompt : public Thomas::ScriptableEntity
{
public:
	void OnCreate()
	{
		TH_CORE_INFO("Prompt Script Instantiated.");
		g_PromptTimer = 0.f;
		g_Sequence = 0;

		auto& trans = GetComponent<Thomas::Transform>();

		auto& type = GetComponent<Thomas::ObjectType>();

		type.fix_ui_trans.x = trans.translation.x - Thomas::Graphics::cam_stuff.translation.x;
		type.fix_ui_trans.y = trans.translation.y - Thomas::Graphics::cam_stuff.translation.y;

		transx = type.fix_ui_trans.x;
		scalex = trans.scaling.x;
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		auto& trans = GetComponent<Thomas::Transform>();
		auto& type = GetComponent<Thomas::ObjectType>();
		auto& tex = GetComponent<Thomas::Texture>();

		trans.translation.x = type.fix_ui_trans.x + Thomas::Graphics::cam_stuff.translation.x;
		trans.translation.y = type.fix_ui_trans.y + Thomas::Graphics::cam_stuff.translation.y;

		if (g_gameStateCurr == GameState::Level1)
		{
			if (g_Sequence == 0)
			{
				//show shoot all enemies down
				g_PromptTimer = 0.f;
			}
			else if (g_Sequence == 1 && g_points == 1)
			{
				//show collected one recipe find the next one
				g_PromptTimer = 0.f;
			}
			else if (g_Sequence == 2 && g_points >= 2)
			{
				//show proceeed to kitchen
				g_PromptTimer = 0.f;
			}
		}
		if (g_gameStateCurr == GameState::Level2)
		{
			if (g_Sequence == 0)
			{
				//show shoot all enemies down and bears
				g_PromptTimer = 0.f;
			}
			else if (g_Sequence == 1 )
			{
				//show traps
				g_PromptTimer = 0.f;
			}
			else if (g_Sequence == 2)
			{
				//show what traps does
				g_PromptTimer = 0.f;
			}
			else if (g_Sequence == 3 && g_points >= 2)
			{
				//show go into backroom
				g_PromptTimer = 0.f;
			}

			if (g_puddle_collide == true)
			{
				//show corrupted go to sink
				g_PromptTimer = 0.f;
			}
		}
			
		if (g_PromptTimer > 5.0f)
		{
			//change texture to empty.wip
			
			g_Sequence++;
		}

		g_PromptTimer += ts;
	}

	void OnDestroy()
	{

	}

};

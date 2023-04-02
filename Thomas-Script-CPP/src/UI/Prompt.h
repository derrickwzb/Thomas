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
		auto& tex = GetComponent<Thomas::Texture>();
		if (g_gameStateCurr == GameState::Level1)
		{
			tex.texid = Thomas::stash.Text_Storage["Prompt_one.png"];
		}
		else if (g_gameStateCurr == GameState::Level2)
		{
			tex.texid = Thomas::stash.Text_Storage["Prompt_five.png"];
		}
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
				g_PromptTimer = 0.f;
				tex.texid = Thomas::stash.Text_Storage["Prompt_one.png"];
				trans.alpha_val = 1.f;
			}
			else if (g_Sequence == 1 && g_points == 1)
			{
				g_PromptTimer = 0.f;
				tex.texid = Thomas::stash.Text_Storage["Prompt_two.png"];
				trans.alpha_val = 1.f;
			}
			else if (g_Sequence == 2 && g_points >= 2)
			{
				g_PromptTimer = 0.f;
				tex.texid = Thomas::stash.Text_Storage["Prompt_four.png"];
				trans.alpha_val = 1.f;
			}
		}
		if (g_gameStateCurr == GameState::Level2)
		{
			if (g_Sequence == 0)
			{
				g_PromptTimer = 0.f;
				tex.texid = Thomas::stash.Text_Storage["Prompt_five.png"];
				trans.alpha_val = 1.f;
			}
			else if (g_Sequence == 1 )
			{
				g_PromptTimer = 0.f;
				tex.texid = Thomas::stash.Text_Storage["Prompt_six.png"];
				trans.alpha_val = 1.f;
			}
			else if (g_Sequence == 2)
			{
				g_PromptTimer = 0.f;
				tex.texid = Thomas::stash.Text_Storage["Prompt_seven.png"];
				trans.alpha_val = 1.f;
			}
			else if (g_Sequence == 3 && g_points >= 2)
			{
				g_PromptTimer = 0.f;
				tex.texid = Thomas::stash.Text_Storage["Prompt_nine.png"];
				trans.alpha_val = 1.f;
				
			}

			if (g_puddle_collide == true)
			{

				g_PromptTimer = 0.f;
				tex.texid = Thomas::stash.Text_Storage["Prompt_eight.png"];
				trans.alpha_val = 1.f;
			}
		}
			
		if (g_PromptTimer > 5.0f)
		{
			trans.alpha_val = 0.f;
			g_Sequence++;
		}

		g_PromptTimer += ts;
	}

	void OnDestroy()
	{

	}

};

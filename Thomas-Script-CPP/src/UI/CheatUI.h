/******************************************************************************/
/*!
\file		CheatUI.h
\author 	Derrick Woo
\par    	email: d.woo@digipen.edu
\date   	10/3/2023
\brief		This file contains the functions and declarations of CheatUI script.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include "../ScriptUtils.h"

struct CheatUI : Thomas::ScriptableEntity
{
	bool CheckBounds(float Cursor_X, float Cursor_Y, glm::vec2 min_pos, glm::vec2 max_pos) {
		if (Cursor_X >= min_pos.x && Cursor_Y >= min_pos.y && Cursor_X <= max_pos.x && Cursor_Y <= max_pos.y)
			return true;
		else
			return false;
	}

	void OnCreate()
	{
		TH_CORE_INFO("CheatUI Script Instantiated");
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		(void)ts;
		float Cursor_X = Thomas::Input::GetMouseX() - Thomas::Graphics::width / 2;
		float Cursor_Y = -(Thomas::Input::GetMouseY() - Thomas::Graphics::height / 2);
		auto& data = GetComponent<Thomas::Texture>();
		auto& trans = GetComponent<Thomas::Transform>();

		if (CheckBounds(Cursor_X, Cursor_Y, trans.global_min, trans.global_max))
		{
			if (Thomas::Input::IsMouseButtonClicked(TH_MOUSE_BUTTON_LEFT))
			{
				if (g_CheatMode)
				{
					g_CheatMode = false;
					data.texid = Thomas::stash.Text_Storage["CheckboxEmpty.png"];
				}
				else
				{
					g_CheatMode = true;
					data.texid = Thomas::stash.Text_Storage["CheckboxToggle.png"];
				}
			}
		}
	}

	void OnDestroy()
	{
	}
};
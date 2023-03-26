/******************************************************************************/
/*!
\file		PlayerUI.h
\author 	Chen XinPeng
\email:		c.xinpeng@digipen.edu
\date   	10/3/2023
\brief		This file contains the functions and declarations of player ui script.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/
#pragma once
#include "../ScriptUtils.h"
#include "../Puddle.h"
#include "../Player.h"

static float posion_length{};

class PlayerUI : public Thomas::ScriptableEntity
{
	void OnCreate()
	{
		auto& trans = GetComponent<Thomas::Transform>();
		auto& type = GetComponent<Thomas::ObjectType>();

		type.fix_ui_trans.x = trans.translation.x - Thomas::Graphics::cam_stuff.translation.x;
		type.fix_ui_trans.y = trans.translation.y - Thomas::Graphics::cam_stuff.translation.y;
	}
	void OnUpdate(Thomas::Timestep ts)
	{
		auto& trans = GetComponent<Thomas::Transform>();
		auto& type = GetComponent<Thomas::ObjectType>();
		auto& tex = GetComponent<Thomas::Texture>();

		trans.translation.x = type.fix_ui_trans.x + Thomas::Graphics::cam_stuff.translation.x;
		trans.translation.y = type.fix_ui_trans.y + Thomas::Graphics::cam_stuff.translation.y;

		std::string name = GetComponent<Thomas::TagComponent>().tag;

		if (name == "Poison_outline") {
			posion_length = trans.translation.x + (trans.scaling.x / 2);
		}

		if (g_gameStateCurr == GameState::Level2 || g_gameStateCurr == GameState::Level3B) {
			if (name == "Poisonbar") {
				if (g_CheatMode == false) {
					if (g_puddle_collide == true) {
						if ((trans.translation.x + trans.scaling.x / 2) <= posion_length) {
							trans.scaling.x += ts / 5.f;
							type.fix_ui_trans.x += (ts) / 10.f;
						}
						else {
							g_gameStateNext = GameState::GameOver;
						}
					}
					else {
						type.fix_ui_trans.x -= trans.scaling.x / 2;
						trans.scaling.x = 0;
					}
				}
			}
		}
		if (name == "GreyRecipe1") {
			if (g_points == 1) {
				type.destroy_pickup = true;
			}
		}
		if (name == "GreyRecipe2") {
			if (g_points == 2) {
				type.destroy_pickup = true;
			}
		}

		if (name == "Recipe1") {
			if (g_points >= 1) {
				tex.text_show = true;
			}
			else {
				tex.text_show = false;
			}
		}
		if (name == "Recipe2") {
			if (g_points == 2) {
				tex.text_show = true;
			}
			else {
				tex.text_show = false;
			}
		}
	}

	void OnDestroy()
	{

	}
};
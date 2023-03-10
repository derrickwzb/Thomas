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

		trans.translation.x = type.fix_ui_trans.x + Thomas::Graphics::cam_stuff.translation.x;
		trans.translation.y = type.fix_ui_trans.y + Thomas::Graphics::cam_stuff.translation.y;

		std::string name = GetComponent<Thomas::TagComponent>().tag;

		if (name == "Poison_outline") {
			posion_length = trans.translation.x + (trans.scaling.x / 2);
		}

		if (g_gameStateCurr == GameState::Level2) {
			if (name == "Poisonbar") {
				if (g_CheatMode == false) {
					if (g_puddle_collide == true) {
						if ((trans.translation.x + trans.scaling.x / 2) <= posion_length) {
							trans.scaling.x += ts / 4.f;
							type.fix_ui_trans.x += (ts) / 8.f;
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
		if (name == "Recipe1") {
			if (g_points == 1) {
				type.destroy_pickup = true;
			}
		}
		if (name == "Recipe2") {
			if (g_points == 2) {
				type.destroy_pickup = true;
			}
		}
	}

	void OnDestroy()
	{

	}
};
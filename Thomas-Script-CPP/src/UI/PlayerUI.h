#pragma once
#include "../ScriptUtils.h"
//#include "../Managers/GameManager.h"
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

		if (g_puddle_collide == true) {
			if (name == "Poisonbar") {

				if (g_gameStateCurr == GameState::Level2)
				{
					if ((trans.translation.x + trans.scaling.x / 2) <= posion_length) {
						trans.scaling.x += ts;
						type.fix_ui_trans.x += ts / 2;
					}
				}
			}
		}

		Thomas::Scene* scene = GetScene();

		if (name == "recipe1") {
			if (g_points == 1) {
				scene->DestroyEntity(this->GetSelf());
			}
		}
		if (name == "recipe2") {
			if (g_points == 2) {
				scene->DestroyEntity(this->GetSelf());
			}
		}
	}

	void OnDestroy()
	{

	}
};
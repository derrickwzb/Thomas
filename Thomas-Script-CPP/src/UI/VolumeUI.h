#pragma once
#include "../ScriptUtils.h"
#include "../Managers/AudioManager.h"

static float vol_bar_min;
static float vol_bar_max;

class VolumeUI : public Thomas::ScriptableEntity
{
	void OnCreate() {

		auto& tag = GetComponent<Thomas::TagComponent>().tag;

		if (tag == "Volume_Fill") {

			auto& trans = GetComponent<Thomas::Transform>();

			float scaling = trans.scaling.x / 2;
			vol_bar_min = trans.translation.x - scaling;
			vol_bar_max = trans.translation.x + scaling;

		}

	}

	void OnUpdate(Thomas::Timestep) {

		auto& tag = GetComponent<Thomas::TagComponent>().tag;

		if (tag == "Volume_Control") {

			auto& trans = GetComponent<Thomas::Transform>();
	
			if (trans.translation.x <= vol_bar_max - (trans.scaling.x / 2)) {
				//Check here for issues becuase the translation might be 0
				trans.translation.x *= (Thomas::CAudioEngine::curr_volume / max_volume);

			}

		}

	}

	void OnDestroy() {



	}
};

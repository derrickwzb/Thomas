/******************************************************************************/
/*!
\file		AudioManager.h
\author 	Brandon Zhuo Jian Yi
\par    	email: zhuo.j@digipen.edu
\date   	10/3/2023
\brief		This file contains the scripts for VolumeUI.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#pragma once
#include "../ScriptUtils.h"
#include "../Managers/AudioManager.h"
#include <iostream>
#include <string>

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
	
			if ( trans.translation.x < vol_bar_max + (trans.scaling.x / 2) ) { 
				trans.translation.x = ( (Thomas::CAudioEngine::curr_volume / max_volume) * (vol_bar_max - vol_bar_min) ) + vol_bar_min;
			}
		} 

		if (tag == "VolumeSFX_Control") {

			auto& trans = GetComponent<Thomas::Transform>();

			if (trans.translation.x < vol_bar_max + (trans.scaling.x / 2)) {
				trans.translation.x = ((Thomas::CAudioEngine::currSFX_volume / max_volume) * (vol_bar_max - vol_bar_min)) + vol_bar_min;
			}
		}
	}

	void OnDestroy() {
	}
};

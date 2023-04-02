/******************************************************************************/
/*!
\file		Pickables.h
\author 	Derrick Woo
\par    	email: d.woo@digipen.edu
\date   	10/3/2023
\brief		This file contains the functions and declarations of pickables script.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include "ScriptUtils.h"
#include "Player.h"


struct Pickables : Thomas::ScriptableEntity
{
	void OnCreate()
	{
		TH_CORE_INFO("Pickables Script Instantiated");
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		(void)ts;
		auto& type = GetComponent<Thomas::ObjectType>();
		auto& parts = GetComponent<Thomas::Additional_Parts>();
		if (type.pickup_collide == true) {
			parts.parts_Transform[0].alpha_val = 1.f;
			if (Thomas::Input::IsKeyPressed(TH_KEY_E)) {
				g_points += 1;
				SoundSFX_CurrChannel = Thomas::CAudioEngine::PlaySFXSound(Thomas::stash.Audio_Storage["Paper_Rustle.wav"], Thomas::CAudioEngine::currSFX_volume + 2.0f);
				TH_CORE_INFO("{0} points", g_points);
				type.destroy_pickup = true;
			}
		}
		else
			parts.parts_Transform[0].alpha_val = 0.f;
	}

	void OnDestroy()
	{

	}
};
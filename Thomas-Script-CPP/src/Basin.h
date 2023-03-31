#pragma once
#include "ScriptUtils.h"
#include "Managers/GameManager.h"
#include "Player.h"

static int basinTimer = 0;
static bool basinToggle = false;
static bool SoundSFXBasin_IsPlaying = false;

struct Basin : Thomas::ScriptableEntity
{

	void OnCreate()
	{
		TH_CORE_INFO("Basin Script Instantiated");
		auto& parts = GetComponent<Thomas::Additional_Parts>();
		parts.parts_Texture[1].slices = 6.f;
		parts.parts_Texture[1].speed = 10.f;
		parts.parts_Texture[1].switch_text = 0;
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		auto& type_data = GetComponent<Thomas::ObjectType>();
		auto& parts = GetComponent<Thomas::Additional_Parts>();
		if (type_data.basin_collide == true) 
		{
			if (g_puddle_collide == true) 
			{
				parts.parts_Transform[0].alpha_val = 1.f;
				if (Thomas::Input::IsKeyPressed(TH_KEY_E)) 
				{
					PlaySFXAudioOnce("Water_Tap.wav", Thomas::CAudioEngine::currSFX_volume);
					basinToggle = true;
				}
			}
			else
				parts.parts_Transform[0].alpha_val = 0.f;
		}

		if (basinToggle) 
		{
			parts.parts_Transform[1].alpha_val = 1.f;
			parts.parts_Texture[1].animation_but = 1;
			basinTimer ++;

			if (basinTimer > 100) 
			{
				basinTimer = 0;
				parts.parts_Transform[1].alpha_val = 0.f;
				parts.parts_Texture[1].animation_but = 0;
				basinToggle = false;
				g_puddle_collide = false;
			}
		}
	}

	void OnDestroy()
	{
	}

	void PlaySFXAudioOnce(std::string audioName, float volume)
	{
		std::string audioFilepath = Thomas::stash.Audio_Storage[audioName];

		if (!SoundSFXBasin_IsPlaying)
		{
			SoundSFX_CurrChannel = Thomas::CAudioEngine::PlaySFXSound(audioFilepath, volume);
			SoundSFXBasin_IsPlaying = true;
		}

		if (SoundSFXBasin_IsPlaying)
		{
			if (Thomas::CAudioEngine::IsPlaying(SoundSFX_CurrChannel))
			{
				SoundSFXBasin_IsPlaying = false;
			}
		}

	}

};
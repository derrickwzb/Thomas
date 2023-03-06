#pragma once
#include "../ScriptUtils.h"
#include "../UI/VolumeUI.h"
#include "../Managers/GameManager.h"



static float curr_volume;
static float min_volume;
static float max_volume;
static bool Sound_IsPlaying = false;
static int Sound_CurrChannel = 0;

class AudioManager : public Thomas::ScriptableEntity
{
public:

	void PlayBGMAudioOnce(std::string audioName, float volume)
	{

		std::string audioFilepath = Thomas::stash.Audio_Storage[audioName];

		if (!Sound_IsPlaying)
		{
			Sound_CurrChannel = Thomas::CAudioEngine::PlayBGMSound(audioFilepath, volume);
			Sound_IsPlaying = true;
		}

		if (Sound_IsPlaying)
		{
			if (Thomas::CAudioEngine::IsPlaying(Sound_CurrChannel))
			{
				Sound_IsPlaying = false;
			}
		}

	}

	void OnCreate()
	{
		TH_CORE_INFO("AudioManager Script Instantiated");
		curr_volume = 2.5f;
		min_volume = 0.f;
		max_volume = 5.f;

		Thomas::CAudioEngine::LoadSound(Thomas::stash.Audio_Storage["Main_Menu_BGM.wav"], true);
		Thomas::CAudioEngine::LoadSound(Thomas::stash.Audio_Storage["Game_BGM.wav"], true);


	}

	void OnUpdate(Thomas::Timestep ts)
	{
		if (g_gameStateCurr == GameState::MainMenu)
		{
			PlayBGMAudioOnce("Main_Menu_BGM.wav", curr_volume);
		}

		Thomas::CAudioEngine::SetChannelvolume(Sound_CurrChannel, curr_volume);

	}

	void OnDestroy()
	{
		Thomas::CAudioEngine::UnLoadSound("Main_Menu_BGM.wav");
		Thomas::CAudioEngine::UnLoadSound("Game_BGM.wav");

	}


};

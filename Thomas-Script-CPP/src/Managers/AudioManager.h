#pragma once
#include "../ScriptUtils.h"
#include "../Managers/GameManager.h"

static float min_volume;
static float max_volume;
static bool Sound_IsPlaying = false;
static int Sound_CurrChannel = 0;

class AudioManager : public Thomas::ScriptableEntity
{
public:


	void OnCreate()
	{
		TH_CORE_INFO("AudioManager Script Instantiated");
		min_volume = 0.0f;
		max_volume = 5.0f;

		Thomas::CAudioEngine::LoadSound(Thomas::stash.Audio_Storage["Main_Menu_BGM.wav"], true);
		Thomas::CAudioEngine::LoadSound(Thomas::stash.Audio_Storage["Game_BGM.wav"], true);


	}

	void OnUpdate(Thomas::Timestep ts)
	{
		if (g_gameStateCurr == GameState::MainMenu)
		{
			PlayBGMAudioOnce("Main_Menu_BGM.wav", Thomas::CAudioEngine::curr_volume);
			//std::cout << "Playing Audio" << std::endl;
		}

		std::cout << Thomas::CAudioEngine::curr_volume << std::endl;


		Thomas::CAudioEngine::SetChannelvolume(Sound_CurrChannel, Thomas::CAudioEngine::curr_volume);

		

	}

	void OnDestroy()
	{
		Thomas::CAudioEngine::UnLoadSound("Main_Menu_BGM.wav");
		Thomas::CAudioEngine::UnLoadSound("Game_BGM.wav");

	}

	void PlayBGMAudioOnce(std::string audioName, float volume)
	{

		std::string audioFilepath = Thomas::stash.Audio_Storage[audioName];

		std::cout << audioFilepath << std::endl;
		std::cout << volume << std::endl;

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

};

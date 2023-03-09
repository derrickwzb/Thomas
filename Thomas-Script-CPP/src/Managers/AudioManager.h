#pragma once
#include "../ScriptUtils.h"
#include "../Managers/GameManager.h"

static float min_volume;
static float max_volume;
static bool Sound_IsPlaying = false;
static int Sound_CurrChannel;

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

		if (g_gameStateCurr == GameState::MainMenu)
		{
			//This stops the previous channel before so it doesnt play main menu and game bgm
			if (g_gameStatePrev == GameState::Level1) {
				Thomas::CAudioEngine::StopChannel(Sound_CurrChannel);
			}
		}

		if (g_gameStateCurr == GameState::Level1)
		{
			//This stops the previous channel before so it doesnt play main menu and game bgm
			if (g_gameStatePrev == GameState::MainMenu) {
				Thomas::CAudioEngine::StopChannel(Sound_CurrChannel);
			}
		}

		if (g_gameStateCurr == GameState::Level2)
		{
			//This stops the previous channel before so it doesnt play main menu and game bgm
			if (g_gameStatePrev == GameState::Level1) {
				Thomas::CAudioEngine::StopChannel(Sound_CurrChannel);
			}
		}

	
	}

	void OnUpdate(Thomas::Timestep ts)
	{	
		if (g_gameStateCurr == GameState::MainMenu)
		{
			PlayBGMAudioOnce("Main_Menu_BGM.wav", Thomas::CAudioEngine::curr_volume);
		}

		if (g_gameStateCurr == GameState::Level1)
		{
			PlayBGMAudioOnce("Game_BGM.wav", Thomas::CAudioEngine::curr_volume);
		}

		if (g_gameStateCurr == GameState::Level2)
		{
			PlayBGMAudioOnce("Game_BGM.wav", Thomas::CAudioEngine::curr_volume);
		}

		//std::cout << Thomas::CAudioEngine::curr_volume << std::endl;
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

		//std::cout << volume << std::endl;

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

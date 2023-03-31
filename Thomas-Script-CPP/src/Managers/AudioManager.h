/******************************************************************************/
/*!
\file		AudioManager.h
\author 	Brandon Zhuo Jian Yi
\par    	email: zhuo.j@digipen.edu
\date   	10/3/2023
\brief		This file contains the scripts for audiomanager.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#pragma once
#include "../ScriptUtils.h"
#include "../Managers/GameManager.h"

static float min_volume;
static float max_volume;
static bool SoundBGM_IsPlaying = false;
static bool SoundSFX_IsPlaying = false;
static int Sound_CurrChannel;
static int SoundSFX_CurrChannel;


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
		Thomas::CAudioEngine::LoadSound(Thomas::stash.Audio_Storage["bug-death-splatter_new.wav"], false);
		Thomas::CAudioEngine::LoadSound(Thomas::stash.Audio_Storage["Player_Death.wav"], false);
		Thomas::CAudioEngine::LoadSound(Thomas::stash.Audio_Storage["Enemy_Death.wav"], false);
		Thomas::CAudioEngine::LoadSound(Thomas::stash.Audio_Storage["Water_Tap.wav"], false);
		
		//try to see if you need to loop the footsteps
		Thomas::CAudioEngine::LoadSound(Thomas::stash.Audio_Storage["cat-footsteps-idoors-carpet_5.wav"], false);

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
			if (g_gameStatePrev == GameState::CutScene) { 
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
		(void)ts;
		if (g_gameStateCurr == GameState::MainMenu)
		{
			PlayBGMAudioOnce("Main_Menu_BGM.wav", Thomas::CAudioEngine::curr_volume);
		}

		else if (g_gameStateCurr == GameState::Level1)
		{
			PlayBGMAudioOnce("Game_BGM.wav", Thomas::CAudioEngine::curr_volume);
		}

		else if (g_gameStateCurr == GameState::Level2)
		{
			PlayBGMAudioOnce("Game_BGM.wav", Thomas::CAudioEngine::curr_volume);
		}

		//std::cout << Thomas::CAudioEngine::curr_volume << std::endl;
		Thomas::CAudioEngine::SetChannelvolume(Sound_CurrChannel, Thomas::CAudioEngine::curr_volume);
		
		Thomas::CAudioEngine::Update();
	}

	void OnDestroy()
	{
		Thomas::CAudioEngine::UnLoadSound("Main_Menu_BGM.wav");
		Thomas::CAudioEngine::UnLoadSound("Game_BGM.wav");
		Thomas::CAudioEngine::UnLoadSound("bug-death-splatter_new.wav");
		Thomas::CAudioEngine::UnLoadSound("cat-footsteps-idoors-carpet_5.wav");
		Thomas::CAudioEngine::UnLoadSound("Player_Death.wav");
		Thomas::CAudioEngine::UnLoadSound("Enemy_Death.wav"); 
		Thomas::CAudioEngine::UnLoadSound("Water_Tap.wav");
		Thomas::CAudioEngine::Shutdown();
	}

	static void PlayBGMAudioOnce(std::string audioName, float volume)
	{
		std::string audioFilepath = Thomas::stash.Audio_Storage[audioName];

		//std::cout << audioFilepath << std::endl;

		if (!SoundBGM_IsPlaying)
		{
			Sound_CurrChannel = Thomas::CAudioEngine::PlayBGMSound(audioFilepath, volume);
			SoundBGM_IsPlaying = true;
		}

		if (SoundBGM_IsPlaying)
		{
			if (Thomas::CAudioEngine::IsPlaying(Sound_CurrChannel))
			{
				SoundBGM_IsPlaying = false;
			}
		}

	}
	
	static void PlaySFXAudioOnce(std::string audioName, float volume)
	{
		std::string audioFilepath = Thomas::stash.Audio_Storage[audioName];

		if (!SoundSFX_IsPlaying)
		{
			SoundSFX_CurrChannel = Thomas::CAudioEngine::PlaySFXSound(audioFilepath, volume);
			SoundSFX_IsPlaying = true;
		}

		if (SoundSFX_IsPlaying)
		{
			if (Thomas::CAudioEngine::IsPlaying(SoundSFX_CurrChannel))
			{
				SoundSFX_IsPlaying = false;
			}
		}

	}

};

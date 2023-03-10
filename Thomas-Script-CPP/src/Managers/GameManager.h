/******************************************************************************/
/*!
\file		GameManager.h
\author 	Derrick Woo
\par    	email: d.woo@digipen.edu
\date   	10/3/2023
\brief		This file contains the functions and declarations of gamemanager script.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include "../ScriptUtils.h"

static float g_GameTimer;
static bool g_IsPaused;

class GameManager : public Thomas::ScriptableEntity
{
public:

	void OnCreate()
	{
		TH_CORE_INFO("GameManager Script Instantiated");

		TH_CORE_INFO("GameManager : Game State set to INIT. ");
		g_GameTimer = 0.f;
		g_IsPaused = false;
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		g_GameTimer += ts;

		// SWITCHING SCENES PORTION
		if (g_gameStateCurr != g_gameStateNext)
		{
			g_gameStatePrev = g_gameStateCurr;
			g_gameStateCurr = g_gameStateNext;
			
			switch (g_gameStateCurr)
			{
			
			
			case GameState::Level1:
			{
		
				LoadNextScene(Thomas::stash.Scene_Storage["New_Level_2.json"]);
				break;
			}
			case GameState::MainMenu:
			{
				LoadNextScene(Thomas::stash.Scene_Storage["New_MainMenu.json"]);
				TH_CORE_INFO("loaded menu");
				break;
			}
			case GameState::Level2:
			{
				LoadNextScene(Thomas::stash.Scene_Storage["New_Level_2.json"]);
				break;
			}
			case GameState::Level3:
			{
				LoadNextScene(Thomas::stash.Scene_Storage["New_Level_3.json"]);
				break;
			}
			case GameState::Credits:
			{
				LoadNextScene(Thomas::stash.Scene_Storage["New_Credits_1.json"]);
				break;
			}
			case GameState::Credits_2:
			{
				LoadNextScene(Thomas::stash.Scene_Storage["New_Credits_2.json"]);
				break;
			}
			case GameState::HTP1:
			{
				LoadNextScene(Thomas::stash.Scene_Storage["New_HTP_1.json"]);
				break;
			}
			case GameState::HTP2:
			{
				LoadNextScene(Thomas::stash.Scene_Storage["New_HTP_2.json"]);
				break;
			}
			case GameState::Settings:
			{
				LoadNextScene(Thomas::stash.Scene_Storage["New_Settings.json"]);
				break;
			}
			case GameState::Pause:
			{
				Thomas::SceneSerializer serializer(GetScene());
				serializer.LoadScene(Thomas::stash.Scene_Storage["New_PauseMenu.json"]);
				break;
			}
			case GameState::CutScene:
			{
				LoadNextScene(Thomas::stash.Scene_Storage["New_CutScene_1.json"]);
				g_GameTimer = 0.f;
				break;
			}
			case GameState::GameOver:
			{
				LoadNextScene(Thomas::stash.Scene_Storage["New_GameOver.json"]);
				g_GameTimer = 0.f;
				break;
			}
			case GameState::Win:
			{
				LoadNextScene(Thomas::stash.Scene_Storage["New_Win.json"]);
				g_GameTimer = 0.f;
				break;
			}
			case GameState::Restart:
			{
				g_gameStateNext = g_gameStatePrev;
				break;
			}
			
			case GameState::Exit:
			{
				Thomas::Application::Get().Close();
				break;
			}
			default:
				break;
			}
		}
	}

	void LoadNextScene(const std::string& scene)
	{
		Thomas::SceneSerializer serializer(GetScene());
		serializer.Deserialize(scene);
	}

	void OnDestroy()
	{
	}
};
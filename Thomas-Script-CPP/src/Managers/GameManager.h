#pragma once
#include "../ScriptUtils.h"

enum class GameState
{
	MainMenu,
	CutScene,

	Level1,
	Level2,
	Level3,

	Pause,

	Credits,
	Credits_2,

	HTP1,
	HTP2,

	Settings,

	Restart,
	GameOver,
	Win,
	QuitConfirmation,
	Exit
};

static float g_GameTimer;
static GameState g_gameStateCurr;
static GameState g_gameStatePrev;
static GameState g_gameStateNext;

class GameManager : public Thomas::ScriptableEntity
{
public:

	void OnCreate()
	{
		TH_CORE_INFO("GameManager Script Instantiated");
		g_gameStateCurr = GameState::MainMenu;
		g_gameStateNext = GameState::MainMenu;
		g_gameStatePrev = GameState::MainMenu;
		TH_CORE_INFO("GameManager : Game State set to INIT. ");
		g_GameTimer = 0.f;
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		g_GameTimer += ts;

		switch(g_gameStateCurr)
		{
		case GameState::Exit:
		{
			Thomas::Application::Get().Close();
			break;
		}
		//case GameState::CutScene:
		//{
		//	if (g_GameTimer) // add time limit
		//	{
		//		LoadNextScene("Level1");
		//	}
		//	break;
		//}
		//case GameState::Win :
		//{
		//	if (g_GameTimer) // add time limit
		//	{
		//		LoadNextScene("MainMenu");
		//	}
		//	break;
		//}
		//case GameState::GameOver:
		//{
		//	if (g_GameTimer) // add time limit
		//	{
		//		LoadNextScene("GameOVer");
		//	}
		//	break;
		//}
		}
		


		// SWITCHING SCENES PORTION
		if (g_gameStateCurr != g_gameStateNext)
		{
			if (g_gameStateCurr == GameState::Pause)
			{
				Thomas::SceneSerializer serializer(GetScene());
				serializer.RemoveScene(Thomas::stash.Scene_Storage["Pause"]);
			}

			g_gameStatePrev = g_gameStateCurr;
			g_gameStateCurr = g_gameStateNext;
			
			switch (g_gameStateCurr)
			{
			case GameState::MainMenu:
			{
				LoadNextScene("MainMenu");
				break;
			}
			
			case GameState::Level1:
			{
				LoadNextScene("Level1");
				break;
			}
			case GameState::Level2:
			{
				LoadNextScene("Level2");
				break;
			}
			case GameState::Level3:
			{
				LoadNextScene("Level3");
				break;
			}
			case GameState::Credits:
			{
				LoadNextScene("../Assets/Scene/New_Credits.json");
				break;
			}
			case GameState::Credits_2:
			{
				LoadNextScene("Credits_2");
				break;
			}
			case GameState::HTP1:
			{
				LoadNextScene("HTP1");
				break;
			}
			case GameState::HTP2:
			{
				LoadNextScene("HTP2");
				break;
			}
			case GameState::QuitConfirmation:
			{
				LoadNextScene("QuitConfirm");
				break;
			}
			case GameState::Settings:
			{
				LoadNextScene("Settings");
				break;
			}
			case GameState::Pause:
			{
				Thomas::SceneSerializer serializer(GetScene());
				serializer.LoadScene(Thomas::stash.Scene_Storage["Pause"]);
				break;
			}
			case GameState::CutScene:
			{
				LoadNextScene("CutScene");
				g_GameTimer = 0.f;
				break;
			}
			case GameState::GameOver:
			{
				LoadNextScene("GameOver");
				g_GameTimer = 0.f;
				break;
			}
			case GameState::Win:
			{
				LoadNextScene("Win");
				g_GameTimer = 0.f;
				break;
			}
			case GameState::Restart:
			{
				g_gameStateNext = g_gameStatePrev;
			}
			}
		}
	}

	void LoadNextScene(const std::string& scene)
	{
		Thomas::SceneSerializer serializer(GetScene());
		//serializer.Deserialize(Thomas::stash.Scene_Storage[scene]);
		serializer.Deserialize(scene);
	}

	void OnDestroy()
	{

	}
	
};
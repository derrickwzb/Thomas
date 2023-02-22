#pragma once
#include "../ScriptUtils.h"
#include "../AllScripts.h"

enum class GameState
{
	MainMenu,
	CutScene,
	Level1,

	Credits,
	Credits_2,

	HTP1,
	HTP2,

	GameOver,
	QuitConfirmation,
	Exit
};

static GameState g_gameStateCurr;
static GameState g_gameStatePrev;
static GameState g_gameStateNext;

class GameManager : Thomas::ScriptableEntity
{
public:

	void OnCreate()
	{
		TH_CORE_INFO("GameManager Script Instantiated");
		g_gameStateCurr = GameState::MainMenu;
		TH_CORE_INFO("GameManager : Game State set to INIT. ");
		m_ActiveScene = GetScene();
	}

	void OnUpdate(Thomas::Timestep ts)
	{

		switch (g_gameStateCurr)
		{
		case GameState::Exit:
		{
			Thomas::Application::Get().Close();
			break;
		}

		}
		if (g_gameStateCurr != g_gameStateNext)
		{
			g_gameStatePrev = g_gameStateCurr;
			g_gameStateCurr = g_gameStateNext;
			//switch (g_gameStateCurr)
			//{
			//case GameState::MainMenu:
			//	//Thomas::SceneSerializer serializer(m_ActiveScene);
			//	//serializer.Deserialize(Thomas::stash.Audio_Storage);
			//}
		}
	}

	void OnDestroy()
	{

	}


private:
	//Player m_player;
	Thomas::Scene* m_ActiveScene;
	
};
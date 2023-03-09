#pragma once
#include "Thomas/Scene/Entity.h"
#include "Thomas/Scene/Components.h"
#include "Thomas/Renderer/Box_collider.h"

//#include "Thomas/Renderer/Transform.h"


#include "Thomas.h"
#include "Thomas/Audio/AudioEngine.h"



enum class GameState
{
	NONE,
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

inline static GameState g_gameStateCurr{ GameState::MainMenu };
inline static GameState g_gameStateNext{ GameState::MainMenu };
inline static GameState g_gameStatePrev{ GameState::MainMenu };
inline static bool g_CheatMode{ false };
//static GameState g_gameStatePrev;
//static GameState g_gameStateNext;


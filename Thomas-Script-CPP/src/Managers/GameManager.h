#pragma once
#include "../ScriptUtils.h"
#include "../AllScripts.h"

enum class GameState
{
	MainMenu
};

static GameState m_gameStateCurr;
static GameState m_gameStatePrev;
static GameState m_gameStateNext;
static int Level;

class GameManager : Thomas::ScriptableEntity
{
public:
	
	void OnCreate()
	{
		TH_CORE_INFO("GameManager Script Instantiated");
		m_gameStateCurr = GameState::MainMenu;
		TH_CORE_INFO("GameManager : Game State set to INIT. ");
		m_ActiveScene = GetScene();
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		switch (m_gameStateCurr) 
		{
		}
	}

	void OnDestroy()
	{

	}


private:
	//Player m_player;
	Thomas::Scene* m_ActiveScene;


};
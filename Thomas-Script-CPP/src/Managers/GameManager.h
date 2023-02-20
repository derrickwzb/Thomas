#pragma once
#include "../ScriptUtils.h"
#include "../AllScripts.h"

class GameManager : Thomas::ScriptableEntity
{
public:
	static int Level;
	

	enum class GameState
	{
		MainMenu
	};
	
	static GameState m_gameState;

	static Player& GetPlayer()
	{
		return m_player;
	}

	static Thomas::Scene* GetScene()
	{
		return m_ActiveScene;
	}

	void OnCreate()
	{
		TH_CORE_INFO("GameManager Script Instantiated");
		m_gameState = GameState::MainMenu;
		TH_CORE_INFO("GameManager : Game State set to INIT. ");
		m_ActiveScene = GetScene();
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		switch (m_gameState) {


		}


	}

	void OnDestroy()
	{

	}


private:
	Player m_player;
	Thomas::Scene* m_ActiveScene;


};
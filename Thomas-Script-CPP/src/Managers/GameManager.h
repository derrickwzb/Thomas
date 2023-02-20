#pragma once
#include "../ScriptUtils.h"
#include "../AllScripts.h"

class GameManager : Thomas::ScriptableEntity
{
public:
	static int Level;
	

	enum class GameState
	{
		Init,
		Game,
		Dead
	};
	
	static GameState m_gameState;

	void OnCreate()
	{
		TH_CORE_INFO("GameManager Script Instantiated");
		m_gameState = GameState::Init;
	}

	void OnUpdate()
	{
		Thomas:: Graphics::cam_stuff.Camera2D_Update();


		auto& trans = GetComponent<Thomas::Transform>().translation;
	}

	void OnDestroy()
	{

	}

private:
	Player m_player;


};
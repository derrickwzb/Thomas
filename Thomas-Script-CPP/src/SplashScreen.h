#pragma once
#include "ScriptUtils.h"

static float g_SplashScreenTimer;

class SplashScreen : public Thomas::ScriptableEntity
{
public:
	void OnCreate()
	{
		TH_CORE_INFO("Splash Screen script binded");
		g_SplashScreenTimer = 0.f;
		auto& texture = GetComponent<Thomas::Texture>();

		texture.texid = Thomas::stash.Text_Storage["DigipenLogo.png"];
	}


	void OnUpdate(Thomas::Timestep ts)
	{
		auto& texture = GetComponent<Thomas::Texture>();
		texture.texid = Thomas::stash.Text_Storage["DigipenLogo.png"];
		if (g_SplashScreenTimer >= 2.f)
		{
			g_gameStateNext = GameState::MainMenu;
		}
		g_SplashScreenTimer += ts;
	}

	void OnDestroy()
	{

	}

};

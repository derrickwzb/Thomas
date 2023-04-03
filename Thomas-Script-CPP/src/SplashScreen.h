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

		texture.texid = Thomas::stash.Text_Storage["Digipen_Logo.png"];
	}


	void OnUpdate(Thomas::Timestep ts)
	{
		auto& texture = GetComponent<Thomas::Texture>();
		texture.texid = Thomas::stash.Text_Storage["Digipen_Logo.png"];
		if (g_SplashScreenTimer >= 2.f)
		{
			Thomas::SceneSerializer serializer(GetScene());
			serializer.Deserialize(Thomas::stash.Scene_Storage["New_MainMenu.json"]);
		}
		g_SplashScreenTimer += ts;
	}

	void OnDestroy()
	{

	}

};

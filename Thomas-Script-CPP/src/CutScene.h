#pragma once
#include "ScriptUtils.h"
#include "Managers/GameManager.h"

static float g_CutSceneTimer;
static int CutScene_No;

class CutScene : public Thomas::ScriptableEntity
{
public:

	void OnCreate()
	{
		TH_CORE_INFO("CutScene Manager Script Instantiated.");
		g_CutSceneTimer = 0.f;
		CutScene_No = 0;
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		if (g_gameStateCurr == GameState::CutScene)
		{
			auto& texture = GetComponent<Thomas::Texture>();
			if (g_CutSceneTimer <= (CutScene_No + 1) * 3.f) {
				texture.texid = Thomas::stash.Text_Storage["cut1.png"] + CutScene_No;
			}
			else {
				CutScene_No++;
			}
			if (CutScene_No == 6) {
				g_gameStateNext = GameState::Level1;
				g_CutSceneTimer = 0.f;
				CutScene_No = 0;
			}
			g_CutSceneTimer += ts;
		}
	}

	void OnDestroy()
	{

	}
};
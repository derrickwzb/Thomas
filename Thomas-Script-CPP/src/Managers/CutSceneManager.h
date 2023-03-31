/******************************************************************************/
/*!
\file		CurSceneManager.h
\author 	Derrick Woo
\par    	email: d.woo@digipen.edu
\date   	10/3/2023
\brief		This file contains the functions and declarations of CutSceneManager script.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include "../ScriptUtils.h"

static float g_CutSceneTimer;
static int CutScene_No;

enum class CutScenes
{
	CS_Start,
	CS_Level2,
	CS_Level3

};

static CutScenes CS;

class CutScene : public Thomas::ScriptableEntity
{
public:

	void OnCreate()
	{
		auto& texture = GetComponent<Thomas::Texture>();
		TH_CORE_INFO("CutScene Manager Script Instantiated.");
		g_CutSceneTimer = 0.f;
		CutScene_No = 1;
		if (g_gameStatePrev == GameState::MainMenu)
		{
			CS = CutScenes::CS_Start;
			texture.texid = Thomas::stash.Text_Storage["CS_start1.png"];
		}
		else if (g_gameStatePrev == GameState::Level1)
		{
			CS = CutScenes::CS_Level2;
		}
		else if (g_gameStatePrev == GameState::Level2)
		{
			CS = CutScenes::CS_Level3;
		}
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		auto& texture = GetComponent<Thomas::Texture>();
		if (CS == CutScenes::CS_Start)
		{
			if (CutScene_No >= 10)
			{
				CutScene_No = 1;
				g_gameStateNext = GameState::Level1;
			}
			else
			{
				if (g_CutSceneTimer > 3.f)
				{
					CutScene_No++;
					std::string filepath = "CS_start";
					filepath = filepath + std::to_string(CutScene_No) + ".png";
					texture.texid = Thomas::stash.Text_Storage[filepath];
					g_CutSceneTimer = 0.f;
					
				}
			}
			
		}
		else if (CS == CutScenes::CS_Level2)
		{
			if (CutScene_No >= 10)
			{
				CutScene_No = 1;
				g_gameStateNext = GameState::Level1;
			}
			else
			{
				if (g_CutSceneTimer > 3.f)
				{
					CutScene_No++;
					std::string filepath = "CS_start";
					filepath = filepath + std::to_string(CutScene_No) + ".png";
					texture.texid = Thomas::stash.Text_Storage[filepath];
					g_CutSceneTimer = 0.f;

				}
			}
		}
		g_CutSceneTimer += ts;
	}

	void OnDestroy()
	{
	}
};
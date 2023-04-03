/******************************************************************************/
/*!
\file		Puddle.h
\author 	Xie Zhi Xiong / Chen XinPeng
\par    	email: xiong.x@digipen.edu / c.xinpeng@digipen.edu
\date   	10/3/2023
\brief		This file contains the functions and declarations of puddle script.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include "ScriptUtils.h"
#include "Managers/GameManager.h"
#include "Player.h"

static int g_corruption_points{};
static int timer = 0;

struct Puddle : Thomas::ScriptableEntity
{
	void OnCreate()
	{
		TH_CORE_INFO("Puddle Script Instantiated");
		auto& type_data = GetComponent<Thomas::ObjectType>();
		type_data.puddle_collide = false;
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		(void)ts;
		auto& type_data = GetComponent<Thomas::ObjectType>();
		auto& trans = GetComponent<Thomas::Transform>();
		auto& text = GetComponent<Thomas::Texture>();
		
		if (type_data.puddle_collide == true) {
			g_puddle_collide = true;
			trans.alpha_val = 1.f;
			text.animation_but = 1;
			g_corruption_points++;
			timer++;
			if (timer > 100) {
				timer = 0;
				type_data.destroy_pickup = true;
			}
		}
	}

	void OnDestroy()
	{

	}
};
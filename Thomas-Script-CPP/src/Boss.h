/******************************************************************************/
/*!
\file		Boss.h
\author 	Chen XinPeng
\email:		c.xinpeng@digipen.edu
\date   	10/3/2023
\brief		This file contains the functions and declarations of boss script.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include "ScriptUtils.h"
//#include "Managers/GameManager.h"

struct Boss : Thomas::ScriptableEntity
{
	void OnCreate()
	{
		TH_CORE_INFO("Boss Script Instantiated");
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		(void)ts;
	}

	void OnDestroy()
	{

	}
};
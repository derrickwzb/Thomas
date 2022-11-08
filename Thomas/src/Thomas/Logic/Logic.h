/*!*************************************************************************
\file           Logic.h
\author         Chen XinPeng
\par DP email:  c.xinpeng@digipen.edu
\par Programming CSD2400 Game project
\date           28/09/2022
\brief
This file contains the declaration for logic system
****************************************************************************/
#pragma once
#include "thpch.h"
#include "Thomas/Core/Timestep.h"

namespace Thomas {
	using EntityID = unsigned int;
	class GameObjectFactory;

	class Logic01
	{
	public:
		void update(EntityID entity, Timestep ts);
	};

	class Logic02 {
	public:
		void update(EntityID entity, Timestep ts);
	};

	class Logic {
	public:
		void Init();
		void Update(std::vector<EntityID> allentity, Timestep ts);

		inline static double Logic_timetaken = 0;
	};

	inline static Logic logic;

}

/*!*************************************************************************
\file           Scene.cpp
\author         Derrick Woo, Chen XinPeng
\par DP email:  d.woo@digipen.edu, c.xinpeng@digipen.edu
\par Programming CSD2400 Game project
\date           26/10/2022
\brief
This file contains declaration for functions used in a scene
****************************************************************************/
#pragma once
#include "Entity.h"

namespace Thomas
{
	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;
		Entity CreateEntity(const std::string& name);
		void OnUpdate(Timestep ts);
		void OnViewportResize(uint32_t width, uint32_t height);


	private:
		uint32_t Viewport_width;
		uint32_t Viewport_height;

	};


}



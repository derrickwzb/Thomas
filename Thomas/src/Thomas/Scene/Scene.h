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
		//Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnRuntimeStart();
		void OnRuntimeStop();

		void OnSimulationStart();
		void OnSimulationStop();

		void OnUpdateRuntime(Timestep ts);
		//void OnUpdateSimulation(Timestep ts , EditorCamera& camera);
		void OnViewportResize(uint32_t width, uint32_t height);

		void DuplicateEntity(Entity entity);

		Entity GetPrimaryCameraEntity();


		template<typename ... Compo




		void OnUpdate(Timestep ts);
		void OnViewportResize(uint32_t width, uint32_t height);


	private:
		uint32_t Viewport_width;
		uint32_t Viewport_height;

	};


}



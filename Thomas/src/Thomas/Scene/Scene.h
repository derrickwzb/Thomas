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
//#include "Entity.h"
#include <string>
#include <memory>
#include "Thomas/Core/Timestep.h"

namespace Thomas
{

	class Entity;
	class GameObjectFactory;

	class Scene
	{
	public:
		Scene();
		~Scene();
		Entity CreateEntity(const std::string& name = std::string());
		//EntityID CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
		//void DestroyEntity(EntityID entity);

		//void OnRuntimeStart();
		//void OnRuntimeStop();

		//void OnSimulationStart();
		//void OnSimulationStop();

		//void OnUpdateRuntime(Timestep ts);
		////void OnUpdateSimulation(Timestep ts , EditorCamera& camera);
		//void OnViewportResize(uint32_t width, uint32_t height);

		//void DuplicateEntity(EntityID entity);

		//EntityID GetPrimaryCameraEntity();





		void OnUpdate(Timestep ts);
		//void OnViewportResize(uint32_t width, uint32_t height);


	private:
		uint32_t Viewport_width;
		uint32_t Viewport_height;

		std::shared_ptr<GameObjectFactory> m_Registry;

		friend class Entity;
		friend class SceneHierarchyPanel;

	};


}



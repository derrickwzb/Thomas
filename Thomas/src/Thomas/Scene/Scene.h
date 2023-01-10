/*!*************************************************************************
\file           Scene.cpp
\author         Derrick Woo
\par DP email:  d.woo@digipen.edu
\par Programming CSD2400 Game project
\date           26/10/2022
\brief
This file contains declaration for functions used in a scene
****************************************************************************/
#pragma once
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
		Entity& CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnUpdate(Timestep ts);

		std::shared_ptr<GameObjectFactory> GetRegistry();

	private:
		uint32_t Viewport_width;
		uint32_t Viewport_height;

		std::shared_ptr<GameObjectFactory> m_Registry;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
		friend class EditorLayer;
		friend class Physics;
		friend class AStarPathfinding;
	};


}



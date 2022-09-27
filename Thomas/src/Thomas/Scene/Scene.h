#pragma once

#include "thpch.h"
#include "Thomas.h"

namespace Thomas {
	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

	private:

	};
}
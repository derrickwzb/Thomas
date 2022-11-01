#pragma once
#include "Entity.h"
namespace Thomas
{
	class Scene
	{
	public:
		Scene();
		~Scene();
		Entity CreateEntity(const std::string& name);
		void OnUpdate(Timestep ts);
		void OnViewportResize(uint32_t width, uint32_t height);


	private:
		uint32_t Viewport_width;
		uint32_t Viewport_height;

	};


}



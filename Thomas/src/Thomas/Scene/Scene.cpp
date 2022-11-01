#include "thpch.h"
#include "Scene.h"

namespace Thomas
{
	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity newentity = factory.CreateEmptyComposition();
		TagComponent newtag;
		return Entity();
	}

	void Scene::OnUpdate(Timestep ts)
	{
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
	}

}
/*!*************************************************************************
\file           Scene.cpp
\author         Derrick Woo, Chen XinPeng
\par DP email:  d.woo@digipen.edu, c.xinpeng@digipen.edu
\par Programming CSD2400 Game project
\date           26/10/2022
\brief
This file contains defination for functions used in a scene
****************************************************************************/
#include "thpch.h"
#include "Scene.h"

namespace Thomas
{
	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity newentity = factory.CreateEmptyComposition();
		TagComponent newtag = name;
		factory.AddComponent<TagComponent>(newentity, newtag);
		return newentity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
	}

}
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
#include "Thomas/Scene/Components.h"
#include "Thomas/Scene/Entity.h"
//#include ""

namespace Thomas
{

	Scene::Scene()
	{
		m_Registry = std::make_shared<GameObjectFactory>();
	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry->CreateEmptyComposition() ,this };
		entity.AddComponent<Transform>();
		auto& Tag = entity.AddComponent<TagComponent>();
		Tag.tag = name.empty() ? "Entity" : name;
		return entity;
	}


	void Scene::OnUpdate(Timestep ts)
	{
		std::map<EntityID, Signature> group = m_Registry->GetEntities();
		//for the map bullshit , iterate through and get all those that has component <T> and do render
		for (auto entity : group)
		{
			if (m_Registry->HasComponent<Transform>(entity.first))
			{
				//zhixiong renderer submit mesh component and transform component to render
			}
		}


	}

	//void Scene::OnViewportResize(uint32_t width, uint32_t height)
	//{
	//}

}
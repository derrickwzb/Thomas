/*!*************************************************************************
\file           Scene.cpp
\author         Derrick Woo
\par DP email:  d.woo@digipen.edu
\par Programming CSD2400 Game project
\date           26/10/2022
\brief
This file contains defination for functions used in a scene
****************************************************************************/
#include "thpch.h"
#include "Scene.h"
#include "Thomas/Scene/Components.h"
#include "Thomas/Renderer/Texture_system.h"
#include "Thomas/Renderer/Texture.h"
#include "Thomas/Renderer/Transform.h"
#include "Thomas/Renderer/Mesh_manager.h"
#include "Thomas/Scene/Entity.h"
#include "Thomas/Audio/AudioEngine.h"
#include "Platform/Windows/WindowsInput.h"
#include "Thomas/Core/KeyCodes.h"
#include "Thomas/Renderer/Graphics.h"
#include "Thomas/Renderer/Asset_Manager.h"
#include "Thomas/Physics/physicsSystem.h"
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

	Entity& Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry->CreateEmptyComposition() ,this };

		// TRANSFORM Component
		auto& trans = entity.AddComponent<Transform>();
		trans.scaling.x = 1.0f;
		trans.scaling.y = 1.0f;
		trans.compute_mdl_to_ndc_xform();

		// SHADER Component
		auto& shader = entity.AddComponent<Shader_manager>();
		shader.setup_shdr_pgm(stash.Shader_Storage.find("engine.vert")->second, stash.Shader_Storage.find("engine.frag")->second);

		// MESH Component
		auto& mesh = entity.AddComponent<Mesh>();
		mesh.setup_vao();

		// TAG Component
		auto& Tag = entity.AddComponent<TagComponent>();
		Tag.tag = name.empty() ? "Entity" : name;

		// BOX RENDERER Component
		auto& box = entity.AddComponent<Box_collider>();
		box.box_tog = 1; // 1 to show the box
		box.box_trans.scaling.x = 1.0f;
		box.box_trans.scaling.y = 1.0f;
		box.box_trans.compute_mdl_to_ndc_xform();
		box.box_trans.minmax_global();
		box.box_mesh.setup_vao();
		box.box_shader.setup_shdr_pgm(stash.Shader_Storage.find("collider.vert")->second, stash.Shader_Storage.find("collider.frag")->second);

		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry->Destroy(entity.GetID());
	}
	

	void Scene::OnUpdate(Timestep ts)
	{
		std::map<EntityID, Signature> group = m_Registry->GetEntities();

		physicsSystem.Update(this, ts);

		for (auto e : group)
		{
			if (m_Registry->HasComponent<Mesh>(e.first))
			{
				//TH_CORE_INFO("entered");
				Entity entity = { e.first,this };
				auto& mesh_data = entity.GetComponent<Mesh>();
				auto& trans_data = entity.GetComponent<Transform>();
				auto& shader_data = entity.GetComponent<Shader_manager>();
				auto color = glm::vec3(0, 0, 0);
				trans_data.compute_mdl_to_ndc_xform();
				trans_data.minmax_global();

				// If have TEXTURE component use another draw call
				if (m_Registry->HasComponent<Texture>(e.first)) {
					auto& text_data = entity.GetComponent<Texture>();
					// Animation button check
					if (text_data.animation_but == 1) {
						text_data.speed = 10;
						text_sys.animation(11, &text_data.counter, text_data.speed, &text_data.switch_text, mesh_data.vbo_hdl);
					}
					Graphics::draw(shader_data, mesh_data, trans_data, text_data, color);
				}
				else {
					Graphics::draw(shader_data, mesh_data, trans_data, color);
				}

				// If have BOX_COLLIDER component, update collider transform matrix and  use another draw call
				if (m_Registry->HasComponent<Box_collider>(e.first)) {
					auto& box = entity.GetComponent<Box_collider>();
					box.box_trans.compute_mdl_to_ndc_xform();
					box.box_trans.minmax_global();
					auto color_on = glm::vec3(1, 0, 0);
					auto color_off = glm::vec3(0, 1, 0);
					Graphics::draw_box(box);
				}
			}

			if (m_Registry->HasComponent<RigidBody>(e.first))
			{
				if (!(m_Registry->HasComponent<BoxCollider2D>(e.first)))
				{
					Entity entity{ e.first, this };
					entity.AddComponent< BoxCollider2D>();
				}
			}

		}

		for (auto e : group)
		{
			if (m_Registry->HasComponent<BulletComponent>(e.first)) {

				Entity entity = { e.first,this };

				auto& bullet_data = entity.GetComponent<BulletComponent>();
				auto& trans_data = entity.GetComponent<Transform>();
				bullet_data.time -= ts;
				trans_data.translation.x += bullet_data.dir.x * ts;
				trans_data.translation.y += bullet_data.dir.y * ts;

				if (bullet_data.time <= 0.f) {
					m_Registry->Destroy(entity);
				}
			}
		}

	}

	std::shared_ptr<GameObjectFactory> Scene::GetRegistry()
	{
		return m_Registry;
	}

}
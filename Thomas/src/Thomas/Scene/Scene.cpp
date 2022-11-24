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

		// TRANSFORM
		auto& trans = entity.AddComponent<Transform>();
		trans.scaling.x = 1.0f;
		trans.scaling.y = 1.0f;
		trans.compute_mdl_to_ndc_xform();

		// SHADER
		auto& shader = entity.AddComponent<Shader_manager>();
		shader.setup_shdr_pgm(stash.Shader_Storage.find("engine.vert")->second, stash.Shader_Storage.find("engine.frag")->second);

		// MESH
		auto& mesh = entity.AddComponent<Mesh>();
		mesh.setup_vao();

		//auto& text = entity.AddComponent<Texture>();
		//text.text_file = 1; 
		///*text.texid = stash.Text_Storage["wallpaper.png"];*/

		auto& Tag = entity.AddComponent<TagComponent>();
		Tag.tag = name.empty() ? "Entity" : name;

		// BOX RENDERER
		auto& box = entity.AddComponent<Box_collider>();
		box.box_tog = 1; // 1 to show the box
		box.box_trans.scaling.x = 1.0f;
		box.box_trans.scaling.y = 1.0f;
		box.box_trans.compute_mdl_to_ndc_xform();
		box.box_trans.minmax_global();
		box.box_mesh.setup_vao();
		box.box_shader.setup_shdr_pgm(stash.Shader_Storage.find("collider.vert")->second, stash.Shader_Storage.find("collider.frag")->second);

		//todo: initialization of box collider
		//how does the box collider update
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
				if (m_Registry->HasComponent<Texture>(e.first)) {
					auto& text_data = entity.GetComponent<Texture>();
					Graphics::draw(shader_data, mesh_data, trans_data, text_data, color);
				}
				else {
					Graphics::draw(shader_data, mesh_data, trans_data, color);
				}
				if (m_Registry->HasComponent<Box_collider>(e.first)) {
					auto& box = entity.GetComponent<Box_collider>();
					box.box_trans.compute_mdl_to_ndc_xform();
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

			/*if (Thomas::factory.HasComponent<Box_collider>(entity)) {
				auto trans_data = Thomas::factory.GetComponent<Transform>(entity);
				auto box_data = Thomas::factory.GetComponent<Box_collider>(entity);

					box_data.box_trans.minmax(width, height);
					box_data.box_trans.rotation = trans_data.rotation;
					box_data.box_trans.compute_mdl_to_ndc_xform();
					box_data.box_trans.mdl_to_ndc_xform = cam_stuff.world_to_ndc_xform * box_data.box_trans.mdl_to_ndc_xform;

					if (box_data.reset_but == 1) {
						box_data.box_trans.translation = trans_data.translation;
						box_data.box_trans.scaling = trans_data.scaling;
						box_data.reset_but = 0;
					}

				Thomas::factory.UpdateComponent<Box_collider>(entity, box_data);
			}*/
			

			////AudioSystem::Update()S
			//if (m_Registry->HasComponent<AudioComponent>(e.first)) {

			//	auto& getAudio = m_Registry->GetComponent<AudioComponent>(e.first);
			//	//playing a sound
			//	getAudio.filepath = stash.Audio_Storage["boss.wav"];
			//	getAudio.fVolumedB = 10.0;
			//	getAudio.nChannelId = AEngine.PlaySound(getAudio.filepath, getAudio.fVolumedB);
			//	//m_Registry->UpdateComponent<Thomas::AudioComponent>(e.first, getAudio);//Updates data for component
			//}

			////AudioSystem::TempSfxInput()
			//if (m_Registry->HasComponent<AudioComponent>(e.first)) {

			//	if (Input::IsKeyPressed(TH_KEY_M)) {

			//		auto getAudio = m_Registry->GetComponent<AudioComponent>(e.first);
			//		CAudioEngine AEngine;
			//		//playing a sound
			//		getAudio.filepath = stash.Audio_Storage["death.mp3"];
			//		getAudio.fVolumedB = 10.0;
			//		getAudio.nChannelId = AEngine.PlaySfxSound(getAudio.filepath, getAudio.fVolumedB);
			//		//m_Registry->UpdateComponent<AudioComponent>(e.first, getAudio);//Updates data for component
			//	}
			//}

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

	//void Scene::OnViewportResize(uint32_t width, uint32_t height)
	//{
	//}

}
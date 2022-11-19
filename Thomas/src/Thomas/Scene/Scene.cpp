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
		auto& trans = entity.AddComponent<Transform>();
		trans.scaling.x = 1.0f;
		trans.scaling.y = 1.0f;
		trans.compute_mdl_to_ndc_xform();

		//entity.AddComponent<Texture>();

		auto& shader = entity.AddComponent<Shader_manager>();
		shader.setup_shdr_pgm(stash.Shader_Storage.find("engine.vert")->second, stash.Shader_Storage.find("engine.frag")->second);

		auto& mesh = entity.AddComponent<Mesh>();
		mesh.setup_vao();

		auto& Tag = entity.AddComponent<TagComponent>();
		Tag.tag = name.empty() ? "Entity" : name;

		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry->Destroy(entity.GetID());
	}


	void Scene::OnUpdate(Timestep ts)
	{
		std::map<EntityID, Signature> group = m_Registry->GetEntities();

		//for the map bullshit , iterate through and get all those that has component <T> and do render
		// sample for update from graphics (just took 1)
		for (auto e : group)
		{
			if (m_Registry->HasComponent<Mesh>(e.first))
			{
				//TH_CORE_INFO("entered");
				Entity entity = { e.first,this };
				//auto tex_data = entity.GetComponent<Texture>();
				auto& mesh_data = entity.GetComponent<Mesh>();
				auto& trans_data = entity.GetComponent<Transform>();
				auto& shader_data = entity.GetComponent<Shader_manager>();

				/*if (tex_data.text_file == 1) {
					tex_data.texid = stash.Text_Storage["bigboss.png"];
				}
				else if (tex_data.text_file == 2) {
					tex_data.texid = stash.Text_Storage["background.png"];
				}
				else if (tex_data.text_file == 3) {
					tex_data.texid = stash.Text_Storage["sprite.png"];
				}
				if (tex_data.animation_but == 1) {
					tex_data.speed = 10;
					text_sys.animation(11, &tex_data.counter, tex_data.speed, &tex_data.switch_text, mesh_data.vbo_hdl);
				}*/
				/*Graphics::cam_stuff.Camera2D_Update(Graphics::cam_stuff.vp_width, Graphics::cam_stuff.vp_height);*/
				auto color = glm::vec3(0, 0, 0);
				//auto tag = m_Registry->GetComponent<TagComponent>(e.first).tag;
				/*TH_CORE_INFO("{0}", entity.GetComponent<Transform>().translation.x);*/
				/*std::cout << trans_data.translation.x << std::endl;*/
				trans_data.compute_mdl_to_ndc_xform();
				Graphics::draw(shader_data, mesh_data, trans_data, color);
			}

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




	}

	//void Scene::OnViewportResize(uint32_t width, uint32_t height)
	//{
	//}

}
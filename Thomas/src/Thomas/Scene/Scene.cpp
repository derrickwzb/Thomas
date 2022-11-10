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
#include "Thomas/Audio/AudioEngine.h"
#include "Platform/Windows/WindowsInput.h"
#include "Thomas/Core/KeyCodes.h"
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
		// sample for update from graphics (just took 1)
		for (auto e : group)
		{
			if (m_Registry->HasComponent<Texture>(e.first))
			{
				Entity entity = { e.first,this };
				auto tex_data = entity.GetComponent<Texture>();
				auto mesh_data = entity.GetComponent<Mesh>();
				auto trans_data = entity.GetComponent<Transform>();

				if (tex_data.text_file == 1) {
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
				}
				//auto tag = m_Registry->GetComponent<TagComponent>(e.first).tag;
				//TH_CORE_INFO("{0}", tag);
			}

			//AudioSystem::Update()
			if (m_Registry->HasComponent<AudioComponent>(e.first)) {

				auto& getAudio = m_Registry->GetComponent<AudioComponent>(e.first);
				//playing a sound
				getAudio.filepath = stash.Audio_Storage["boss.wav"];
				getAudio.fVolumedB = 10.0;
				getAudio.nChannelId = AEngine.PlaySound(getAudio.filepath, getAudio.fVolumedB);
				//m_Registry->UpdateComponent<Thomas::AudioComponent>(e.first, getAudio);//Updates data for component
			}

			//AudioSystem::TempSfxInput()
			if (m_Registry->HasComponent<AudioComponent>(e.first)) {

				if (Input::IsKeyPressed(TH_KEY_M)) {

					auto getAudio = m_Registry->GetComponent<AudioComponent>(e.first);
					CAudioEngine AEngine;
					//playing a sound
					getAudio.filepath = stash.Audio_Storage["death.mp3"];
					getAudio.fVolumedB = 10.0;
					getAudio.nChannelId = AEngine.PlaySfxSound(getAudio.filepath, getAudio.fVolumedB);
					//m_Registry->UpdateComponent<AudioComponent>(e.first, getAudio);//Updates data for component
				}
			}


		}




	}

	//void Scene::OnViewportResize(uint32_t width, uint32_t height)
	//{
	//}

}
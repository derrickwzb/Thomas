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

		auto& trans = entity.AddComponent<Transform>();
		trans.scaling.x = 1.0f;
		trans.scaling.y = 1.0f;
		trans.compute_mdl_to_ndc_xform();

		auto& shader = entity.AddComponent<Shader_manager>();
		shader.setup_shdr_pgm(stash.Shader_Storage.find("engine.vert")->second, stash.Shader_Storage.find("engine.frag")->second);

		auto& mesh = entity.AddComponent<Mesh>();
		mesh.setup_vao();

		auto& text = entity.AddComponent<Texture>();
		text.text_file = 1; 
		text.texid = stash.Text_Storage["wallpaper.png"];

		auto& Tag = entity.AddComponent<TagComponent>();
		Tag.tag = name.empty() ? "Entity" : name;

		auto& box = entity.AddComponent<Box_collider>();
		//todo: initialization of box collider
		//how does the box collider update



		// auto& box_collider = entity.AddComponent<Box_collider>();
		// box_collider.box_trans.scaling.x = 1.0f;
		// box_collider.box_trans.scaling.y = 1.0f;
		// box_collider.box_trans.compute_mdl_to_ndc_xform();
		// box_collider.box_shader.setup_shdr_pgm(stash.Shader_Storage.find("engine.vert")->second, 
		// 									   stash.Shader_Storage.find("engine.frag")->second);
		// box_collider.box_mesh.setup_vao();

		// auto& rigid = entity.AddComponent<RigidBody>();

		// auto& box_collider_2D = entity.AddComponent<BoxCollider2D>();

		// box_collider_2D.bounds.min.x = 0.f;
		// box_collider_2D.bounds.min.y = 0.f;
		// box_collider_2D.bounds.max.x = 0.f;
		// box_collider_2D.bounds.max.y = 0.f;

		// std::array<float, 2> temp_vertices;
		// std::array<std::array<float, 2>, 4> temp_result;
		// //const rapidjson::Value& bvertice = component["Vertices"];

		// for (int i = 0; i < 4; ++i) {
		// 	//const rapidjson::Value& bvertice_pos = bvertice[i];
		// 	temp_vertices[0] = 0.f;
		// 	temp_vertices[1] = 0.f;
		// 	temp_result[i] = temp_vertices;
		// }

		// box_collider_2D.vertices = temp_result;
		// box_collider_2D.ArrayToVector();

		// entity.GetComponent<Box_collider>().reset_but = 1;
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
				auto color = glm::vec3(0, 0, 0);
				trans_data.compute_mdl_to_ndc_xform();
				if (m_Registry->HasComponent<Texture>(e.first)) {
					auto& text_data = entity.GetComponent<Texture>();
					Graphics::draw(shader_data, mesh_data, trans_data, text_data, color);
				}
				else {
					Graphics::draw(shader_data, mesh_data, trans_data, color);
				}
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
				/*Graphics::cam_stuff.Camera2D_Update(Graphics::cam_stuff.vp_width, Graphics::cam_stuff.vp_height
				//auto tag = m_Registry->GetComponent<TagComponent>(e.first).tag;
				/*TH_CORE_INFO("{0}", entity.GetComponent<Transform>().translation.x);*/
				/*std::cout << trans_data.translation.x << std::endl;*/	
			}

			//physicsSystem.Update(this, ts);

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

        for (auto e : group) {

            //Static rect to rect collision
            if (m_Registry->HasComponent<BoxCollider2D>(e.first)) {

                //TH_CORE_INFO("entered");
                Entity entity = { e.first,this };
                //auto tex_data = entity.GetComponent<Texture>();
                auto& box_data = entity.GetComponent<BoxCollider2D>();
                auto& rigid_data = entity.GetComponent<RigidBody>();
                auto& trans_data = entity.GetComponent<Transform>();
                auto& bounding_box_data = entity.GetComponent<Box_collider>();

                box_data.verticesList[0] = Vec2{ bounding_box_data.box_trans.vertice0.x , bounding_box_data.box_trans.vertice0.y };
                box_data.verticesList[1] = Vec2{ bounding_box_data.box_trans.vertice1.x , bounding_box_data.box_trans.vertice1.y };
                box_data.verticesList[2] = Vec2{ bounding_box_data.box_trans.vertice2.x , bounding_box_data.box_trans.vertice2.y };
                box_data.verticesList[3] = Vec2{ bounding_box_data.box_trans.vertice3.x , bounding_box_data.box_trans.vertice3.y };

                for (auto e2 : group) {

                    if (e != e2) {

                        if (m_Registry->HasComponent<BoxCollider2D>(e2.first)) {

							Entity entity2 = { e2.first,this };
							auto& box_data2 = entity2.GetComponent<BoxCollider2D>();
							auto& rigid_data2 = entity2.GetComponent<RigidBody>();
							auto& trans_data2 = entity2.GetComponent<Transform>();
							auto& bounding_box_data2 = entity2.GetComponent<Box_collider>();

							box_data2.verticesList[0] = Vec2{ bounding_box_data2.box_trans.vertice0.x , bounding_box_data2.box_trans.vertice0.y };
							box_data2.verticesList[1] = Vec2{ bounding_box_data2.box_trans.vertice1.x , bounding_box_data2.box_trans.vertice1.y };
							box_data2.verticesList[2] = Vec2{ bounding_box_data2.box_trans.vertice2.x , bounding_box_data2.box_trans.vertice2.y };
							box_data2.verticesList[3] = Vec2{ bounding_box_data2.box_trans.vertice3.x , bounding_box_data2.box_trans.vertice3.y };


                            Vec2 normal;
                            float depth;
                            if (Thomas::SATPolygonIntersection(box_data.verticesList, box_data2.verticesList, normal, depth))
                            {
								bounding_box_data.collision_detected = 1;
								bounding_box_data2.collision_detected = 1;

                                glm::vec2 diff_1, diff_2;
                                diff_1 = glm::vec2(trans_data.translation.x - bounding_box_data.box_trans.translation.x, trans_data.translation.y - bounding_box_data.box_trans.translation.y);
                                diff_2 = glm::vec2(trans_data2.translation.x - bounding_box_data2.box_trans.translation.x, trans_data2.translation.y - bounding_box_data2.box_trans.translation.y);

								rigid_data.m_Position.x = bounding_box_data.box_trans.translation.x;
								rigid_data.m_Position.y = bounding_box_data.box_trans.translation.y;

                                physicsSystem.addForce(rigid_data, depth / 2.f, ts);
								rigid_data.m_Position += -normal * ts;

								bounding_box_data.box_trans.translation.x = rigid_data.m_Position.x;
								bounding_box_data.box_trans.translation.y = rigid_data.m_Position.y;

								trans_data.translation.x = (rigid_data.m_Position.x + diff_1.x);
								trans_data.translation.y = (rigid_data.m_Position.y + diff_1.y);

								rigid_data2.m_Position.x = bounding_box_data2.box_trans.translation.x;
								rigid_data2.m_Position.y = bounding_box_data2.box_trans.translation.y;

                                physicsSystem.addForce(rigid_data2, depth / 2.f, ts);
								rigid_data2.m_Position += normal * ts;

								bounding_box_data2.box_trans.translation.x = rigid_data2.m_Position.x;
								bounding_box_data2.box_trans.translation.y = rigid_data2.m_Position.y;


								trans_data2.translation.x = bounding_box_data2.box_trans.translation.x + diff_2.x;
								trans_data2.translation.y = bounding_box_data2.box_trans.translation.y + diff_2.y;
                            }
                            else {
								bounding_box_data.collision_detected = 0;
								bounding_box_data2.collision_detected = 0;
                            }
                        }
                    }
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
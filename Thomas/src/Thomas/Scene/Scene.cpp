/*!*************************************************************************
\file           Scene.cpp
\author         Derrick Woo
\par DP email:  d.woo@digipen.edu
\par Programming CSD2400 Game project
\date           26/10/2022
\brief
This file contains defination for functions used in a scene
****************************************************************************/
#pragma warning( disable : 4172 )
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
#include "Thomas/Physics/Random.h"
#include "Thomas/Scripting/ScriptEngine.h"
#include "Thomas/Renderer/Fonts.h"

namespace Thomas
{

	Scene::Scene()
	{
		m_Registry = std::make_shared<GameObjectFactory>();
		Graphics::init();
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
		trans.z_axis = 0.f;
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

	Entity& Scene::CreatePlayerEntity() {
		Entity entity = this->CreateEntity("Player");

		auto& object_type = entity.AddComponent<ObjectType>();
		object_type.type = ObjectTypeID::player;

		auto& combat = entity.AddComponent<CombatComponent>();
		combat.attack = 1;
		combat.health = 10;

		auto& tex = entity.AddComponent<Texture>();
		tex.texid = stash.Text_Storage["Chef_Kay_Top.png"];
		tex.text_file = 36;
		tex.filename = "Chef_Kay_Top.png";

		auto& box = entity.GetComponent<Box_collider>();
		auto& boxCollider = entity.AddComponent<BoxCollider2D>();
		auto& data = entity.AddComponent<RigidBody>();
		boxCollider.verticesList.push_back(box.box_trans.global_vertice0);
		boxCollider.verticesList.push_back(box.box_trans.global_vertice1);
		boxCollider.verticesList.push_back(box.box_trans.global_vertice2);
		boxCollider.verticesList.push_back(box.box_trans.global_vertice3);

		//tex.filename = "../Assets/textures/Chef_Kay_Top.png";
		return entity;
	}

	Entity& Scene::CreateEnemyEntity() {
		Entity entity = { m_Registry->CreateEmptyComposition() ,this };
		/*Entity entity = this->CreateEntity("Enemy");*/
		auto& Tag = entity.AddComponent<TagComponent>();
		Tag.tag = "Enemy";

		auto& object_type = entity.AddComponent<ObjectType>();
		object_type.type = ObjectTypeID::enemy;

		auto& combat = entity.AddComponent<CombatComponent>();
		combat.attack = 1;
		combat.attack_interval = 0.5f;
		combat.health = 5;

		auto& tex = entity.AddComponent<Texture>();
		tex.texid = stash.Text_Storage["Raccoon_Waiter_Top.png"];
		tex.text_file = 124;
		tex.filename = "Raccoon_Waiter_Top.png";

		auto& box = entity.GetComponent<Box_collider>();
		auto& boxCollider = entity.AddComponent<BoxCollider2D>();
		auto& data = entity.AddComponent<RigidBody>();
		boxCollider.verticesList.push_back(box.box_trans.global_vertice0);
		boxCollider.verticesList.push_back(box.box_trans.global_vertice1);
		boxCollider.verticesList.push_back(box.box_trans.global_vertice2);
		boxCollider.verticesList.push_back(box.box_trans.global_vertice3);

		//auto& astar_agent = entity.AddComponent<AStarPathfindingAgent>();

		return entity;
	}

	Entity& Scene::CreateObstacleEntity() {
		//Entity entity = this->CreateEntity("Obstacle");


		Entity entity = { m_Registry->CreateEmptyComposition() ,this };
		/*Entity entity = this->CreateEntity("Enemy");*/
		auto& Tag = entity.AddComponent<TagComponent>();
		Tag.tag = "Obstacle";

		auto& object_type = entity.AddComponent<ObjectType>();
		object_type.type = ObjectTypeID::obstacle;

		auto& tex = entity.AddComponent<Texture>();
		tex.texid = 1;

		auto& box = entity.GetComponent<Box_collider>();
		auto& boxCollider = entity.AddComponent<BoxCollider2D>();
		auto& data = entity.AddComponent<RigidBody>();
		boxCollider.verticesList.push_back(box.box_trans.global_vertice0);
		boxCollider.verticesList.push_back(box.box_trans.global_vertice1);
		boxCollider.verticesList.push_back(box.box_trans.global_vertice2);
		boxCollider.verticesList.push_back(box.box_trans.global_vertice3);

		//auto& a = entity.AddComponent<AStarPathfindingObstacle>();

		return entity;
	}

	Entity& Scene::CloneEntity(Entity entity) {
		Entity newentity = { m_Registry->Clone(entity) ,this };
		return newentity;
	}

	/*
	Entity& Scene::GetEntityByID(Entity entityID)
	{
		Entity entityID = EntityGetID();
	}*/

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry->Destroy(entity.GetID());
	}
	
	void Scene::OnRuntimeStart()
	{
		ScriptEngine::OnRuntimeStart(this);

		//Instantiate all script entities

		std::map<EntityID, Signature> group = m_Registry->GetEntities();

		for (auto e : group)
		{
			if (m_Registry->HasComponent<ScriptComponent>(e.first))
			{
				Entity entity = { e.first,this };
				const auto& sc = entity.GetComponent<ScriptComponent>();
				ScriptEngine::OnCreateEntity(entity);
			}
		}

	}

	void Scene::OnRuntimeStop()
	{
		ScriptEngine::OnRuntimeStop();
	}

	void Scene::OnUpdate(Timestep ts)
	{
		std::map<EntityID, Signature> group = m_Registry->GetEntities();

		for (auto e : group)
		{
			// This is the one that is checking for the serialised object
			//C# Entity OnUpdate
			if (m_Registry->HasComponent<ScriptComponent>(e.first))
			{
				Entity entity = { e.first,this };
				ScriptEngine::OnCreateEntity(entity);
				ScriptEngine::OnUpdateEntity(entity, ts);
			}

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
						text_sys.animation(text_data, mesh_data.vbo_hdl);
					}
					Graphics::draw(shader_data, mesh_data, trans_data, text_data);
				}
				else {
					Graphics::draw(shader_data, mesh_data, trans_data);
				}

				// If have BOX_COLLIDER component, update collider transform matrix and  use another draw call
				if (m_Registry->HasComponent<Box_collider>(e.first)) {
					auto& box = entity.GetComponent<Box_collider>();
					box.box_trans.compute_mdl_to_ndc_xform();
					box.box_trans.minmax_global();
					box.box_trans.z_axis = trans_data.z_axis;
					auto color_on = glm::vec3(1, 0, 0);
					auto color_off = glm::vec3(0, 1, 0);
					Graphics::draw_box(box);
				}

				if (m_Registry->HasComponent<Fonts>(e.first)) {
					auto& font = entity.GetComponent<Fonts>();
					glm::vec2 fonts_coords = trans_data.screen_to_world(trans_data.translation);
					std::cout << fonts_coords.x << "       " << fonts_coords.y << std::endl;
					font.RenderText("HELLO", fonts_coords.x, fonts_coords.y, 2.f, trans_data.z_axis, glm::vec3(1,1,0));
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
				auto& box_data = entity.GetComponent<Box_collider>();
				
				bullet_data.time -= ts;
				trans_data.translation.x += bullet_data.dir.x * ts;
				trans_data.translation.y += bullet_data.dir.y * ts;
				box_data.box_trans.translation.x += bullet_data.dir.x * ts;
				box_data.box_trans.translation.y += bullet_data.dir.y * ts;

				if (bullet_data.time <= 0.f) {
					m_Registry->Destroy(entity);
					//this->GetRegistry()->Destroy(entity);
				}
			}
		}

		for (auto e : group)
		{
			if (m_Registry->HasComponent<ParticleComponent>(e.first)) {
				Entity entity = { e.first,this };
				auto& trans_data = entity.GetComponent<Transform>();
				//auto& particleComponent_data = entity.GetComponent<ParticleComponent>();

				//particleComponent_data.time -= ts;

				//if (particleComponent_data.time <= 0.f)
				//{
					Entity particle = Scene::CreateEntity("particle");
					auto& particle_trans_data = particle.GetComponent<Transform>();
					auto& box = particle.GetComponent<Box_collider>();

					particle_trans_data.translation.x = trans_data.translation.x;
					particle_trans_data.translation.y = trans_data.translation.y;
					particle_trans_data.scaling.x = 0.2f;
					particle_trans_data.scaling.y = 0.2f;

					box.box_tog = 0; // 1 to show the box

					auto& particle_data = particle.AddComponent<Particle>();
					//auto& particle_data = particle.GetComponent<Particle>();

					particle_data.total_time = 1.f;
					particle_data.life_time = particle_data.total_time;

					//particleComponent_data.time = 0.05f;
				//}
			}
		}

		for (auto e : group)
		{
			if (m_Registry->HasComponent<Particle>(e.first)) {

				Entity entity = { e.first,this };

				auto& particle_data = entity.GetComponent<Particle>();
				auto& trans_data = entity.GetComponent<Transform>();
				particle_data.life_time -= ts;
				//trans_data.translation.x += particle_data.dir.x * ts;
				//trans_data.translation.y += particle_data.dir.y * ts;
				trans_data.translation.x += (Random::Float() * 2.f) * static_cast<float>(ts);
				trans_data.translation.y += (Random::Float() * 2.f) * static_cast<float>(ts);
				trans_data.rotation += (Random::Float()) * (180 / 3.1415926f) * 0.2f;
				trans_data.scaling.x = 0.2f * (particle_data.life_time / particle_data.total_time);
				trans_data.scaling.y = 0.2f * (particle_data.life_time / particle_data.total_time);

				if (particle_data.life_time <= 0.f) {
					m_Registry->Destroy(entity);
				}
			}
		}

	

		//gridSystem.
		aStarSystem.Update(this, ts);
		physicsSystem.Update(this, ts);
		//std::cout << "Scene Function: " << &aStarSystem.grid << std::endl;


		//if (aStarSystem.grid != nullptr)
		//{
		//	std::cout << "Scene Serializer grid not null";
		//	//auto& gridData = entity2.GetComponent<Grid>();
		//	gridSystem.AddObstacleToGrid(*aStarSystem.grid, e);


		//}
		

		//gridSystem.Update(this);

		//physicsSystem.ClickButton(this);
	}

	std::shared_ptr<GameObjectFactory> Scene::GetRegistry()
	{
		return m_Registry;
	}

	Scene* Scene::GetScene() {
		return this;
	}

}
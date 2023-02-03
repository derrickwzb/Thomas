/******************************************************************************/
/*!
\file		SceneHierarchyPanel.h
\author 	Derrick Woo
\par    	email: d.woo@digipen.edu
\date   	2/11/2022
\brief		This file contains the definitions of member function of the object SceneHierarchyPanel.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "SceneHierarchyPanel.h"
#include "ImGui/imgui.h"
#include "Thomas/Scene/Components.h"
#include "Thomas/Scripting/ScriptEngine.h"
#include "Thomas/Renderer/Texture_system.h"

#include "Thomas/Renderer/Graphics.h"

namespace Thomas
{
	extern const std::filesystem::path s_AssetsPath;

	SceneHierarchyPanel::SceneHierarchyPanel(const std::shared_ptr<Scene>& context)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(const std::shared_ptr<Scene>& context)
	{
		m_Context = context;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		const auto& entities = m_Context->m_Registry->GetEntities();

		for (const auto& e : entities)
		{
			//TH_CORE_INFO("{0}", e.first);
			Entity entity{ e.first , m_Context.get() };
			//TH_CORE_INFO("{0}", e.first);
			DrawEntityNode(entity);

		}
		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_SelectionContext = {};

		//right click on a blank space
		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem("Create New Entity"))
			{
				m_Context->CreateEntity("Empty Entity");
			}
			if (ImGui::MenuItem("Create Player Entity"))
			{
				m_Context->CreatePlayerEntity();
			}
			if (ImGui::MenuItem("Create Enemy Entity"))
			{
				m_Context->CreateEnemyEntity();
			}
			if (ImGui::MenuItem("Create Obstacle Entity"))
			{
				m_Context->CreateObstacleEntity();
			}

			ImGui::EndPopup();
		}


		ImGui::End();

		ImGui::Begin("Inspector");
		if (m_SelectionContext)
		{
			DrawComponents(m_SelectionContext);
			//TH_CORE_INFO("{0}", m_SelectionContext.GetComponent<TagComponent>().tag);
			if (ImGui::Button("Add Component"))
			{
				ImGui::OpenPopup("AddComponent");
			}
			if (ImGui::BeginPopup("AddComponent"))
			{
				if (ImGui::MenuItem("Audio Component"))
				{
					m_SelectionContext.AddComponent<AudioComponent>();
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("Texture Component"))
				{
					auto& data = m_SelectionContext.AddComponent<Texture>();
					data.texid = 1;
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("Box Collider 2D"))
				{
					auto& box = m_SelectionContext.GetComponent<Box_collider>();
					auto& boxCollider = m_SelectionContext.AddComponent<BoxCollider2D>();
					auto& data = m_SelectionContext.AddComponent<RigidBody>();
					boxCollider.verticesList.push_back(box.box_trans.global_vertice0);
					boxCollider.verticesList.push_back(box.box_trans.global_vertice1);
					boxCollider.verticesList.push_back(box.box_trans.global_vertice2);
					boxCollider.verticesList.push_back(box.box_trans.global_vertice3);

					ImGui::CloseCurrentPopup();
				}

				if (ImGui::MenuItem("Particle Component"))
				{
					//auto& data = m_SelectionContext.AddComponent<ParticleComponent>();
					//data.time = 0.05f;
					m_SelectionContext.AddComponent<ParticleComponent>();
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("Object Type"))
				{
					m_SelectionContext.AddComponent<ObjectType>();
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("Combat Component"))
				{
					m_SelectionContext.AddComponent<CombatComponent>();
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("Font Component"))
				{
					m_SelectionContext.AddComponent<Fonts>();
					auto& fontData = m_SelectionContext.GetComponent<Fonts>();
					fontData.font_type = stash.Font_Storage["Freedom-10eM.ttf"];
					fontData.Fonts_init();
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("Script Component"))
				{
					m_SelectionContext.AddComponent<ScriptComponent>();
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::MenuItem("Grid Component"))
				{
					m_SelectionContext.AddComponent<Grid>();
					//aStarSystem.gridExist = true;

					auto& gridData = m_SelectionContext.GetComponent<Grid>();
					aStarSystem.grid = &gridData;
					//std::cout << aStarSystem.grid << std::endl;
					auto& transformData = m_SelectionContext.GetComponent<Transform>();

					gridData.gridWorldSize = Vec2(transformData.scaling);
					gridData.nodeRadius = 0.5f;
					gridData.origin = { transformData.translation.x - (gridData.gridWorldSize.x / 2),
										transformData.translation.y - (gridData.gridWorldSize.y / 2) };

					gridSystem.SetGridParameters(gridData, gridData.gridWorldSize ,gridData.nodeRadius);

					gridSystem.ClearGrid(gridData);
					gridSystem.CreateGrid(gridData);
					gridSystem.AddNeighboursToGrid(gridData);


					std::cout << "Origin: (" << gridData.origin.x << "," << gridData.origin.y << ")\n";

					ImGui::CloseCurrentPopup();
				}

				
				if (ImGui::MenuItem("AStarPathfindingObstacle Component"))
				{
					m_SelectionContext.AddComponent<AStarPathfindingObstacle>();
					auto& obstacleData = m_SelectionContext.GetComponent<AStarPathfindingObstacle>();
					auto& boxTransformData = m_SelectionContext.GetComponent<Box_collider>();
					obstacleData.position = Vec2(boxTransformData.box_trans.translation);
					obstacleData.size = Vec2(boxTransformData.box_trans.scaling);

					obstacleData.ID = m_SelectionContext.GetID();

					std::cout << "Obstacle ID: " << obstacleData.ID << "\n";
					if (aStarSystem.grid != nullptr)
					{
						
						gridSystem.AddObstacleToGrid(*aStarSystem.grid, obstacleData);



					}

					//if()
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::MenuItem("AStarPathfindingAgent Component"))
				{
					m_SelectionContext.AddComponent<AStarPathfindingAgent>();
					//auto& agentData = m_SelectionContext.GetComponent<AStarPathfindingAgent>();

					//auto& agentData = m_SelectionContext.GetComponent<AStarPathfindingAgent>();
					//auto& transformData = m_SelectionContext.GetComponent<Transform>();

					ImGui::CloseCurrentPopup();
				}
			
				if (ImGui::MenuItem("Target Component"))
				{
					m_SelectionContext.AddComponent<Target>();
					//auto& targetData = m_SelectionContext.GetComponent<Target>();

					//auto& agentData = m_SelectionContext.GetComponent<AStarPathfindingAgent>();
					//auto& transformData = m_SelectionContext.GetComponent<Transform>();

					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}
		}


		ImGui::End();
		if (m_DeletionContext)
		{
			m_Context->DestroyEntity(m_DeletionContext);
		}
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().tag;

		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
			TH_CORE_INFO("{0}", tag);
		}

		bool entitydeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
			{
				entitydeleted = true;
			}
			if (ImGui::MenuItem("Clone Entity"))
			{
				m_Context->CloneEntity(m_SelectionContext);
			}

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}
		
		if (entitydeleted || m_Context->GetRegistry()->GetComponent<DeleteComponent>(entity).isdeleted == true)
		{
			m_DeletionContext = entity;
			if (m_SelectionContext == entity)
			{
				m_SelectionContext = {};
			}
		}
	}

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		/*auto& tag = entity.GetComponent<TagComponent>().tag;
		TH_CORE_INFO("{0}", tag);*/
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, tag.c_str());
			if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap;

		if (entity.HasComponent<Transform>())
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
			bool open = (ImGui::TreeNodeEx((void*)typeid(Transform).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"));
			ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
			if (ImGui::Button("+", ImVec2{ 20,20 }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}
			ImGui::PopStyleVar();
			bool removecomponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove Component"))
					removecomponent = true;
				ImGui::EndPopup();
			}

			if (open)
			{
				auto& data = entity.GetComponent<Transform>();
				auto& box = entity.GetComponent<Box_collider>();

				ImGui::DragFloat("Position X", &data.translation.x, 0.1f);
				ImGui::DragFloat("Position Y", &data.translation.y, 0.1f);
				ImGui::DragFloat("Scale X", &data.scaling.x, 0.1f);
				ImGui::DragFloat("Scale Y", &data.scaling.y, 0.1f);
				ImGui::DragFloat("Rotation", &data.rotation, 1.f, -360.f, 360.f);
				ImGui::DragFloat("Layer", &data.z_axis, 0.01f, -0.9f, 0.9f);
				ImGui::DragFloat("Blend", &data.alpha_val, 0.01f, 0.f, 1.f);

				if (ImGui::Button("Mouse Following")) {
					if (data.mouse_following != 1)
						data.mouse_following = 1;
					else
						data.mouse_following = 0;
				}
				ImGui::SameLine();

				if (ImGui::Button("Box Resize")) {
					box.box_trans.translation = data.translation;
					box.box_trans.scaling = data.scaling;
					box.box_trans.rotation = data.rotation;
				}
				ImGui::SameLine();

				if (ImGui::RadioButton("Trans Lock", data.transform_Lock)) {
					if (data.transform_Lock != true) data.transform_Lock = true;
					else data.transform_Lock = false;
				}

				float temp_Color[3] = { data.color.x, data.color.y, data.color.z };
				if (ImGui::ColorEdit3("Color", temp_Color)) {
					data.color.x = temp_Color[0];
					data.color.y = temp_Color[1];
					data.color.z = temp_Color[2];
				}
				ImGui::TreePop();
			}

			if (removecomponent)
			{
				entity.RemoveComponent<Transform>();
			}
		}

		if (entity.HasComponent<Texture>())
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
			bool open = (ImGui::TreeNodeEx((void*)typeid(Texture).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Texture"));
			ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
			if (ImGui::Button("+", ImVec2{ 20,20 }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}
			ImGui::PopStyleVar();
			bool removecomponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove Component"))
					removecomponent = true;
				ImGui::EndPopup();
			}

			if (open)
			{
				auto& data = entity.GetComponent<Texture>();
				auto& mesh = entity.GetComponent<Mesh>();
				ImGui::Button("Texture", ImVec2(200.0f, 100.0f));
				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
					{
						const wchar_t* path = (const wchar_t*)payload->Data;
						std::filesystem::path texturePath = std::filesystem::path(s_AssetsPath) / path;
						TH_CORE_INFO("{0}", texturePath.filename().string());

						data.texid = stash.Text_Storage[texturePath.filename().string()];
						data.text_file = stash.Text_Storage[texturePath.filename().string()];
						data.filename = texturePath.filename().string();
						//filename = texturePath.filename().string();
					}
					ImGui::EndDragDropTarget();
				}
				ImGui::Text("Texture loaded : %s\n", data.filename.c_str());
				ImGui::DragFloat("Animation Slices", &data.slices, 1.f, 1.f, 50.f);
				ImGui::DragFloat("Animation speed", &data.speed, 0.1f, 0.f, 20.f);
				if (ImGui::DragFloat("Animation cut", &data.switch_text, 1.f, 0.f, data.max_text)) {
					text_sys.animation_image(data, mesh.vbo_hdl);
				}
				if (ImGui::Button("Animation on", ImVec2(200.0f, 25.0f)))
				{
					data.animation_but = 1;
				}
				if (ImGui::Button("Animation pause", ImVec2(200.0f, 25.0f)))
				{
					data.animation_but = 0;
				}
				if (ImGui::Button("Animation off", ImVec2(200.0f, 25.0f))) {
					text_sys.animation_off(mesh.vbo_hdl);
				}
				ImGui::TreePop();
			}

			if (removecomponent)
			{
				entity.RemoveComponent<Texture>();
			}
		}

		if (entity.HasComponent<BoxCollider2D>())
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
			bool open = (ImGui::TreeNodeEx((void*)typeid(BoxCollider2D).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Box Collider 2D"));
			ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
			if (ImGui::Button("+", ImVec2{ 20,20 }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}
			ImGui::PopStyleVar();
			bool removecomponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove Component"))
					removecomponent = true;
				ImGui::EndPopup();
			}

			if (open)
			{
				auto& data = entity.GetComponent<BoxCollider2D>();
				auto& box = entity.GetComponent<Box_collider>();

				if (ImGui::Button("Box_collider")) {
					if (box.box_tog != 1)
						box.box_tog = 1;
					else
						box.box_tog = 0;
				}

				ImGui::DragFloat("Box Position X", &box.box_trans.translation.x, 0.1f);
				ImGui::DragFloat("Box Position Y", &box.box_trans.translation.y, 0.1f);
				ImGui::DragFloat("Box Scale X", &box.box_trans.scaling.x, 0.1f);
				ImGui::DragFloat("Box Scale Y", &box.box_trans.scaling.y, 0.1f);
				ImGui::DragFloat("Box Rotation", &box.box_trans.rotation, 0.1f, -360.f, 360.f);

				ImGui::TreePop();
			}

			if (removecomponent)
			{
				entity.RemoveComponent<BoxCollider2D>();
				entity.RemoveComponent<RigidBody>();
			}
		}

		if (entity.HasComponent<AudioComponent>())
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
			bool open = (ImGui::TreeNodeEx((void*)typeid(AudioComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Audio Component"));
			ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
			if (ImGui::Button("+", ImVec2{ 20,20 }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}
			ImGui::PopStyleVar();
			bool removecomponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove Component"))
					removecomponent = true;
				ImGui::EndPopup();
			}

			if (open)
			{
				auto& data = entity.GetComponent<AudioComponent>();
				ImGui::Button("Audio", ImVec2(200.0f, 100.0f));
				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
					{
						const wchar_t* path = (const wchar_t*)payload->Data;
						std::filesystem::path texturePath = std::filesystem::path(s_AssetsPath) / path;
						TH_CORE_INFO("{0}", texturePath.filename().string());

						data.filepath = texturePath.filename().string();

						/*data.texid = stash.Text_Storage[texturePath.filename().string()];
						data.text_file = stash.Text_Storage[texturePath.filename().string()];*/
					}
					ImGui::EndDragDropTarget();
				}
				ImGui::Text("Audio file loaded : %s\n", data.filepath.c_str());

				ImGui::TreePop();
			}

			if (removecomponent)
			{
				entity.RemoveComponent<AudioComponent>();
			}
		}

		if (entity.HasComponent<ParticleComponent>())
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
			bool open = (ImGui::TreeNodeEx((void*)typeid(ParticleComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Particle Component"));
			ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
			if (ImGui::Button("+", ImVec2{ 20,20 }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}
			ImGui::PopStyleVar();
			bool removecomponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove Component"))
					removecomponent = true;
				ImGui::EndPopup();
			}

			if (open)
			{
				auto& data = entity.GetComponent<ParticleComponent>();
				ImGui::TreePop();
			}

			if (removecomponent)
			{
				entity.RemoveComponent<ParticleComponent>();
			}
		}

		if (entity.HasComponent<Fonts>())
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
			bool open = (ImGui::TreeNodeEx((void*)typeid(Fonts).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Fonts"));
			ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
			if (ImGui::Button("+", ImVec2{ 20,20 }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}
			ImGui::PopStyleVar();
			bool removecomponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove Component"))
					removecomponent = true;
				ImGui::EndPopup();
			}

			if (open)
			{
				auto& data = entity.GetComponent<Fonts>();
				ImGui::TreePop();
			}

			if (removecomponent)
			{
				entity.RemoveComponent<Fonts>();
			}
		}

		if (entity.HasComponent<ObjectType>())
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
			bool open = (ImGui::TreeNodeEx((void*)typeid(ObjectType).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Object Type"));
			ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
			if (ImGui::Button("+", ImVec2{ 20,20 }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}
			ImGui::PopStyleVar();
			bool removecomponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove Component"))
					removecomponent = true;
				ImGui::EndPopup();
			}

			if (open)
			{
				auto& data = entity.GetComponent<ObjectType>();

				const char* items[] = { "Nil", "Player", "Enemy", "Obstacle", "Bullet", "Pick Up", "Goal"};
				static const char* current_item;

				if (data.type == ObjectTypeID::nil) {
					current_item = "Nil";
				}
				else if (data.type == ObjectTypeID::player) {
					current_item = "Player";
				}
				else if (data.type == ObjectTypeID::enemy) {
					current_item = "Enemy";
				}
				else if (data.type == ObjectTypeID::obstacle) {
					current_item = "Obstacle";
				}
				else if (data.type == ObjectTypeID::bullet) {
					current_item = "Bullet";
				}
				else if (data.type == ObjectTypeID::pickup) {
					current_item = "Pick Up";
				}
				else if (data.type == ObjectTypeID::goal) {
					current_item = "Goal";
				}

				//The second parameter is the label previewed before opening the combo.
				if (ImGui::BeginCombo("##combo", current_item))
				{
					for (int n = 0; n < IM_ARRAYSIZE(items); n++)
					{
						bool is_selected = (current_item == items[n]);
						if (ImGui::Selectable(items[n], is_selected)) {
							current_item = items[n];

							if (current_item == "Nil") {
								data.type = ObjectTypeID::nil;
							}
							if (current_item == "Player") {
								data.type = ObjectTypeID::player;
								//if()
							}
							if (current_item == "Enemy") {
								data.type = ObjectTypeID::enemy;
							}
							if (current_item == "Obstacle") {
								data.type = ObjectTypeID::obstacle;
							}
							if (current_item == "Bullet") {
								data.type = ObjectTypeID::bullet;
							}
							if (current_item == "Pick Up") {
								data.type = ObjectTypeID::pickup;
							}
							if (current_item == "Goal") {
								data.type = ObjectTypeID::goal;
							}
						}
						if (is_selected) {
							// You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}

				ImGui::TreePop();
			}

			if (removecomponent)
			{
				entity.RemoveComponent<ObjectType>();
			}
		}

		if (entity.HasComponent<CombatComponent>())
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
			bool open = (ImGui::TreeNodeEx((void*)typeid(CombatComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Combat Component"));
			ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
			if (ImGui::Button("+", ImVec2{ 20,20 }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}
			ImGui::PopStyleVar();
			bool removecomponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove Component"))
					removecomponent = true;
				ImGui::EndPopup();
			}

			if (open)
			{
				auto& data = entity.GetComponent<CombatComponent>();
				ImGui::DragFloat("Attack", &data.attack, 0.1f);
				ImGui::DragFloat("Health", &data.health, 0.1f);
				ImGui::TreePop();
			}

			if (removecomponent)
			{
				entity.RemoveComponent<CombatComponent>();
			}
		}

		if (entity.HasComponent<ScriptComponent>())
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
			bool open = (ImGui::TreeNodeEx((void*)typeid(ScriptComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Script Component"));
			ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
			if (ImGui::Button("+", ImVec2{ 20,20 }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}
			ImGui::PopStyleVar();
			bool removecomponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove Component"))
					removecomponent = true;
				ImGui::EndPopup();
			}

			if (open)
			{
				ImGui::TreePop();
			}

			if (removecomponent)
			{
				entity.RemoveComponent<ScriptComponent>();
			}
		}

		if (entity.HasComponent<AStarPathfindingAgent>())
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
			bool open = (ImGui::TreeNodeEx((void*)typeid(AStarPathfindingAgent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "AStarPathfindingAgent"));
			ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
			if (ImGui::Button("+", ImVec2{ 20,20 }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}
			ImGui::PopStyleVar();
			bool removecomponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove Component"))
					removecomponent = true;
				ImGui::EndPopup();
			}

			if (open)
			{
				auto& agentData = entity.GetComponent<AStarPathfindingAgent>();
				if (agentData.pathfindingEnabled)
				{
					ImGui::Text("True");

				}
				else
				{
					ImGui::Text("False");
				}

				if (ImGui::Button("Toggle Pathfinding"))
				{
					agentData.pathfindingEnabled = !agentData.pathfindingEnabled;

				}


				ImGui::TreePop();


				if (removecomponent)
				{
					entity.RemoveComponent<AStarPathfindingAgent>();
					//gridSystem.
				}
			}
		}

		if (entity.HasComponent<AStarPathfindingObstacle>())
	{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
			bool open = (ImGui::TreeNodeEx((void*)typeid(AStarPathfindingObstacle).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "AStarPathfindingObstacle"));
			ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
			if (ImGui::Button("+", ImVec2{ 20,20 }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}
			ImGui::PopStyleVar();
			bool removecomponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove Component"))
					removecomponent = true;
				ImGui::EndPopup();
			}

			if (open)
			{
				auto& obstacleData = entity.GetComponent<AStarPathfindingObstacle>();
				ImGui::DragFloat("Obstacle Width", &obstacleData.size.x);
				ImGui::DragFloat("Obstacle Height", &obstacleData.size.y);
				ImGui::DragFloat("Obstacle Position X", &obstacleData.position.x);
				ImGui::DragFloat("Obstacle Position Y", &obstacleData.position.y);


				//if (ImGui::Button("Create Grid"))
				//{
				//	//if(gridData.
				//	gridSystem.ClearGrid(gridData);
				//	gridSystem.CreateGrid(gridData);
				//	//std::cout << "Size of grid: " << gridData.nodeGrids.size();

				//	for (auto const& row : gridData.nodeGrids)
				//	{
				//		for (auto const& elem : row)
				//		{
				//			//std::cout << counter++ << " ";
				//			gridSystem.AddNeighbours(gridData, elem);

				//			//std::cout << 
				//		}

				//	}
				//	//gridSystem.CreateGrid(data);

				//	//std::cout << "w2222222222222222";
				//}
				/*ImGui::DragFloat("Scale X", &data.scaling.x, 0.1f);
				ImGui::DragFloat("Scale Y", &data.scaling.y, 0.1f);
				ImGui::DragFloat("Rotation", &data.rotation, 1.f, -360.f, 360.f);
				ImGui::DragFloat("Layer", &data.z_axis, 0.01f, -0.9f, 0.9f);
				ImGui::DragFloat("Blend", &data.alpha_val, 0.01f, 0.f, 1.f);*/
				ImGui::TreePop();
			}

			if (removecomponent)
			{
				auto& obstacleData = entity.GetComponent<AStarPathfindingObstacle>();
				gridSystem.RemoveObstacleFromGrid(*aStarSystem.grid, obstacleData);

				entity.RemoveComponent<AStarPathfindingObstacle>();


				//gridSystem.
			}
		}

		if (entity.HasComponent<Grid>())
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
			bool open = (ImGui::TreeNodeEx((void*)typeid(Grid).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Grid"));
			ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
			if (ImGui::Button("+", ImVec2{ 20,20 }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}
			ImGui::PopStyleVar();
			bool removecomponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove Component"))
					removecomponent = true;
				ImGui::EndPopup();
			}

			if (open)
			{
				auto& gridData = entity.GetComponent<Grid>();
				auto& transformData = entity.GetComponent<Transform>();
				//auto& gridTransform = entity.GetComponent<Transform>();
				ImGui::DragFloat("Grid Width ", &gridData.gridWorldSize.x);
				ImGui::DragFloat("Grid Height ", &gridData.gridWorldSize.y);
				ImGui::DragFloat("Node Radius ", &gridData.nodeRadius);
				//ImGui::
				if (ImGui::Button("Update Grid"))
				{
					gridData.origin = { transformData.translation.x - (gridData.gridWorldSize.x / 2),
					transformData.translation.y - (gridData.gridWorldSize.y / 2) };

					gridSystem.SetGridParameters(gridData, gridData.gridWorldSize, gridData.nodeRadius);
					gridSystem.ClearGrid(gridData);
					gridSystem.CreateGrid(gridData);

					gridSystem.AddNeighboursToGrid(gridData);
					std::cout << "ObstaclesSize: " << gridSystem.obstacles.size() << "\n";
					for (AStarPathfindingObstacle* obstacle : gridSystem.obstacles)
					{

						//gridSystem.RemoveObstacleFromGrid(*aStarSystem.grid, *obstacle);

						//obstacle.hasChanged = false;
						//obstacle.hasChanged = true;
						gridSystem.AddObstacleToGrid(*aStarSystem.grid, *obstacle);


						//gridSystem.UpdateObstacleInGrid(*aStarSystem.grid, obstacle)
					}
				}
				if (ImGui::Button("Show Grid"))
				{
					for (auto row : aStarSystem.grid->nodeGrids)
					{
						for (Node* node : row)
						{
							std::cout << node->blocked << " ";

						}
						std::cout << "\n";
					}


				}

				ImGui::TreePop();
			}

			if (removecomponent)
			{
				gridSystem.ClearGrid(entity.GetComponent<Grid>());
				entity.RemoveComponent<Grid>();
			}
		}

		if (entity.HasComponent<Target>())
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
			bool open = (ImGui::TreeNodeEx((void*)typeid(Target).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Target"));
			ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
			if (ImGui::Button("+", ImVec2{ 20,20 }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}
			ImGui::PopStyleVar();
			bool removecomponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove Component"))
					removecomponent = true;
				ImGui::EndPopup();
			}

			if (open)
			{
				//auto& agentData = entity.GetComponent<Target>();

				ImGui::TreePop();
			}

			if (removecomponent)
			{
				entity.RemoveComponent<Target>();
				//gridSystem.
			}
		}

		if (entity.HasComponent<ScriptComponent>())
		{
			/*
			if (ImGui::Button("+", ImVec2{ 20,20 }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}
			ImGui::PopStyleVar();
			bool removecomponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove Component"))
					removecomponent = true;
				ImGui::EndPopup();
			}
			*/
			auto& component_name = entity.GetComponent<ScriptComponent>().ClassName;

			bool scriptClassExists = ScriptEngine::EntityClassExists(component_name);

			char buffer[256];
			//memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, component_name.c_str());

			if (!scriptClassExists)
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.2f, 0.3f, 0.4f));

			if (ImGui::InputText("Class", buffer, sizeof(buffer)))
				component_name = buffer;

			//std::cout << component_name;

			if (!scriptClassExists)
				ImGui::PopStyleColor();

			/*
			if (removecomponent)
			{
				entity.RemoveComponent<ScriptComponent>();
			}
			*/
		}
		
	}
	
}
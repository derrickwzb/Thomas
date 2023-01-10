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
<<<<<<< HEAD
=======
#include "Thomas/Scripting/ScriptEngine.h"
#include "Thomas/Renderer/Texture_system.h"
>>>>>>> parent of 2038385 (Revert "Merge branch 'main' of https://github.com/derrickwzb/Thomas")

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

		if (entitydeleted)
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
			if(ImGui::InputText("Tag", buffer , sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}
		
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap;

		if (entity.HasComponent<Transform>())
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });	
			bool open = (ImGui::TreeNodeEx((void*)typeid(Transform).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"));
			ImGui::SameLine(ImGui::GetWindowWidth()-25.0f);
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
				if (ImGui::Button("Box_collider")) {
					if (box.box_tog != 1)
						box.box_tog = 1;
					else
						box.box_tog = 0;
				}
				ImGui::SameLine();
				if (ImGui::Button("Box_resize")) {
					box.box_trans.translation = data.translation;
					box.box_trans.scaling = data.scaling;
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
			bool open = (ImGui::TreeNodeEx((void*)typeid(Texture).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Box Collider 2D"));
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
			bool open = (ImGui::TreeNodeEx((void*)typeid(Texture).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Audio Component"));
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
				entity.RemoveComponent<BoxCollider2D>();
			}
		}

<<<<<<< HEAD

=======
		if (entity.HasComponent<ParticleComponent>())
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
			bool open = (ImGui::TreeNodeEx((void*)typeid(Texture).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Particle Component"));
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


		if (entity.HasComponent<ScriptComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().tag;
			
			const auto& entity = ScriptEngine::GetEntityClasses();

			bool scriptClassExists = ScriptEngine::EntityClassExists(tag);
			if (entity.find(tag) != entity.end())
				scriptClassExists = true;

			char buffer[256];
			//memset(buffer, 0, sizeof(buffer));
			strcpy(buffer, tag.c_str());

			if (!scriptClassExists)
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.2f, 0.3f, 0.1f));

			if (ImGui::InputText("Class", buffer, sizeof(buffer)))
				tag = buffer;

			if (!scriptClassExists)
				ImGui::PopStyleColor();
			
		}
		
>>>>>>> parent of 2038385 (Revert "Merge branch 'main' of https://github.com/derrickwzb/Thomas")
	}

}

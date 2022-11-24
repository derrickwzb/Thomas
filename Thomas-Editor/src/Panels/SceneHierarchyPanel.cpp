#include "SceneHierarchyPanel.h"
#include "ImGui/imgui.h"
#include "Thomas/Scene/Components.h"

namespace Thomas
{

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
					data.text_file = 1;
						//text.text_file = 1; 
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("Box Collider 2D"))
				{
					auto& box = m_SelectionContext.GetComponent<Box_collider>();
					auto& boxCollider = m_SelectionContext.AddComponent<BoxCollider2D>();
					boxCollider.verticesList.push_back(box.box_trans.vertice0);
					boxCollider.verticesList.push_back(box.box_trans.vertice1);
					boxCollider.verticesList.push_back(box.box_trans.vertice2);
					boxCollider.verticesList.push_back(box.box_trans.vertice3);
					
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("RigidBody"))
				{
					auto& data = m_SelectionContext.AddComponent<RigidBody>();
					//data.
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
				//TH_CORE_INFO("{0}", data.translation.x);
				ImGui::DragFloat("Position X", &data.translation.x, 0.1f);
				ImGui::DragFloat("Position Y", &data.translation.y, 0.1f);
				ImGui::DragFloat("Scale X", &data.scaling.x, 0.1f);
				ImGui::DragFloat("Scale Y", &data.scaling.y, 0.1f);
				ImGui::DragFloat("Rotation", &data.rotation, 0.1f, -360.f, 360.f);
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
				//ImGui::
				
				//TH_CORE_INFO("{0}", data.translation.x);
				/*ImGui::DragFloat("Position X", &data.translation.x, 0.1f);
				ImGui::DragFloat("Position Y", &data.translation.y, 0.1f);
				ImGui::DragFloat("Scale X", &data.scaling.x, 0.1f);
				ImGui::DragFloat("Scale Y", &data.scaling.y, 0.1f);
				ImGui::DragFloat("Rotation", &data.rotation, 0.1f, -360.f, 360.f);*/
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
				//ImGui::

				//TH_CORE_INFO("{0}", data.translation.x);
				/*ImGui::DragFloat("Position X", &data.translation.x, 0.1f);
				ImGui::DragFloat("Position Y", &data.translation.y, 0.1f);
				ImGui::DragFloat("Scale X", &data.scaling.x, 0.1f);
				ImGui::DragFloat("Scale Y", &data.scaling.y, 0.1f);
				ImGui::DragFloat("Rotation", &data.rotation, 0.1f, -360.f, 360.f);*/
				ImGui::TreePop();
			}

			if (removecomponent)
			{
				entity.RemoveComponent<BoxCollider2D>();
			}
		}

		if (entity.HasComponent<RigidBody>())
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
			bool open = (ImGui::TreeNodeEx((void*)typeid(Texture).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "RigidBody"));
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
				auto& data = entity.GetComponent<RigidBody>();
				//ImGui::

				//TH_CORE_INFO("{0}", data.translation.x);
				/*ImGui::DragFloat("Position X", &data.translation.x, 0.1f);
				ImGui::DragFloat("Position Y", &data.translation.y, 0.1f);
				ImGui::DragFloat("Scale X", &data.scaling.x, 0.1f);
				ImGui::DragFloat("Scale Y", &data.scaling.y, 0.1f);
				ImGui::DragFloat("Rotation", &data.rotation, 0.1f, -360.f, 360.f);*/
				ImGui::TreePop();
			}

			if (removecomponent)
			{
				entity.RemoveComponent<RigidBody>();
			}
		}
		/*if (entity.HasComponent<AudioComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, tag.c_str());
			if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}*/

	}

}

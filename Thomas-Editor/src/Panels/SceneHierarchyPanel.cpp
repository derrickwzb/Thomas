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
			Entity entity{ e.first , m_Context.get() };
			//TH_CORE_INFO("{0}", e.first);
			DrawEntityNode(entity);

		}
		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_SelectionContext = {};

		ImGui::End();
		
		ImGui::Begin("Inspector");
		if (m_SelectionContext)
		{
			DrawComponents(m_SelectionContext);
			//TH_CORE_INFO("{0}", m_SelectionContext.GetComponent<TagComponent>().tag);
		}


		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().tag;

		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
			TH_CORE_INFO("{0}", tag);
		}

		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
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
		if (entity.HasComponent<Transform>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(Transform).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
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
		}

	}

}

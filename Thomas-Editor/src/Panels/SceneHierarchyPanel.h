#pragma once

#include "Thomas/Core/Core.h"
#include "Thomas/Core/Log.h"
#include "Thomas/Scene/Scene.h"
#include "Thomas/Scene/Entity.h"


namespace Thomas
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const std::shared_ptr<Scene>& context);

		void SetContext(const std::shared_ptr<Scene>& context);

		void OnImGuiRender();

	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);

	private:
		std::shared_ptr<Scene> m_Context;
		Entity m_SelectionContext;
		Entity m_DeletionContext;

	};

}


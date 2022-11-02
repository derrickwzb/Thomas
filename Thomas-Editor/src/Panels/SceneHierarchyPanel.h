#pragma once

#include "Thomas/Core/Core.h"
#include "Thomas/Scene/Scene.h"

namespace Thomas 
{

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const std::shared_ptr<Scene>& scene);
		void OnImGuiRender();


		void SetContext(const std::shared_ptr<Scene>& scene);

	private:
		void DrawEntityNode(Scene& scene);
	private:

		std::shared_ptr<Scene> m_Context;
		Entity m_SelectionContext;


	};

}


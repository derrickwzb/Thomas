/******************************************************************************/
/*!
\file		EditorLayer.h
\author 	Derrick Woo
\par    	email: d.woo@digipen.edu
\date   	2/11/2022
\brief		This file contains the declaration for the the editor layer class and its interface.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

#include "Thomas.h"

#include "Panels/ContentBrowserPanel.h"
#include "Panels/SceneHierarchyPanel.h"

namespace Thomas {
	class EditorLayer : public Thomas::Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach()override;
		virtual void OnDetach()override;

		void OnUpdate(Timestep ts)override;
		virtual void OnImGuiRender()override;
		void OnEvent(Event& e)override;

	private:

		//camera controller
		//Camera m_Camera;
		std::shared_ptr <Framebuffer> m_Framebuffer;
		std::shared_ptr<Scene> m_ActiveScene;

		glm::vec2 m_ViewportSize = {0.f,0.f};
		glm::vec2 m_OldViewport = { 0.f,0.f };
		glm::vec2 button_size = { 100.f, 30.f };
		glm::vec2 button_offset = { 0.f, 0.f };
		glm::vec2 vp_pos = { 0.f,0.f };

		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;

		ContentBrowserPanel m_ContentBrowserPanel;
		SceneHierarchyPanel m_SceneHierarchyPanel;
	};
}


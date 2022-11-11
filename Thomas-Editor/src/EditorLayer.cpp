/******************************************************************************/
/*!
\file		EditorLayer.cpp
\author 	Derrick Woo
\par    	email: d.woo@digipen.edu
\date   	2/11/2022
\brief		This file contains the definition for the the editor layer class and its interface.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "EditorLayer.h"
#include "ImGui/imgui.h"

#include "Thomas/Renderer/Graphics.h"
#include "GLEW/include/GL/glew.h"



namespace Thomas
{
	EditorLayer::EditorLayer()
		:Layer("Editor Layer")
	{

	}

	void EditorLayer::OnAttach()
	{
		FramebufferSpec fbSpec;
		fbSpec.Width = 1920;
		fbSpec.Height = 1080;
		m_Framebuffer = std::make_shared<Framebuffer>(fbSpec);
		m_ActiveScene = std::make_shared<Scene>();

		//auto square = m_ActiveScene->CreateEntity("Test Entity");
		auto square2 = m_ActiveScene->CreateEntity();
		
		auto test2 = m_ActiveScene->CreateEntity("test entity2");

		//square.AddComponent<AudioComponent>();
		
		//TH_CORE_INFO("{0}", square2.GetComponent<TagComponent>().tag);
		/*TH_CORE_INFO("{0}", test2.GetComponent<TagComponent>().tag);
		test2.GetComponent<TagComponent>().tag = "changed test2";
		TH_CORE_INFO("{0}", test2.GetComponent<TagComponent>().tag);*/


		m_SceneHierarchyPanel.SetContext(m_ActiveScene);

	}

	void EditorLayer::OnDetach()
	{
		//profile

	}

	void EditorLayer::OnUpdate(Thomas::Timestep ts)
	{
		m_ActiveScene->OnUpdate(ts);
		
		////render update here
		if (m_ViewportFocused)
		{
		/*	physicsSystem.Input(Graphics::sel, ts);
			physicsSystem.Update(Application::entities, ts);*/
		}

		//Graphics::update(Application::entities);
		m_Framebuffer->Bind();
		//Graphics::draw();
		glClearColor(1.f, 1.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Graphics::draw(Application::entities);

		m_Framebuffer->Unbind();

	}

	void EditorLayer::OnImGuiRender()
	{

			static bool dockspaceOpen = true;
			static bool opt_fullscreen_persistant = true;
			bool opt_fullscreen = opt_fullscreen_persistant;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_fullscreen)
			{
				ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->Pos);
				ImGui::SetNextWindowSize(viewport->Size);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

				if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
					window_flags |= ImGuiWindowFlags_NoBackground;

				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
				ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
				ImGui::PopStyleVar();

				if (opt_fullscreen)
					ImGui::PopStyleVar(2);

				ImGuiIO& io = ImGui::GetIO();
				if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
				{
					ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
					ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
				}

				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("File"))
					{
						// Disabling fullscreen would allow the window to be moved to the front of other windows, 
						// which we can't undo at the moment without finer window depth/z control.
						//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

						if (ImGui::MenuItem("Exit")) Application::Get().Close();
						ImGui::EndMenu();
					}

					ImGui::EndMenuBar();
				}

				m_SceneHierarchyPanel.OnImGuiRender();
				m_ContentBrowserPanel.OnImGuiRender();

				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
				ImGui::Begin("Viewport");
				m_ViewportFocused = ImGui::IsWindowFocused();
				m_ViewportHovered = ImGui::IsWindowHovered();
				Application::Get().GetImguiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);
				
				ImVec2 viewportPanelsize = ImGui::GetContentRegionAvail();	

				if (m_ViewportSize != *((glm::vec2*)&viewportPanelsize) && viewportPanelsize.x > 0 && viewportPanelsize.y > 0)
				{
					m_ViewportSize = { viewportPanelsize.x , viewportPanelsize.y };
				}
				//Graphics::cam_stuff.Camera2D_Resize(m_ViewportSize.x, m_ViewportSize.y);
				uint32_t textureID = m_Framebuffer->GetColorAttachmentID();

				ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x,m_ViewportSize.y}, ImVec2{0, 1}, ImVec2{1, 0});
				ImGui::End();
				ImGui::PopStyleVar();

				ImGui::End();
			}
	}

	void EditorLayer::OnEvent(Thomas::Event& e)
	{
		//push event to camera controller
	}
}
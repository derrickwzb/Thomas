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

//#include "Thomas/Renderer/Graphics.h"
#include "GLEW/include/GL/glew.h"

//#include "ImGui/backends/imgui_impl_glfw.h"
//#include "ImGui/backends/imgui_impl_opengl3.h"
#include "Thomas/Scene/SceneSerializer.h"
#include "Thomas/Utils/CoreUtils.h"
#include "Thomas/Scene/Components.h"
#include "Thomas/Physics/RigidBody.hpp"
#include "Thomas/Collision/BoxCollider2D.hpp"


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


		auto test3 = m_ActiveScene->CreateEntity("test entity3");
		/*square2.AddComponent<RigidBody>();
		square2.AddComponent<BoxCollider2D>();
		square2.AddComponent<Box_collider>();*/

		
		/*test2.AddComponent<RigidBody>();
		test2.AddComponent<BoxCollider2D>();
		test2.AddComponent<Box_collider>();
		test2.AddComponent<Tr
		test3.AddComponent<RigidBody>();
		test3.AddComponent<BoxCollider2D>();
		test3.AddComponent<Box_collider>();*/

		//test2.AddComponent<NativeScriptComponent>().Bind<Camera>();
		//TH_CORE_INFO("{0}", square2.GetComponent<Transform>().translation[0]);

		//square.AddComponent<AudioComponent>();
		
		//TH_CORE_INFO("{0}", square2.GetComponent<TagComponent>().tag);
		/*TH_CORE_INFO("{0}", test2.GetComponent<TagComponent>().tag);
		test2.GetComponent<TagComponent>().tag = "changed test2";
		TH_CORE_INFO("{0}", test2.GetComponent<TagComponent>().tag);*/

		/*m_ViewportSize.x = fbSpec.Width;
		m_ViewportSize.y = fbSpec.Height;*/
		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
		//Graphics::cam_stuff.Camera2D_Update(fbSpec.Width, fbSpec.Height);
		
		/*SceneSerializer serializer(m_ActiveScene);
		serializer.Serialize("../Assets/Scene/Thomas.json");*/

	}

	void EditorLayer::OnDetach()
	{
		//profile
		//ImGui_ImplOpenGL3_Shutdown();
		//ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

	}

	void EditorLayer::OnUpdate(Thomas::Timestep ts)
	{
		
		if (FramebufferSpec spec = m_Framebuffer->GetSpec();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}
		//Graphics::cam_stuff.Camera2D_Update(m_ViewportSize.x, m_ViewportSize.y);
		
		////render update here
		if (m_ViewportFocused)
		{
			physicsSystem.Update(m_ActiveScene.get(), ts);
			/*physicsSystem.Input(Graphics::sel, ts);
			physicsSystem.Update(Application::entities, ts);*/
		}

		//Graphics::update(Application::entities);
		m_Framebuffer->Bind();
		//Graphics::draw();
		glClearColor(0.f, 1.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Graphics::draw(Application::entities);
		m_ActiveScene->OnUpdate(ts);

		m_Framebuffer->Unbind();
		
		//std::map<EntityID, Signature> group = m_ActiveScene->m_Registry->GetEntities();

		////for the map bullshit , iterate through and get all those that has component <T> and do render
		//// sample for update from graphics (just took 1)
		//for (auto e : group)
		//{
		//	Entity entity = { e.first, m_ActiveScene.get()};
		//	entity.HasComponent<fgydshad>()
		//}



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
				ImGuiStyle& style = ImGui::GetStyle();
				float minPanelSize = style.WindowMinSize.x;
				style.WindowMinSize.x = 370.0f;
				if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
				{
					ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
					ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
				}
				style.WindowMinSize.x = minPanelSize;
				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("File"))
					{
						// Disabling fullscreen would allow the window to be moved to the front of other windows, 
						// which we can't undo at the moment without finer window depth/z control.
						//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);
						if (ImGui::MenuItem("New ... ", "Ctrl+N"))
						{
							auto entities = m_ActiveScene->m_Registry->GetEntities();
							for (auto e : entities)
							{
								Entity entity = { e.first ,m_ActiveScene.get() };
								m_ActiveScene->DestroyEntity(entity);
							}
							
						}
						if (ImGui::MenuItem("Open ... ", "Ctrl+O"))
						{
							std::string filepath = FileDialogs::OpenFile("Thomas Scene\0*.json\0");
							if (!filepath.empty())
							{
							
								m_SceneHierarchyPanel.SetContext(m_ActiveScene);

								SceneSerializer serializer(m_ActiveScene);
								serializer.Deserialize(filepath);

							}
						}
						if (ImGui::MenuItem("Save", "Ctrl+S"))
						{
							std::string filepath = FileDialogs::SaveFile("Thomas Scene\0*.json\0");
							if (!filepath.empty())
							{
								SceneSerializer serializer(m_ActiveScene);
								serializer.Serialize(filepath);
							}
						}
						if (ImGui::MenuItem("Exit")) Application::Get().Close();
						ImGui::EndMenu();
					}

					ImGui::EndMenuBar();
				}

				m_SceneHierarchyPanel.OnImGuiRender();
				m_ContentBrowserPanel.OnImGuiRender();
				static bool viewportOpen = true;
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
				ImGui::Begin("Viewport" ,&viewportOpen, ImGuiWindowFlags_NoResize);

				ImVec2 pos;
				button_offset.x = (ImGui::GetWindowWidth() / 2.f) - (button_size.x);
				button_offset.y = 20.f;	// Offset the top viewport logo
				pos.x = button_offset.x;
				pos.y = button_offset.y;
				ImGui::SetCursorPos(pos);
				ImGui::Button("Play", ImVec2(button_size.x, button_size.y));
				ImGui::SameLine(0, 10.f);
				ImGui::Button("Pause", ImVec2(button_size.x, button_size.y));
				m_ViewportFocused = ImGui::IsWindowFocused();
				m_ViewportHovered = ImGui::IsWindowHovered();
				Application::Get().GetImguiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);
				
				ImVec2 viewportPanelsize = ImGui::GetContentRegionAvail();	

				if (m_OldViewport != *((glm::vec2*)&viewportPanelsize) && viewportPanelsize.x > 0 && viewportPanelsize.y > 0)
				{
					float temp_ar = viewportPanelsize.x / viewportPanelsize.y;
					if (temp_ar > Graphics::cam_stuff.ar) {
						m_ViewportSize.y = viewportPanelsize.y;
						m_ViewportSize.x = viewportPanelsize.y * Graphics::cam_stuff.ar;
						vp_pos.y = button_size.y + 22.f;		// Offset the button size and the viewport logo
						vp_pos.x = (ImGui::GetContentRegionAvail().x / 2.f) - (m_ViewportSize.x / 2.f);
					}
					else if (temp_ar < Graphics::cam_stuff.ar) {
						m_ViewportSize.x = viewportPanelsize.x;
						m_ViewportSize.y = viewportPanelsize.x / Graphics::cam_stuff.ar;
						vp_pos.y = button_size.y + 22.f + (ImGui::GetContentRegionAvail().y / 2.f) - (m_ViewportSize.y / 2.f); // Offset the button size and the viewport logo
					}
					else {
						m_ViewportSize.x = viewportPanelsize.x;
						m_ViewportSize.y = viewportPanelsize.y;
					}
					m_OldViewport.x = viewportPanelsize.x;
					m_OldViewport.y = viewportPanelsize.x;
				}
				ImVec2 temp_pos;
				temp_pos.x = vp_pos.x;
				temp_pos.y = vp_pos.y;
				ImGui::SetCursorPos(temp_pos);

				Graphics::cam_stuff.Camera2D_Update(m_ViewportSize.x, m_ViewportSize.y);
				double Viewport_CursX, Viewport_CursY;
				Viewport_CursX = Input::GetMouseX() - ImGui::GetWindowPos().x - (m_ViewportSize.x / 2.f) - vp_pos.x + 10.f;
				Viewport_CursY = -(Input::GetMouseY() - ImGui::GetWindowPos().y - (m_ViewportSize.y / 2.f) - vp_pos.y + (button_offset.y/2) + (button_size.y/2));

				std::map<EntityID, Signature> group = m_ActiveScene->m_Registry->GetEntities();
				for (auto& e : group) {
					if (m_ActiveScene->m_Registry->HasComponent<Transform>(e.first)) {
						Entity objs = { e.first, m_ActiveScene.get() };
						auto& trans_stuff = objs.GetComponent<Transform>();
						auto& box_stuff = objs.GetComponent<Box_collider>();
						auto& text_stuff = objs.GetComponent<Texture>();

						if (objs.GetID() == 0) {
							text_stuff.texid = stash.Text_Storage["wallpaper.png"];
						}
						/*else {
							text_stuff.texid = stash.Text_Storage["Chef_Kay_Top.png"];
						}*/
						trans_stuff.minmax_screen(m_ViewportSize.x, m_ViewportSize.y);

						if ((Viewport_CursX > trans_stuff.screen_min.x && Viewport_CursX<trans_stuff.screen_max.x && Viewport_CursY>trans_stuff.screen_min.y && Viewport_CursY < trans_stuff.screen_max.y) && Input::IsMouseButtonPressed(0) && Graphics::obj_clicked == 0 && objs.GetID()!=0) {
							Graphics::sel = objs.GetID();
							Entity e = { objs.GetID() , m_ActiveScene.get() };
							m_SceneHierarchyPanel.GetSelection() = e;
							Graphics::obj_clicked = 1;
							std::cout << Graphics::sel << std::endl;
						}

						// Keypress to move the object
						if (objs.GetID() == Graphics::sel) {
							if (Input::IsKeyPressed(TH_KEY_W)){
								trans_stuff.translation.y -= 0.001f;
								Graphics::cam_stuff.translation.y += 0.001f * (m_ViewportSize.y / Graphics::cam_stuff.c_height);
							}
							if (Input::IsKeyPressed(TH_KEY_S)) {
								trans_stuff.translation.y += 0.001f;
								Graphics::cam_stuff.translation.y -= 0.001f * (m_ViewportSize.y / Graphics::cam_stuff.c_height);
							}
							if (Input::IsKeyPressed(TH_KEY_A)) {
								trans_stuff.translation.x -= 0.001f;
								Graphics::cam_stuff.translation.x -= 0.001f * (m_ViewportSize.y / Graphics::cam_stuff.c_width);
							}
							if (Input::IsKeyPressed(TH_KEY_D)) {
								trans_stuff.translation.x += 0.001f;
								Graphics::cam_stuff.translation.x += 0.001f * (m_ViewportSize.y / Graphics::cam_stuff.c_width);
							}
						}

						if ((Graphics::obj_clicked != 0) && (objs.GetID() == Graphics::sel)) {
							glm::vec2 move = glm::vec2(Viewport_CursX, Viewport_CursY);
							glm::vec2 diff_dist = glm::vec2(trans_stuff.translation.x - box_stuff.box_trans.translation.x, trans_stuff.translation.y - box_stuff.box_trans.translation.y);
							trans_stuff.translation.x = (move.x / (m_ViewportSize.x / 4.f));
							trans_stuff.translation.y = -(move.y / (m_ViewportSize.y / 4.f));
							box_stuff.box_trans.translation.x = (move.x / (m_ViewportSize.x / 4)) - diff_dist.x;
							box_stuff.box_trans.translation.y = -(move.y / (m_ViewportSize.y / 4)) - diff_dist.y;
						}
						if (!Input::IsMouseButtonPressed(0))
							Graphics::obj_clicked = 0;
					}
				}
				/*if (m_ViewportSize != *((glm::vec2*)&viewportPanelsize) && viewportPanelsize.x > 0 && viewportPanelsize.y > 0)
				{
					m_Framebuffer->Resize((uint32_t)viewportPanelsize.x, (uint32_t)viewportPanelsize.y);
					m_ViewportSize = { viewportPanelsize.x , viewportPanelsize.y };
				}*/
				uint32_t textureID = m_Framebuffer->GetColorAttachmentID();

				//m_Framebuffer->GetSpec().Height
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
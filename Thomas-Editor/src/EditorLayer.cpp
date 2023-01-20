/******************************************************************************/
/*!
\file				EditorLayer.cpp
\author 		Derrick Woo
\par				email: d.woo@digipen.edu
\code			70%
\co-author	Xie Zhi Xiong
\par				email: xiong.x@digipen.edu
\code			30%
\date   	2/11/2022
\brief		This file contains the definition for the the editor layer class and its interface.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "EditorLayer.h"
#include "ImGui/imgui.h"
#include "GLEW/include/GL/glew.h"
#include "Thomas/Scene/Scene.h"
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

		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
		ScriptEngine::OnRuntimeStart(m_ActiveScene.get());
	}

	void EditorLayer::OnDetach()
	{
		
	}

	void EditorLayer::OnUpdate(Thomas::Timestep ts)
	{
		
		if (FramebufferSpec spec = m_Framebuffer->GetSpec();
			Graphics::m_ViewportSize.x > 0.0f && Graphics::m_ViewportSize.y > 0.0f && (spec.Width != Graphics::m_ViewportSize.x || spec.Height != Graphics::m_ViewportSize.y))
		{
			m_Framebuffer->Resize((uint32_t)Graphics::m_ViewportSize.x, (uint32_t)Graphics::m_ViewportSize.y);
		}

		////render update here
		if (m_ViewportFocused)
		{
			physicsSystem.Update(m_ActiveScene.get(), ts);
		}

		m_Framebuffer->Bind();

		glClearColor(0.5f, 0.5f, 0.5f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_ActiveScene->OnUpdate(ts);

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
						//if (ImGui::MenuItem("test")) 
						//{
						//	std::string filepath = ("../Assets/Scene/level1.json");
						//	if (!filepath.empty())
						//	{

						//		m_SceneHierarchyPanel.SetContext(m_ActiveScene);

						//		SceneSerializer serializer(m_ActiveScene);
						//		serializer.Deserialize(filepath);

						//	}
						//}
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
				ImGui::SetCursorPos(pos); // Offset the button
				ImGui::Button("Play", ImVec2(button_size.x, button_size.y));
				ImGui::SameLine(0, 10.f);
				ImGui::Button("Pause", ImVec2(button_size.x, button_size.y));
				m_ViewportFocused = ImGui::IsWindowFocused();
				m_ViewportHovered = ImGui::IsWindowHovered();
				Application::Get().GetImguiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);
				
				ImVec2 viewportPanelsize = ImGui::GetContentRegionAvail();	

				// If the Imgui Viewport size change adjust the render screen accordingly 
				if (m_OldViewport != *((glm::vec2*)&viewportPanelsize) && viewportPanelsize.x > 0 && viewportPanelsize.y > 0)
				{
					// Compute the new aspect ratio
					float temp_ar = viewportPanelsize.x / viewportPanelsize.y;

					// If aspect ratio is greater than the camera aspect ratio
					if (temp_ar > Graphics::cam_stuff.ar) {
						Graphics::m_ViewportSize.y = viewportPanelsize.y;
						Graphics::m_ViewportSize.x = viewportPanelsize.y * Graphics::cam_stuff.ar;
						vp_pos.y = button_size.y + 22.f;		// Offset the button size and the viewport logo
						vp_pos.x = (ImGui::GetContentRegionAvail().x / 2.f) - (Graphics::m_ViewportSize.x / 2.f);			// Change the width
					}

					// If aspect ratio is smaller than the camera aspect ratio
					else if (temp_ar < Graphics::cam_stuff.ar) {
						Graphics::m_ViewportSize.x = viewportPanelsize.x;
						Graphics::m_ViewportSize.y = viewportPanelsize.x / Graphics::cam_stuff.ar; // Change the height
						vp_pos.y = button_size.y + 22.f + (ImGui::GetContentRegionAvail().y / 2.f) - (Graphics::m_ViewportSize.y / 2.f); // Offset the button size and the viewport logo
					}
					else {
						Graphics::m_ViewportSize.x = viewportPanelsize.x;
						Graphics::m_ViewportSize.y = viewportPanelsize.y;
					}
					m_OldViewport.x = viewportPanelsize.x;
					m_OldViewport.y = viewportPanelsize.x;
				}
				ImVec2 temp_pos;
				temp_pos.x = vp_pos.x;
				temp_pos.y = vp_pos.y;
				ImGui::SetCursorPos(temp_pos); // Set offset for the render screen

				Graphics::cam_stuff.Camera2D_Update(static_cast<int>(Graphics::m_ViewportSize.x), static_cast<int>(Graphics::m_ViewportSize.y));

				// On_Screen mouse cursor
				double Viewport_CursX, Viewport_CursY;
				Viewport_CursX = Input::GetMouseX() - ImGui::GetWindowPos().x - (Graphics::m_ViewportSize.x / 2.f) - vp_pos.x + 10.f;
				Viewport_CursY = -(Input::GetMouseY() - ImGui::GetWindowPos().y - (Graphics::m_ViewportSize.y / 2.f) - vp_pos.y + (button_offset.y/2) + (button_size.y/2)) ;

				std::map<EntityID, Signature> group = m_ActiveScene->m_Registry->GetEntities();
				for (auto& e : group) {
					if (m_ActiveScene->m_Registry->HasComponent<Transform>(e.first)) {
						Entity objs = { e.first, m_ActiveScene.get() };
						auto& trans_stuff = objs.GetComponent<Transform>();
						auto& box_stuff = objs.GetComponent<Box_collider>();

						trans_stuff.minmax_screen(Graphics::m_ViewportSize.x, Graphics::m_ViewportSize.y);

						// Collision check between the on_screen mouse cursor and the on_screen objects
						if ((Viewport_CursX > trans_stuff.screen_min.x && Viewport_CursX<trans_stuff.screen_max.x && Viewport_CursY>trans_stuff.screen_min.y && Viewport_CursY < trans_stuff.screen_max.y) && Input::IsMouseButtonPressed(0) && objs.GetID()!=0) {
							++Graphics::obj_counter;
							if (Graphics::obj_counter == 1) {
								Graphics::sel = objs.GetID();
								Graphics::sel_layer = trans_stuff.z_axis;
								Entity e = { objs.GetID() , m_ActiveScene.get() };
								m_SceneHierarchyPanel.GetSelection() = e;
								Graphics::obj_clicked = true;
							}
							else {
								if (trans_stuff.z_axis < Graphics::sel_layer) {
									Graphics::sel = objs.GetID();
									Graphics::sel_layer = trans_stuff.z_axis;
									Entity e = { objs.GetID() , m_ActiveScene.get() };
									m_SceneHierarchyPanel.GetSelection() = e;
									Graphics::obj_clicked = true;
								}
							}
							//std::cout << "Items: " << Graphics::obj_clicked << std::endl;
						}

						// Keypress to move the object
						if (objs.GetID() == Graphics::sel) {
							/*if (Input::IsKeyPressed(TH_KEY_W)){
								trans_stuff.translation.y -= 0.01f;
								box_stuff.box_trans.translation.y -= 0.01f;
								Graphics::cam_stuff.translation.y += 0.01f * (m_ViewportSize.y / Graphics::cam_stuff.c_height);
							}
							if (Input::IsKeyPressed(TH_KEY_S)) {
								trans_stuff.translation.y += 0.01f;
								box_stuff.box_trans.translation.y += 0.01f;
								Graphics::cam_stuff.translation.y -= 0.01f * (m_ViewportSize.y / Graphics::cam_stuff.c_height);
							}
							if (Input::IsKeyPressed(TH_KEY_A)) {
								trans_stuff.translation.x -= 0.01f;
								box_stuff.box_trans.translation.x -= 0.01f;
								Graphics::cam_stuff.translation.x -= 0.01f * (m_ViewportSize.y / Graphics::cam_stuff.c_width);
							}
							if (Input::IsKeyPressed(TH_KEY_D)) {
								trans_stuff.translation.x += 0.01f;
								box_stuff.box_trans.translation.x += 0.01f;
								Graphics::cam_stuff.translation.x += 0.01f * (m_ViewportSize.y / Graphics::cam_stuff.c_width);*/
							//}

							Graphics::cam_stuff.c_aspectratio = Graphics::cam_stuff.c_width / Graphics::cam_stuff.c_height;
							if (Input::IsKeyPressed(TH_KEY_Z)) {
								Graphics::cam_stuff.c_width += 10.f;
								Graphics::cam_stuff.c_height += 10.f / Graphics::cam_stuff.c_aspectratio;

								//Graphics::cam_stuff.scaling.x += 1.f;
								//Graphics::cam_stuff.scaling.y += 1.f;
							}
							if (Input::IsKeyPressed(TH_KEY_X)) {
								Graphics::cam_stuff.c_width -= 10.f;
								Graphics::cam_stuff.c_height -= 10.f / Graphics::cam_stuff.c_aspectratio;

								//Graphics::cam_stuff.scaling.x -= 1.f;
								//Graphics::cam_stuff.scaling.y -= 1.f;
							}

							if (trans_stuff.mouse_following == TRUE) {
								glm::vec2 move = glm::vec2(Viewport_CursX, Viewport_CursY);
								glm::vec2 A = glm::vec2(0, -1.f);
								glm::vec2 B = glm::vec2(trans_stuff.world_to_screen(move));
								B.x -= trans_stuff.translation.x;
								B.y -= trans_stuff.translation.y;
								float dot_product = glm::dot(A,B);
								std::cout << B.x << std::endl;
								float angle = acos(dot_product / (glm::length(A) * glm::length(B)));
								float degree = (angle / static_cast<float>(M_PI)) * 180.f;
								if ((B.x + trans_stuff.translation.x) < trans_stuff.translation.x)
									degree *= -1;
								trans_stuff.rotation = degree;			
								Graphics::cam_stuff.rotation = (degree * -1.f);
								if (Input::IsKeyPressed(TH_KEY_I)) {
									Graphics::cam_stuff.move_flag = GL_TRUE;
									trans_stuff.translation.x += (0.001f * Graphics::cam_stuff.up.x * (Graphics::cam_stuff.c_width / Graphics::m_ViewportSize.y));
									trans_stuff.translation.y -= (0.001f * Graphics::cam_stuff.up.y * (Graphics::cam_stuff.c_height / Graphics::m_ViewportSize.y));
									box_stuff.box_trans.translation.x += (0.001f * Graphics::cam_stuff.up.x * (Graphics::cam_stuff.c_width / Graphics::m_ViewportSize.y));
									box_stuff.box_trans.translation.y -= (0.001f * Graphics::cam_stuff.up.y * (Graphics::cam_stuff.c_height / Graphics::m_ViewportSize.y));
								}
								else {
									Graphics::cam_stuff.move_flag = GL_FALSE;
								}
							}

							// Upon clicking, game object follows mouse cursor
							if ((Graphics::obj_clicked != 0) && Graphics::sel == objs.GetID() && trans_stuff.mouse_following == FALSE) {
								glm::vec2 move = glm::vec2(Viewport_CursX, Viewport_CursY);
								glm::vec2 diff_dist = glm::vec2(trans_stuff.translation.x - box_stuff.box_trans.translation.x, trans_stuff.translation.y - box_stuff.box_trans.translation.y);

								trans_stuff.translation = trans_stuff.world_to_screen(move);
								glm::vec2 temp_check = trans_stuff.screen_to_world(trans_stuff.translation);
								std::cout << temp_check.x << "        " << temp_check.y << std::endl;
								box_stuff.box_trans.translation.x = trans_stuff.translation.x - diff_dist.x;
								box_stuff.box_trans.translation.y = trans_stuff.translation.y - diff_dist.y;
							}
						}

						if (!Input::IsMouseButtonPressed(0)) {
							Graphics::obj_clicked = false;
							Graphics::obj_counter = 0;
						}
					}
				}
				uintptr_t textureID = m_Framebuffer->GetColorAttachmentID();
				ImGui::Image((ImTextureID)textureID, ImVec2{ Graphics::m_ViewportSize.x,Graphics::m_ViewportSize.y}, ImVec2{0, 1}, ImVec2{1, 0});
				ImGui::End();
				ImGui::PopStyleVar();

				ImGui::End();
			}
	}

	void EditorLayer::OnEvent(Thomas::Event& e)
	{

	}

}
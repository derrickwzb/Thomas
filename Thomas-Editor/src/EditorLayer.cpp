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
#include "ImGuizmo.h"
#include "Thomas/Renderer/Additional_Parts.h"


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

			// Camera Control
			if (Input::IsKeyPressed(TH_KEY_Z) && Graphics::cam_stuff.height <= Graphics::cam_stuff.max_height)
				Graphics::cam_stuff.height += 2.f * ts;
			if (Input::IsKeyPressed(TH_KEY_X) && Graphics::cam_stuff.height >= Graphics::cam_stuff.min_height)
				Graphics::cam_stuff.height -= 2.f * ts;
			if (Input::IsKeyPressed(TH_KEY_W)) Graphics::cam_stuff.translation.y -= 2.f * ts;
			if (Input::IsKeyPressed(TH_KEY_A)) Graphics::cam_stuff.translation.x -= 2.f * ts;
			if (Input::IsKeyPressed(TH_KEY_S)) Graphics::cam_stuff.translation.y += 2.f * ts;
			if (Input::IsKeyPressed(TH_KEY_D)) Graphics::cam_stuff.translation.x += 2.f * ts;
		}

		m_Framebuffer->Bind();

		glClearColor(0.0f, 0.3f, 0.5f, 1.f);
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

								SceneSerializer serializer(m_ActiveScene.get());
								serializer.Deserialize(filepath);

							}
						}
						if (ImGui::MenuItem("Save", "Ctrl+S"))
						{
							std::string filepath = FileDialogs::SaveFile("Thomas Scene\0*.json\0");
							if (!filepath.empty())
							{
								
								SceneSerializer serializer(m_ActiveScene.get());

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
					if (temp_ar > Graphics::cam_stuff.c_ar) {
						Graphics::m_ViewportSize.y = viewportPanelsize.y;
						Graphics::m_ViewportSize.x = viewportPanelsize.y * Graphics::cam_stuff.c_ar;
					}
					// If aspect ratio is smaller than the camera aspect ratio
					else if (temp_ar < Graphics::cam_stuff.c_ar) {
						Graphics::m_ViewportSize.x = viewportPanelsize.x;
						Graphics::m_ViewportSize.y = viewportPanelsize.x / Graphics::cam_stuff.c_ar; // Change the height
					}
					else {
						Graphics::m_ViewportSize.x = viewportPanelsize.x;
						Graphics::m_ViewportSize.y = viewportPanelsize.y;
					}
					vp_pos.x = (ImGui::GetContentRegionAvail().x - Graphics::m_ViewportSize.x) / 2.f;	 // Screen offset X
					vp_pos.y = (ImGui::GetContentRegionAvail().y - Graphics::m_ViewportSize.y) / 2.f + button_offset.y + button_size.y + 2.f;
					m_OldViewport.x = viewportPanelsize.x;
					m_OldViewport.y = viewportPanelsize.x;
				}
				ImVec2 temp_pos;
				temp_pos.x = vp_pos.x;
				temp_pos.y = vp_pos.y;
				ImGui::SetCursorPos(temp_pos); // Set offset for the render screen

				uintptr_t textureID = m_Framebuffer->GetColorAttachmentID();
				ImGui::Image((ImTextureID)textureID, ImVec2{ Graphics::m_ViewportSize.x,Graphics::m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

				Graphics::cam_stuff.Camera2D_Update();

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
						if (((Viewport_CursX > trans_stuff.screen_min.x && Viewport_CursX<trans_stuff.screen_max.x && Viewport_CursY>trans_stuff.screen_min.y 
							&& Viewport_CursY < trans_stuff.screen_max.y) && Input::IsMouseButtonPressed(0) && trans_stuff.transform_Lock == false) && 
							(Viewport_CursX > -(Graphics::m_ViewportSize.x / 2.f) && Viewport_CursX < (Graphics::m_ViewportSize.x / 2.f) && Viewport_CursY > -(Graphics::m_ViewportSize.y / 2.f)
							&& Viewport_CursY < (Graphics::m_ViewportSize.x / 2.f))) {
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
						}

						if (objs.GetID() == Graphics::sel) {
							if (trans_stuff.mouse_following == TRUE) {
								glm::vec2 move = glm::vec2(Viewport_CursX, Viewport_CursY);
								glm::vec2 A = glm::vec2(0, -1.f);
								glm::vec2 B = glm::vec2(trans_stuff.world_to_screen(move));
								B.x -= trans_stuff.translation.x;
								B.y -= trans_stuff.translation.y;
								float dot_product = glm::dot(A, B);
								float angle = acos(dot_product / (glm::length(A) * glm::length(B)));
								float degree = (angle / static_cast<float>(M_PI)) * 180.f;
								if ((B.x + trans_stuff.translation.x) < trans_stuff.translation.x)
									degree *= -1;
								trans_stuff.rotation = degree;
								Graphics::cam_stuff.rotation = (degree * -1.f);
							}

							// GIZMO Control
							static ImGuizmo::OPERATION current_Operation(ImGuizmo::TRANSLATE);
							if (Input::IsKeyPressed(TH_KEY_1)) current_Operation = ImGuizmo::TRANSLATE;
							if (Input::IsKeyPressed(TH_KEY_2)) current_Operation = ImGuizmo::ROTATE;
							if (Input::IsKeyPressed(TH_KEY_3)) current_Operation = ImGuizmo::SCALE;

							ImGuizmo::SetOrthographic(true);
							ImGuizmo::SetDrawlist();
							ImGuizmo::SetRect(ImGui::GetWindowPos().x + vp_pos.x, ImGui::GetWindowPos().y + vp_pos.y, (float)ImGui::GetWindowWidth() - (vp_pos.x * 2), 
								(float)ImGui::GetWindowHeight() - (vp_pos.y * 2) + button_size.y + 2.f + button_offset.y);
							const glm::mat4 cameraView = glm::mat4(Graphics::cam_stuff.view_xform);
							const glm::mat4 cameraProjection = glm::mat4(Graphics::cam_stuff.projection);
							glm::mat4 transform = trans_stuff.getTransform();
							ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
								current_Operation, ImGuizmo::LOCAL, glm::value_ptr(transform));

							if (ImGuizmo::IsUsing()) {
								if (m_ActiveScene->m_Registry->HasComponent<Additional_Parts>(e.first)) {
									std::vector<glm::vec2> parts_Offset;
									auto& parts_data = objs.GetComponent<Additional_Parts>();

									// Calculating offset for the additional parts
									for (int i{}; i < parts_data.parts_Transform.size(); i++) {
										// Rotate the additional parts back
										glm::mat3 inv_rotation = { cos(-trans_stuff.rotation), -sin(-trans_stuff.rotation), 0, sin(-trans_stuff.rotation), cos(-trans_stuff.rotation), 0, 0, 0, 1 };
										glm::vec2 inv_Pos = glm::vec2(inv_rotation * glm::vec3(parts_data.parts_Transform[i].translation, 1.f));
										glm::vec2 temp_Offset = trans_stuff.translation - inv_Pos;
										parts_Offset.push_back(temp_Offset);
									}
									glm::vec2 box_Offset = trans_stuff.translation - box_stuff.box_trans.translation;
									glm::vec3 matrix_Translation, matrix_Rotation, matrix_Scale;
									ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform), glm::value_ptr(matrix_Translation),
										glm::value_ptr(matrix_Rotation), glm::value_ptr(matrix_Scale));
									glm::vec3 delta_rot = matrix_Rotation - glm::vec3(trans_stuff.rotation, 1.f, 0.f);
									float rad = (float)(delta_rot.z * (M_PI / 180.f));
									trans_stuff.translation = glm::vec2(matrix_Translation);
									trans_stuff.scaling = glm::vec2(matrix_Scale);
									trans_stuff.rotation = rad;
									box_stuff.box_trans.translation = trans_stuff.translation - box_Offset;
									for (int j{}; j < parts_data.parts_Transform.size(); j++) {
										glm::vec2 temp_trans = trans_stuff.translation - parts_Offset[j];
										glm::mat3 temp_rot_matrix = { cos(-trans_stuff.rotation), sin(-trans_stuff.rotation), 0, -sin(-trans_stuff.rotation), cos(-trans_stuff.rotation), 0, 0, 0, 1 };
										parts_data.parts_Transform[j].translation = glm::vec2(temp_rot_matrix * glm::vec3(temp_trans, 1.f));
										parts_data.parts_Transform[j].rotation = trans_stuff.rotation;
									}
								}
								else {
									glm::vec2 box_Offset = trans_stuff.translation - box_stuff.box_trans.translation;
									glm::vec3 matrix_Translation, matrix_Rotation, matrix_Scale;
									ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform), glm::value_ptr(matrix_Translation),
										glm::value_ptr(matrix_Rotation), glm::value_ptr(matrix_Scale));
									glm::vec3 delta_rot = matrix_Rotation - glm::vec3(trans_stuff.rotation, 1.f, 0.f);
									float rad = (float)(delta_rot.z * (M_PI / 180.f));
									trans_stuff.translation = glm::vec2(matrix_Translation);
									trans_stuff.scaling = glm::vec2(matrix_Scale);
									trans_stuff.rotation = rad;
									box_stuff.box_trans.translation = trans_stuff.translation - box_Offset;
								}
							}
						}

						if (!Input::IsMouseButtonPressed(0)) {
							Graphics::obj_clicked = false;
							Graphics::obj_counter = 0;
						}
					}
				}
				ImGui::End();
				ImGui::PopStyleVar();
				ImGui::End();
			}
	}

	void EditorLayer::OnEvent(Thomas::Event& e)
	{
	}


}
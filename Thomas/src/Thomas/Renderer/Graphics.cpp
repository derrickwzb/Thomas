///*!*************************************************************************
//\file:								Graphics.cpp
//\author:						Xie Zhi Xiong
//\par DP email:			xiong.x@digipen.edu
//\par Course:				CSD2125
//\par Programming:	CSD2400 Game project
//\date:							31/10/2022
//\brief:
//	This file contains the definitions of the member functions for
//	Graphics class.
//****************************************************************************/
//// Includes
#include "thpch.h"
//#include "Thomas/Renderer/Graphics.h"
//#include "Thomas/Core/application.h"
//#include "GL/glew.h"
//#include "GLFW/glfw3.h"
//#include <math.h>
//#include "Thomas/Core/Input.h"
//#include "Thomas/Renderer/Asset_Manager.h"
////#include "Thomas/Scene/Entity.h"
//#include "Thomas/Renderer/Box_collider.h"
//#include "Thomas/Renderer/Transform.h"
//#include "Thomas/Renderer/Texture.h"
//#include "Platform/Windows/WindowsInput.h"
//#include "Thomas/Core/KeyCodes.h"	
//#include <sstream>
////#define _USE_MATH_DEFINES
//
//using namespace std;
//
//namespace Thomas {
//
//	// Init()
//	// 1. Clear the background color & set entire viewport
//	// 2. Initialize the Camera
//	// 3. Initialize the Fonts
//	void Graphics::init() {
//		glClearColor(1.f, 1.f, 1.f, 1.f);
//		Thomas::Application& app = Thomas::Application::Get();
//		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
//		glfwGetWindowSize(window, &width, &height);
//		glViewport(0, 0, width, height);
//		cam_stuff.Camera2D_Init();
//		team_font.font_type = stash.Font_Storage["Freedom-10eM.ttf"];
//		fps_font.font_type = stash.Font_Storage["FFF_Tusj.ttf"];
//		fps_font.Fonts_init();
//		team_font.Fonts_init();
//	}
//
//	// Update(std::vector<Thomas::EntityID> allentity)
//	// 1. Update the mouse cursor position 
//	// 2. Update the Texture Component
//	// 3. Update the Transform Component
//	// 4. Update the Box_collider Component
//	// 5. Allow mouse picking of the objects
//	void Graphics::update(std::vector<Thomas::EntityID> allentity) {
//
//		auto start = std::chrono::steady_clock::now();
//
//		Thomas::Application& app = Thomas::Application::Get();
//		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
//		glfwGetCursorPos(window, &xpos, &ypos);
//		GLdouble CursorX, CursorY;
//		CursorX = xpos - width / 2;
//		CursorY = (ypos - height / 2) * -1.f;
//
//		//// Loop thru all entity 
//		//for (auto const& entity : allentity) {
//		//	// Texture Component Handling 
//		//	if (Thomas::factory.HasComponent<Texture>(entity)) {
//		//		auto tex_data = Thomas::factory.GetComponent<Texture>(entity);
//		//		auto mesh_data = Thomas::factory.GetComponent<Mesh>(entity);
//		//		auto trans_data = Thomas::factory.GetComponent<Transform>(entity);
//
//		//			if (tex_data.text_file == 1) {
//		//				tex_data.texid = stash.Text_Storage["bigboss.png"];
//		//			}
//		//			else if (tex_data.text_file == 2) {
//		//				tex_data.texid = stash.Text_Storage["background.png"];
//		//			}
//		//			else if (tex_data.text_file == 3) {
//		//				tex_data.texid = stash.Text_Storage["sprite.png"];
//		//			}
//		//			if (tex_data.animation_but == 1) {
//		//				tex_data.speed = 10;
//		//				text_sys.animation(11, &tex_data.counter, tex_data.speed, &tex_data.switch_text, mesh_data.vbo_hdl);
//		//			}
//
//		//		Thomas::factory.UpdateComponent<Texture>(entity, tex_data);
//		//		Thomas::factory.UpdateComponent<Mesh>(entity, mesh_data);
//		//		Thomas::factory.UpdateComponent<Transform>(entity, trans_data);
//		//	}
//
//		//	// Transform Component Handling
//		//	if (Thomas::factory.HasComponent<Transform>(entity)) {
//		//		auto trans_data = Thomas::factory.GetComponent<Transform>(entity);
//
//		//			trans_data.minmax(width, height);
//		//			cam_stuff.Camera2D_Update();
//		//			if (Input::IsKeyPressed(TH_KEY_I))
//		//				cam_stuff.translation.y -= (0.1f * Thomas::Application::timestep);
//		//			if (Input::IsKeyPressed(TH_KEY_J))
//		//				cam_stuff.translation.x -= (0.1f * Thomas::Application::timestep);
//		//			if (Input::IsKeyPressed(TH_KEY_K))
//		//				cam_stuff.translation.y += (0.1f * Thomas::Application::timestep);
//		//			if (Input::IsKeyPressed(TH_KEY_L))
//		//				cam_stuff.translation.x += (0.1f * Thomas::Application::timestep);
//		//			trans_data.compute_mdl_to_ndc_xform();
//		//			trans_data.mdl_to_ndc_xform = cam_stuff.world_to_ndc_xform * trans_data.mdl_to_ndc_xform;
//
//		//		Thomas::factory.UpdateComponent<Transform>(entity, trans_data);
//		//	}
//
//		//	// Box collider Component Handling
//		//	if (Thomas::factory.HasComponent<Box_collider>(entity)) {
//		//		auto trans_data = Thomas::factory.GetComponent<Transform>(entity);
//		//		auto box_data = Thomas::factory.GetComponent<Box_collider>(entity);
//
//		//			box_data.box_trans.minmax(width, height);
//		//			box_data.box_trans.rotation = trans_data.rotation;
//		//			box_data.box_trans.compute_mdl_to_ndc_xform();
//		//			box_data.box_trans.mdl_to_ndc_xform = cam_stuff.world_to_ndc_xform * box_data.box_trans.mdl_to_ndc_xform;
//
//		//			if (box_data.reset_but == 1) {
//		//				box_data.box_trans.translation = trans_data.translation;
//		//				box_data.box_trans.scaling = trans_data.scaling;
//		//				box_data.reset_but = 0;
//		//			}
//
//		//		Thomas::factory.UpdateComponent<Box_collider>(entity, box_data);
//		//	}
//		//	if (Input::IsMouseButtonPressed(0))
//		//		std::cout << CursorX << "            " << CursorY << std::endl;
//		//	// Mouse dragging for objects
//		//	if (Thomas::factory.HasComponent<Transform>(entity)) {
//		//		auto trans_data = Thomas::factory.GetComponent<Transform>(entity);
//		//		auto box_data = Thomas::factory.GetComponent<Box_collider>(entity);
//
//		//		if ((CursorX > trans_data.min.x && CursorX<trans_data.max.x && CursorY>trans_data.min.y && CursorY < trans_data.max.y) && Input::IsMouseButtonPressed(0) && obj_clicked == 0) {
//		//			sel = entity;
//		//			obj_clicked = 1;
//		//			//std::cout << sel << std::endl;
//		//		}
//
//		//		if ((obj_clicked != 0) && (entity == sel)) {
//		//			glm::vec2 move = glm::vec2(CursorX, CursorY);
//		//			glm::vec2 diff_dist = glm::vec2(trans_data.translation.x - box_data.box_trans.translation.x, trans_data.translation.y - box_data.box_trans.translation.y);
//		//			trans_data.translation.x = (move.x / (width / 2) * 2.7);
//		//			trans_data.translation.y = -(move.y / (height / 2) * 2);
//		//			box_data.box_trans.translation.x = (move.x / (width / 2) * 2.7) - diff_dist.x;
//		//			box_data.box_trans.translation.y = -(move.y / (height / 2) * 2) - diff_dist.y;
//		//		}
//		//		if (!Input::IsMouseButtonPressed(0))
//		//			obj_clicked = 0;
//
//		//		Thomas::factory.UpdateComponent<Transform>(entity, trans_data);
//		//		Thomas::factory.UpdateComponent<Box_collider>(entity, box_data);
//		//	}
//
//		//}
//
//		auto stop = std::chrono::steady_clock::now();
//		std::chrono::duration<double> duration = (stop - start);
//		Graphic_update_timetaken = duration.count();
//	}
//
//	// draw(std::vector<Thomas::EntityID> allentity)
//	// 1. Set the background to the preset color 
//	// 2. Render the fonts
//	// 3. Render the objects
//	// 4. Render the Box collider
//	void Graphics::draw(std::vector<Thomas::EntityID> allentity) {
//		auto start = std::chrono::steady_clock::now();
//
//		/*glClear(GL_COLOR_BUFFER_BIT);
//		std::stringstream fps_text;
//		fps_text << "FPS: " << Application::fps;
//		fps_font.RenderText(fps_text.str(), 0.f, 1000.f, 1.5f, glm::vec3(0.0f, 1.0f, 1.0f));
//		team_font.RenderText("THOMAS ENGINE", 1250.f, 1000.f, 1.5f, glm::vec3(0.0f, 1.0f, 1.0f));
//		for (auto const& entity : allentity) {
//			if (Thomas::factory.HasComponent<Mesh>(entity)) {
//				auto shader_data = Thomas::factory.GetComponent<Shader_manager>(entity);
//				auto trans_data = Thomas::factory.GetComponent<Transform>(entity);
//				auto tex_data = Thomas::factory.GetComponent<Texture>(entity);
//				auto mesh_data = Thomas::factory.GetComponent<Mesh>(entity);
//				auto box_data = Thomas::factory.GetComponent<Box_collider>(entity);
//
//					int texture_toggle{};
//					shader_data.shdr_pgm.Use();
//					GLint uniform_var_loc1 = glGetUniformLocation(shader_data.shdr_pgm.GetHandle(), "uModelToNDC");
//					if (uniform_var_loc1 >= 0) {
//						glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, glm::value_ptr(trans_data.mdl_to_ndc_xform));
//					}
//					else {
//						std::cout << "Uniform variable doesn't exist!!!\n";
//						std::exit(EXIT_FAILURE);
//					}
//					if (tex_data.text_file != 0)
//						texture_toggle = 1;
//					else
//						texture_toggle = 0;
//					GLint txttog = glGetUniformLocation(shader_data.shdr_pgm.GetHandle(), "TEXT_tog");
//					glUniform1i(txttog, texture_toggle);
//					GLint color = glGetUniformLocation(shader_data.shdr_pgm.GetHandle(), "tri_color");
//					glUniform3fv(color, 1, glm::value_ptr(glm::vec3(0, 0, 0)));
//					GLuint tex_loc = glGetUniformLocation(shader_data.shdr_pgm.GetHandle(), "uTex2d");
//					glUniform1i(tex_loc, 1);
//					glBindTextureUnit(1, tex_data.texid);
//					glEnable(GL_BLEND);
//					glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
//					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//					glBindVertexArray(mesh_data.vaoid);
//					glDrawElements(mesh_data.primitive_type, mesh_data.idx_elem_cnt, GL_UNSIGNED_SHORT, NULL);
//					glBindVertexArray(0);
//					shader_data.shdr_pgm.UnUse();
//
//					if (box_data.box_tog == 1) {
//						box_data.box_shader.shdr_pgm.Use();
//						GLint uniform_var_loc1 = glGetUniformLocation(box_data.box_shader.shdr_pgm.GetHandle(), "uModelToNDC");
//						if (uniform_var_loc1 >= 0) {
//							glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, glm::value_ptr(box_data.box_trans.mdl_to_ndc_xform));
//						}
//						else {
//							std::cout << "Uniform variable doesn't exist!!!\n";
//							std::exit(EXIT_FAILURE);
//						}
//						GLint color = glGetUniformLocation(box_data.box_shader.shdr_pgm.GetHandle(), "tri_color");
//						glUniform3fv(color, 1, glm::value_ptr(glm::vec3(0, 0, 0)));
//
//						if (box_data.collision_detected == 0)
//							glUniform3fv(color, 1, glm::value_ptr(glm::vec3(0, 1, 0)));
//						else
//							glUniform3fv(color, 1, glm::value_ptr(glm::vec3(1, 0, 0)));
//						glBindVertexArray(box_data.box_mesh.vaoid);
//						glLineWidth(5.f);
//						glDrawElements(GL_LINE_STRIP, box_data.box_mesh.idx_elem_cnt, GL_UNSIGNED_SHORT, NULL);
//						glBindVertexArray(0);
//						box_data.box_shader.shdr_pgm.UnUse();
//					}
//
//				Thomas::factory.UpdateComponent<Shader_manager>(entity, shader_data);
//				Thomas::factory.UpdateComponent<Transform>(entity, trans_data);
//				Thomas::factory.UpdateComponent<Texture>(entity, tex_data);
//				Thomas::factory.UpdateComponent<Mesh>(entity, mesh_data);
//				Thomas::factory.UpdateComponent<Box_collider>(entity, box_data);
//			}
//		}*/
//		auto stop = std::chrono::steady_clock::now();
//		std::chrono::duration<double> duration = (stop - start);
//		Graphic_draw_timetaken = duration.count();
//	}
//
//	// cleanup()
//	void Graphics::cleanup() {
//	}
//
//}

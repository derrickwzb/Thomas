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
#include "Thomas/Renderer/Graphics.h"
#include "Thomas/Core/application.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <math.h>
#include "Thomas/Renderer/Asset_Manager.h"
#include "Thomas/Renderer/Box_collider.h"
#include "Thomas/Renderer/Transform.h"
#include "Thomas/Renderer/Texture.h"
#include "Thomas/Renderer/Texture_system.h"
#include "Thomas/Renderer/Mesh_manager.h"
#include <sstream>
using namespace std;

namespace Thomas {

	// Init()
	// 1. Clear the background color & set entire viewport
	// 2. Initialize the Camera
	// 3. Initialize the Fonts
	void Graphics::init() {
		glClearColor(1.f, 1.f, 1.f, 1.f);
		Thomas::Application& app = Thomas::Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
		glfwGetWindowSize(window, &width, &height);
		glViewport(0, 0, width, height);
		cam_stuff.Camera2D_Init();
	}

	// Draw for normal entity
	void Graphics::draw(Shader_manager shdr, Mesh mesh, Transform trans) {
		int texture_toggle{};
		shdr.shdr_pgm.Use();
		GLint uniform_var_loc1 = glGetUniformLocation(shdr.shdr_pgm.GetHandle(), "uModelToNDC");
		if (uniform_var_loc1 >= 0) {
			glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, glm::value_ptr(trans.mdl_to_ndc_xform));
		}
		else {
			TH_CORE_WARN("Uniform variable doesn't exist!!!");
			std::exit(EXIT_FAILURE);
		}
		GLint uniform_var_loc2 = glGetUniformLocation(shdr.shdr_pgm.GetHandle(), "uWorldToNDC");
		if (uniform_var_loc2 >= 0) {
			glUniformMatrix3fv(uniform_var_loc2, 1, GL_FALSE, glm::value_ptr(cam_stuff.world_to_ndc_xform));
		}
		else {
			TH_CORE_WARN("Uniform variable doesn't exist!!!");
			std::exit(EXIT_FAILURE);
		}
		GLint uniform_z_axis = glGetUniformLocation(shdr.shdr_pgm.GetHandle(), "z_axis");
		if (uniform_z_axis >= 0) {
			glUniform1f(uniform_z_axis, trans.z_axis);
		}
		else {
			TH_CORE_WARN("Uniform variable doesn't exist!!!");
			std::exit(EXIT_FAILURE);
		}
		GLint uniform_alpha = glGetUniformLocation(shdr.shdr_pgm.GetHandle(), "alpha_val");
		if (uniform_alpha >= 0) {
			glUniform1f(uniform_alpha, trans.alpha_val);
		}
		else {
			TH_CORE_WARN("Uniform variable doesn't exist!!!");
			std::exit(EXIT_FAILURE);
		}
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		GLint txttog = glGetUniformLocation(shdr.shdr_pgm.GetHandle(), "TEXT_tog");
		glUniform1i(txttog, texture_toggle);
		GLint tone = glGetUniformLocation(shdr.shdr_pgm.GetHandle(), "tri_color");
		glUniform3fv(tone, 1, glm::value_ptr(trans.color));
		glBindVertexArray(mesh.vaoid);
		glDrawElements(mesh.primitive_type, static_cast<GLsizei>(mesh.idx_elem_cnt), GL_UNSIGNED_SHORT, NULL);
		glBindVertexArray(0);
		shdr.shdr_pgm.UnUse();
	}

	// Draw for textured entity
	void Graphics::draw(Shader_manager shdr, Mesh mesh, Transform trans, Texture text) {
		int texture_toggle{};
		shdr.shdr_pgm.Use();
		GLint uniform_var_loc1 = glGetUniformLocation(shdr.shdr_pgm.GetHandle(), "uModelToNDC");
		if (uniform_var_loc1 >= 0) {
			glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, glm::value_ptr(trans.mdl_to_ndc_xform));
		}
		else {
			TH_CORE_WARN("Uniform variable doesn't exist!!!");
			std::exit(EXIT_FAILURE);
		}
		GLint uniform_var_loc2 = glGetUniformLocation(shdr.shdr_pgm.GetHandle(), "uWorldToNDC");
		if (uniform_var_loc2 >= 0) {
			glUniformMatrix3fv(uniform_var_loc2, 1, GL_FALSE, glm::value_ptr(cam_stuff.world_to_ndc_xform));
		}
		else {
			TH_CORE_WARN("Uniform variable doesn't exist!!!");
			std::exit(EXIT_FAILURE);
		}
		GLint uniform_z_axis = glGetUniformLocation(shdr.shdr_pgm.GetHandle(), "z_axis");
		if (uniform_z_axis >= 0) {
			glUniform1f(uniform_z_axis, trans.z_axis);
		}
		else {
			TH_CORE_WARN("Uniform variable doesn't exist!!!");
			std::exit(EXIT_FAILURE);
		}
		GLint uniform_alpha = glGetUniformLocation(shdr.shdr_pgm.GetHandle(), "alpha_val");
		if (uniform_alpha >= 0) {
			glUniform1f(uniform_alpha, trans.alpha_val);
		}
		else {
			TH_CORE_WARN("Uniform variable doesn't exist!!!");
			std::exit(EXIT_FAILURE);
		}
		if (text.text_file != 0)
			texture_toggle = 1;
		else
			texture_toggle = 0;
		GLint txttog = glGetUniformLocation(shdr.shdr_pgm.GetHandle(), "TEXT_tog");
		glUniform1i(txttog, texture_toggle);
		GLint tone = glGetUniformLocation(shdr.shdr_pgm.GetHandle(), "tri_color");
		glUniform3fv(tone, 1, glm::value_ptr(trans.color));
		GLuint tex_loc = glGetUniformLocation(shdr.shdr_pgm.GetHandle(), "uTex2d");
		glUniform1i(tex_loc, 1);
		glBindTextureUnit(1, text.texid);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindVertexArray(mesh.vaoid);
		glDrawElements(mesh.primitive_type, static_cast<GLsizei>(mesh.idx_elem_cnt), GL_UNSIGNED_SHORT, NULL);
		glBindVertexArray(0);
		shdr.shdr_pgm.UnUse();
	}

	// Draw for bounding box 
	void Graphics::draw_box(Box_collider box_renderer, glm::vec3 on_color, glm::vec3 off_color) {
		if (box_renderer.box_tog == 1) {
			box_renderer.box_shader.shdr_pgm.Use();
			GLint uniform_var_loc1 = glGetUniformLocation(box_renderer.box_shader.shdr_pgm.GetHandle(), "uModelToNDC");
			if (uniform_var_loc1 >= 0) {
				glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, glm::value_ptr(box_renderer.box_trans.mdl_to_ndc_xform));
			}
			else {
				TH_CORE_WARN("Uniform variable doesn't exist!!!");
				std::exit(EXIT_FAILURE);
			}

			GLint uniform_var_loc2 = glGetUniformLocation(box_renderer.box_shader.shdr_pgm.GetHandle(), "uWorldToNDC");
			if (uniform_var_loc2 >= 0) {
				glUniformMatrix3fv(uniform_var_loc2, 1, GL_FALSE, glm::value_ptr(cam_stuff.world_to_ndc_xform));
			}
			else {
				TH_CORE_WARN("Uniform variable doesn't exist!!!");
				std::exit(EXIT_FAILURE);
			}

			GLint uniform_z_axis = glGetUniformLocation(box_renderer.box_shader.shdr_pgm.GetHandle(), "z_axis");
			if (uniform_z_axis >= 0) {
				glUniform1f(uniform_z_axis, box_renderer.box_trans.z_axis);
			}
			else {
				TH_CORE_WARN("Uniform variable doesn't exist!!!");
				std::exit(EXIT_FAILURE);
			}

			GLint uniform_alpha = glGetUniformLocation(box_renderer.box_shader.shdr_pgm.GetHandle(), "alpha_val");
			if (uniform_alpha >= 0) {
				glUniform1f(uniform_alpha, box_renderer.box_trans.alpha_val);
			}
			else {
				TH_CORE_WARN("Uniform variable doesn't exist!!!");
				std::exit(EXIT_FAILURE);
			}
			glEnable(GL_DEPTH_TEST);
			GLint color = glGetUniformLocation(box_renderer.box_shader.shdr_pgm.GetHandle(), "tri_color");
			glUniform3fv(color, 1, glm::value_ptr(glm::vec3(0, 0, 0)));

			if (box_renderer.collision_detected == 0)
				glUniform3fv(color, 1, glm::value_ptr(off_color));
			else
				glUniform3fv(color, 1, glm::value_ptr(on_color));
			glBindVertexArray(box_renderer.box_mesh.vaoid);
			glLineWidth(5.f);
			glDrawElements(GL_LINE_STRIP, static_cast<GLsizei>(box_renderer.box_mesh.idx_elem_cnt), GL_UNSIGNED_SHORT, NULL);
			glBindVertexArray(0);
			box_renderer.box_shader.shdr_pgm.UnUse();
		}
	}

	// cleanup()
	void Graphics::cleanup() {
	}

}

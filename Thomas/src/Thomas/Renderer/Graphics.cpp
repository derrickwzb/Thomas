#include "thpch.h"
#include "Thomas/Renderer/Graphics.h"
#include "Thomas/Core/application.h"

#include "GLFW/glfw3.h"
#include <math.h>
#include <stb_image.h>
#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION
using namespace std;


namespace Thomas {

	void Graphics::init() {
		// Clear background & set viewport
		glClearColor(1.f, 1.f, 1.f, 1.f);
		Thomas::Application& app = Thomas::Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
		glfwGetWindowSize(window, &width, &height);
		glViewport(0, 0, width, height);
		cam_stuff.Camera2D_Init();
		/*stash.Load_Texture();
		stash.Load_Font();
		stash.Load_Shader();*/
		/*font_stuff.Fonts_init();*/
		std::cout << Thomas::stash.Text_Storage["bigboss.png"] << endl;
		
	}


	void Graphics::update(std::vector<Thomas::Entity> allentity) {
		// Update mouse cursor
		Thomas::Application& app = Thomas::Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
		glfwGetCursorPos(window, &xpos, &ypos);
		GLdouble CursorX, CursorY;
		CursorX = xpos - width / 2;
		CursorY = (ypos - height / 2) * -1.f;

		//temp_physics();
		for (auto const& entity : allentity) {

			// TEXTURE
			if (Thomas::factory.HasComponent<Texture>(entity)) {
				auto tex_data = Thomas::factory.GetComponent<Texture>(entity);
				auto mesh_data = Thomas::factory.GetComponent<Mesh>(entity);
				auto trans_data = Thomas::factory.GetComponent<Transform>(entity);


				if (tex_data.text_file == 1) {
					tex_data.texid = stash.Text_Storage["bigboss.png"];
				}
				else if (tex_data.text_file == 2) {
					tex_data.texid = stash.Text_Storage["background.png"];
				}
				else if (tex_data.text_file == 3) {
					tex_data.texid = stash.Text_Storage["sprite.png"];
				}
				trans_data.minmax(width, height);

				// Animation
				if (tex_data.animation_but == 1) {
					text_sys.animation(11, &tex_data.counter, &tex_data.switch_text, mesh_data.vbo_hdl);
				}

				Thomas::factory.ChangeComponent<Texture>(entity, tex_data);
				Thomas::factory.ChangeComponent<Mesh>(entity, mesh_data);
				Thomas::factory.ChangeComponent<Transform>(entity, trans_data);
			}

			// TRANSFORM
			if (Thomas::factory.HasComponent<Transform>(entity)) {
				auto trans_data = Thomas::factory.GetComponent<Transform>(entity);

				if (cam_stuff.cam_mode == 1)
					cam_stuff.Camera2D_Update();
				if (cam_stuff.cam_mode == 2)
					cam_stuff.Camera2D_Update(trans_data);
				if (cam_stuff.cam_mode == 0) {
					cam_stuff.translation = trans_data.translation;
					cam_stuff.Camera2D_compute_world_to_ndc_xform();
				}
				trans_data.compute_mdl_to_ndc_xform();
				trans_data.mdl_to_ndc_xform = cam_stuff.world_to_ndc_xform * trans_data.mdl_to_ndc_xform;

				Thomas::factory.ChangeComponent<Transform>(entity, trans_data);
			}

			// BOUNDING BOX
			if (Thomas::factory.HasComponent<Box_collider>(entity)) {
				auto cam_data = Thomas::factory.GetComponent<Camera>(entity);
				auto trans_data = Thomas::factory.GetComponent<Transform>(entity);
				auto box_data = Thomas::factory.GetComponent<Box_collider>(entity);

				if (cam_data.cam_mode == 0) {
					cam_data.translation = box_data.box_trans.translation;
					cam_data.Camera2D_compute_world_to_ndc_xform();
				}
				box_data.box_trans.rotation = trans_data.rotation;
				box_data.box_trans.compute_mdl_to_ndc_xform();
				box_data.box_trans.mdl_to_ndc_xform = cam_data.world_to_ndc_xform * box_data.box_trans.mdl_to_ndc_xform;

				if (box_data.reset_but == 1) {
					box_data.box_trans.translation = trans_data.translation;
					box_data.box_trans.scaling = trans_data.scaling;
					box_data.reset_but = 0;
				}

				Thomas::factory.ChangeComponent<Box_collider>(entity, box_data);
			}

			// Using mouse to drag things around (Collision)
			if (Thomas::factory.HasComponent<Transform>(entity)) {
				auto trans_data = Thomas::factory.GetComponent<Transform>(entity);
				auto box_data = Thomas::factory.GetComponent<Box_collider>(entity);

				if ((CursorX > trans_data.min.x && CursorX<trans_data.max.x && CursorY>trans_data.min.y && CursorY < trans_data.max.y) && ImGui::IsMouseDown(0) && obj_clicked == 0) {
					sel = entity;
					obj_clicked = 1;
					std::cout << sel << std::endl;
				}

				if (obj_clicked != 0) {
					glm::vec2 move = glm::vec2(CursorX, CursorY);
					glm::vec2 diff_dist = glm::vec2(trans_data.translation.x - box_data.box_trans.translation.x, trans_data.translation.y - box_data.box_trans.translation.y);
					trans_data.translation.x = (move.x / (width / 2));
					trans_data.translation.y = -(move.y / (height / 2));
					box_data.box_trans.translation.x = (move.x / (width / 2)) - diff_dist.x;
					box_data.box_trans.translation.y = -(move.y / (height / 2)) - diff_dist.y;
				}
				if (ImGui::IsMouseReleased(0))
					obj_clicked = 0;

				Thomas::factory.ChangeComponent<Transform>(entity, trans_data);
				Thomas::factory.ChangeComponent<Box_collider>(entity, box_data);
			}
		}
	}


	void Graphics::draw(std::vector<Thomas::Entity> allentity) {
		glClear(GL_COLOR_BUFFER_BIT);
		/*font_stuff.RenderText("Hello", 500.0f, 300.f, 1.5f, glm::vec3(0.0f, 1.0f, 1.0f));*/
		for (auto const& entity : allentity) {

			if (Thomas::factory.HasComponent<Mesh>(entity)) {

				auto shader_data = Thomas::factory.GetComponent<Shader_manager>(entity);
				auto trans_data = Thomas::factory.GetComponent<Transform>(entity);
				auto tex_data = Thomas::factory.GetComponent<Texture>(entity);
				auto mesh_data = Thomas::factory.GetComponent<Mesh>(entity);
				auto box_data = Thomas::factory.GetComponent<Box_collider>(entity);

				int texture_toggle{};
				shader_data.shdr_pgm.Use();
				GLint uniform_var_loc1 = glGetUniformLocation(shader_data.shdr_pgm.GetHandle(), "uModelToNDC");
				if (uniform_var_loc1 >= 0) {
					glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, glm::value_ptr(trans_data.mdl_to_ndc_xform));
				}
				else {
					std::cout << "Uniform variable doesn't exist!!!\n";
					std::exit(EXIT_FAILURE);
				}
				if (tex_data.text_file != 0)
					texture_toggle = 1;
				else
					texture_toggle = 0;
				GLint txttog = glGetUniformLocation(shader_data.shdr_pgm.GetHandle(), "TEXT_tog");
				glUniform1i(txttog, texture_toggle);
				GLint color = glGetUniformLocation(shader_data.shdr_pgm.GetHandle(), "tri_color");
				glUniform3fv(color, 1, glm::value_ptr(glm::vec3(0, 0, 0)));
				GLuint tex_loc = glGetUniformLocation(shader_data.shdr_pgm.GetHandle(), "uTex2d");
				glUniform1i(tex_loc, 1);
				glBindTextureUnit(1, tex_data.texid);
				glEnable(GL_BLEND);
				glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindVertexArray(mesh_data.vaoid);
				glDrawElements(mesh_data.primitive_type, mesh_data.idx_elem_cnt, GL_UNSIGNED_SHORT, NULL);
				glBindVertexArray(0);
				shader_data.shdr_pgm.UnUse();

				if (box_data.box_tog == 1) {
					box_data.box_shader.shdr_pgm.Use();
					GLint uniform_var_loc1 = glGetUniformLocation(box_data.box_shader.shdr_pgm.GetHandle(), "uModelToNDC");
					if (uniform_var_loc1 >= 0) {
						glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, glm::value_ptr(box_data.box_trans.mdl_to_ndc_xform));
					}
					else {
						std::cout << "Uniform variable doesn't exist!!!\n";
						std::exit(EXIT_FAILURE);
					}
					GLint color = glGetUniformLocation(box_data.box_shader.shdr_pgm.GetHandle(), "tri_color");
					glUniform3fv(color, 1, glm::value_ptr(glm::vec3(0, 0, 0)));

					if (box_data.collision_detected == 0)
						glUniform3fv(color, 1, glm::value_ptr(glm::vec3(0, 1, 0)));
					else
						glUniform3fv(color, 1, glm::value_ptr(glm::vec3(1, 0, 0)));
					glBindVertexArray(box_data.box_mesh.vaoid);
					glLineWidth(5.f);
					glDrawElements(GL_LINE_STRIP, box_data.box_mesh.idx_elem_cnt, GL_UNSIGNED_SHORT, NULL);
					glBindVertexArray(0);
					box_data.box_shader.shdr_pgm.UnUse();
				}

				Thomas::factory.ChangeComponent<Shader_manager>(entity, shader_data);
				Thomas::factory.ChangeComponent<Transform>(entity, trans_data);
				Thomas::factory.ChangeComponent<Texture>(entity, tex_data);
				Thomas::factory.ChangeComponent<Mesh>(entity, mesh_data);
				Thomas::factory.ChangeComponent<Box_collider>(entity, box_data);
			}
		}

		//
		//for (int i = 0; i < mdl_obj.size(); ++i) {
		//	mdl_obj[i].draw();
		//	if (mdl_obj[i].bounding_on == 1)
		//		collider_obj[i].draw_collider();
		//}
	}


	void Graphics::cleanup() {
	}


	bool Graphics::simple_collision(glm::vec2 minA, glm::vec2 maxA, glm::vec2 minB, glm::vec2 maxB) {
		if (maxA.x > minB.x && maxA.y > minB.y && minA.x < maxB.x && minA.y < maxB.y)
			return true;
		else
			return false;
	}
}
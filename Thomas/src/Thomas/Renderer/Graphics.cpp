#include "thpch.h"
#include "Thomas/Renderer/Graphics.h"
#include "Thomas/Core/application.h"

#include "GLFW/glfw3.h"
#include <math.h>
#include <stb_image.h>
#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION
using namespace std;

// Declarations 
//std::vector<Graphics::temp_Obj> Graphics::mdl_obj;
//std::vector <Graphics::temp_Obj> Graphics::collider_obj;


void Graphics::init() {
	// Clear background & set viewport
	
	glClearColor(1.f, 1.f, 1.f, 1.f);
	Thomas::Application& app = Thomas::Application::Get();
	GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
	glfwGetWindowSize(window, &width, &height);
	glViewport(0, 0, width, height);

	temp_width = width;
	temp_height = height;

	// Load texture into container
	text_sys.Gen_Text("../Assets/textures/bigboss.png");
	text_sys.Gen_Text("../Assets/textures/background.png");
	text_sys.Gen_Text("../Assets/textures/sprite.png");

	//// Create first obj
	//temp_Obj test_obj, test_collider;
	//test_obj.trans_stuff.scaling = glm::vec2(1.f, 1.f);
	//test_obj.trans_stuff.translation = glm::vec2(0, 0);
	//test_obj.shader_stuff.setup_shdr_pgm();
	//test_obj.mesh_stuff.setup_vao();
	//test_collider.trans_stuff.scaling = test_obj.trans_stuff.scaling;
	//test_collider.trans_stuff.translation = test_obj.trans_stuff.translation;
	//test_collider.shader_stuff.setup_shdr_pgm();
	//test_collider.mesh_stuff.setup_vao();
	//mdl_obj.push_back(test_obj);
	//collider_obj.push_back(test_collider);
}


void Graphics::update(std::vector<Thomas::Entity> allentity){
	// Update mouse cursor
	Thomas::Application& app = Thomas::Application::Get();
	GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
	glfwGetCursorPos(window, &xpos, &ypos);
	GLdouble CursorX, CursorY;
	CursorX = xpos - width / 2;
	CursorY = (ypos - height / 2) * -1.f;
	
	//temp_physics();
	for (auto const& entity : allentity) {
		
		if (Thomas::factory.HasComponent<Texture>(entity)) {
			auto tex_data = Thomas::factory.GetComponent<Texture>(entity);
			auto mesh_data = Thomas::factory.GetComponent<Mesh>(entity);

			if (tex_data.text_file == 1)
				tex_data.texid = text_sys.texture_container[0];
			else if (tex_data.text_file == 2)
				tex_data.texid = text_sys.texture_container[1];
			else if (tex_data.text_file == 3)
				tex_data.texid = text_sys.texture_container[2];
			auto trans_data = Thomas::factory.GetComponent<Transform>(entity);
			trans_data.minmax(width, height);

			// Animation
			if (tex_data.animation_but == 1) {
				text_sys.animation(11, &tex_data.counter, &tex_data.switch_text, mesh_data.vbo_hdl);
			}

			Thomas::factory.ChangeComponent<Texture>(entity, tex_data);
			Thomas::factory.ChangeComponent<Mesh>(entity, mesh_data);
			Thomas::factory.ChangeComponent<Transform>(entity, trans_data);
		}

		if (Thomas::factory.HasComponent<Transform>(entity)) {
			auto cam_data = Thomas::factory.GetComponent<Camera>(entity);
			auto trans_data = Thomas::factory.GetComponent<Transform>(entity);

			cam_data.translation = trans_data.translation;
			cam_data.Camera2D_Init();
			trans_data.compute_mdl_to_ndc_xform();
			trans_data.mdl_to_ndc_xform = cam_data.world_to_ndc_xform * trans_data.mdl_to_ndc_xform;

			Thomas::factory.ChangeComponent<Camera>(entity, cam_data);
			Thomas::factory.ChangeComponent<Transform>(entity, trans_data);
		}

		if (Thomas::factory.HasComponent<Box_collider>(entity)) {
			auto cam_data = Thomas::factory.GetComponent<Camera>(entity);
			auto trans_data = Thomas::factory.GetComponent<Transform>(entity);
			auto box_data = Thomas::factory.GetComponent<Box_collider>(entity);

			box_data.box_trans.rotation = trans_data.rotation;
			box_data.box_trans.compute_mdl_to_ndc_xform();
			box_data.box_trans.mdl_to_ndc_xform = cam_data.world_to_ndc_xform * box_data.box_trans.mdl_to_ndc_xform;

			Thomas::factory.ChangeComponent<Box_collider>(entity, box_data);
		}

		// Using mouse to drag things around (Collision)
		if (Thomas::factory.HasComponent<Transform>(entity)) {
			auto trans_data = Thomas::factory.GetComponent<Transform>(entity);
			auto box_data = Thomas::factory.GetComponent<Box_collider>(entity);

			if ((CursorX > trans_data.min.x && CursorX<trans_data.max.x && CursorY>trans_data.min.y && CursorY < trans_data.max.y) && ImGui::IsMouseDown(0) && obj_clicked == 0) {
				std::cout << "HELLO" << std::endl;
				sel = entity;
				obj_clicked = 1;
				std::cout << sel << std::endl;
			}

			if (obj_clicked != 0) {
				glm::vec2 move = glm::vec2(CursorX, CursorY);
				//		glm::vec2 diff_dist = glm::vec2(mdl_obj[sel].trans_stuff.translation.x - collider_obj[sel].trans_stuff.translation.x, mdl_obj[sel].trans_stuff.translation.y - collider_obj[sel].trans_stuff.translation.y);
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
	//// Giving texture to objects accordingly
	//for (int i = 0; i < mdl_obj.size(); ++i) {
	//	if (mdl_obj[i].text_stuff.text_file == 1)
	//		mdl_obj[i].text_stuff.texid = text_sys.texture_container[0];
	//	else if (mdl_obj[i].text_stuff.text_file == 2)
	//		mdl_obj[i].text_stuff.texid = text_sys.texture_container[1];
	//	else if (mdl_obj[i].text_stuff.text_file == 3)
	//		mdl_obj[i].text_stuff.texid = text_sys.texture_container[2];
	//	mdl_obj[i].minmax();
	//	collider_obj[i].minmax();
	//	// Animation
	//	if (mdl_obj[i].text_stuff.animation_but == 1) {
	//		text_sys.animation(11, &mdl_obj[i].text_stuff.counter, &mdl_obj[i].text_stuff.switch_text, mdl_obj[i].mesh_stuff.vbo_hdl);
	//	}
	//}

	//// Update transform
	//for (int i = 0; i < mdl_obj.size(); ++i) {
	//	mdl_obj[i].cam_stuff.translation = mdl_obj[i].trans_stuff.translation;
	//	mdl_obj[i].cam_stuff.Camera2D_Init();
	//	glm::mat3 scale_mat = { mdl_obj[i].trans_stuff.scaling.x, 0, 0, 0, mdl_obj[i].trans_stuff.scaling.y, 0, 0, 0, 1 };
	//	glm::mat3 rot_mat = { cos(mdl_obj[i].trans_stuff.rotation * (M_PI / 180)), sin(mdl_obj[i].trans_stuff.rotation * (M_PI / 180)), 0, -sin(mdl_obj[i].trans_stuff.rotation * (M_PI / 180)), cos(mdl_obj[i].trans_stuff.rotation * (M_PI / 180)), 0, 0, 0, 1 };
	//	glm::mat3 trans_mat = { 1, 0, 0, 0, 1, 0, mdl_obj[i].trans_stuff.translation.x, mdl_obj[i].trans_stuff.translation.y, 1 };
	//	mdl_obj[i].trans_stuff.mdl_to_ndc_xform = mdl_obj[i].cam_stuff.world_to_ndc_xform * trans_mat * rot_mat * scale_mat;

	//	collider_obj[i].cam_stuff.translation = mdl_obj[i].trans_stuff.translation;
	//	collider_obj[i].trans_stuff.rotation = mdl_obj[i].trans_stuff.rotation;
	//	collider_obj[i].cam_stuff.Camera2D_Init();
	//	collider_obj[i].trans_stuff.compute_mdl_to_ndc_xform();
	//	collider_obj[i].trans_stuff.mdl_to_ndc_xform = collider_obj[i].cam_stuff.world_to_ndc_xform * collider_obj[i].trans_stuff.mdl_to_ndc_xform;
	//}

	//// Using mouse to drag things around (Collision)
	//for (int i = 0; i < mdl_obj.size(); ++i) {
	//	if ((CursorX > mdl_obj[i].min.x && CursorX<mdl_obj[i].max.x && CursorY>mdl_obj[i].min.y && CursorY < mdl_obj[i].max.y) && ImGui::IsMouseDown(0) && obj_clicked == 0) {
	//		sel = i;
	//		obj_clicked = 1;
	//		std::cout << sel << std::endl;
	//	}
	//	if (i != sel) {
	//		if (simple_collision(collider_obj[sel].min, collider_obj[sel].max, collider_obj[i].min, collider_obj[i].max)) {
	//			collider_obj[i].collision_detected = 1;
	//		}
	//		else {
	//			collider_obj[i].collision_detected = 0;
	//		}
	//	}
	//	if (collider_obj[sel].reset_but == 1) {
	//		collider_obj[sel].trans_stuff.translation = mdl_obj[sel].trans_stuff.translation;
	//		collider_obj[sel].trans_stuff.scaling = mdl_obj[sel].trans_stuff.scaling;
	//		collider_obj[sel].reset_but = 0;
	//	}

	//	if (obj_clicked != 0) {
	//		glm::vec2 move = glm::vec2(CursorX, CursorY);
	//		glm::vec2 diff_dist = glm::vec2(mdl_obj[sel].trans_stuff.translation.x - collider_obj[sel].trans_stuff.translation.x, mdl_obj[sel].trans_stuff.translation.y - collider_obj[sel].trans_stuff.translation.y);
	//		mdl_obj[sel].trans_stuff.translation.x = (move.x / (width / 2));
	//		mdl_obj[sel].trans_stuff.translation.y = -(move.y / (height / 2));
	//		collider_obj[sel].trans_stuff.translation.x = (move.x / (width / 2)) - diff_dist.x;
	//		collider_obj[sel].trans_stuff.translation.y = -(move.y / (height / 2)) - diff_dist.y;
	//	}
	//	if (ImGui::IsMouseReleased(0))
	//		obj_clicked = 0;
	//}
}


void Graphics::draw(std::vector<Thomas::Entity> allentity){
	glClear(GL_COLOR_BUFFER_BIT);
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


void Graphics::temp_Obj::draw() {
	int texture_toggle{};
	shader_stuff.shdr_pgm.Use();
	GLint uniform_var_loc1 = glGetUniformLocation(shader_stuff.shdr_pgm.GetHandle(), "uModelToNDC");
	if (uniform_var_loc1 >= 0) {
		glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, glm::value_ptr(trans_stuff.mdl_to_ndc_xform));
	}
	else {
		std::cout << "Uniform variable doesn't exist!!!\n";
		std::exit(EXIT_FAILURE);
	}
	if (text_stuff.text_file != 0)
		texture_toggle = 1;
	else
		texture_toggle = 0;
	GLint txttog = glGetUniformLocation(shader_stuff.shdr_pgm.GetHandle(), "TEXT_tog");
	glUniform1i(txttog, texture_toggle);
	GLint color = glGetUniformLocation(shader_stuff.shdr_pgm.GetHandle(), "tri_color");
	glUniform3fv(color, 1, glm::value_ptr(glm::vec3(0, 0, 0)));
	GLuint tex_loc = glGetUniformLocation(shader_stuff.shdr_pgm.GetHandle(), "uTex2d");
	glUniform1i(tex_loc, 1);
	glBindTextureUnit(1, text_stuff.texid);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindVertexArray(mesh_stuff.vaoid);
	glDrawElements(mesh_stuff.primitive_type, mesh_stuff.idx_elem_cnt, GL_UNSIGNED_SHORT, NULL);
	glBindVertexArray(0);
	shader_stuff.shdr_pgm.UnUse();
}


void Graphics::temp_Obj::draw_collider() {
	shader_stuff.shdr_pgm.Use();
	GLint uniform_var_loc1 = glGetUniformLocation(shader_stuff.shdr_pgm.GetHandle(), "uModelToNDC");
	if (uniform_var_loc1 >= 0) {
		glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, glm::value_ptr(trans_stuff.mdl_to_ndc_xform));
	}
	else {
		std::cout << "Uniform variable doesn't exist!!!\n";
		std::exit(EXIT_FAILURE);
	}
	GLint color = glGetUniformLocation(shader_stuff.shdr_pgm.GetHandle(), "tri_color");
	glUniform3fv(color, 1, glm::value_ptr(glm::vec3(0, 0, 0)));

	if (collision_detected == 0)
		glUniform3fv(color, 1, glm::value_ptr(glm::vec3(0, 1, 0)));
	else
		glUniform3fv(color, 1, glm::value_ptr(glm::vec3(1, 0, 0)));
	glBindVertexArray(mesh_stuff.vaoid);
	glLineWidth(5.f);
	glDrawElements(GL_LINE_STRIP, mesh_stuff.idx_elem_cnt, GL_UNSIGNED_SHORT, NULL);
	glBindVertexArray(0);
	shader_stuff.shdr_pgm.UnUse();
}


//void Graphics::Add_Obj() {
//	std::uniform_real_distribution<float> urdf(-1.0, 1.0);
//	temp_Obj new_mod, new_collider;
//	new_mod.trans_stuff.scaling = glm::vec2{ 1.f / 10.f, 1.f / 10.f };
//	new_mod.trans_stuff.translation = glm::vec2(urdf(dre), urdf(dre));
//	new_mod.shader_stuff.setup_shdr_pgm();
//	new_mod.mesh_stuff.setup_vao();
//	new_collider.trans_stuff.scaling = new_mod.trans_stuff.scaling;
//	new_collider.trans_stuff.translation = new_mod.trans_stuff.translation;
//	new_collider.shader_stuff.setup_shdr_pgm();
//	new_collider.mesh_stuff.setup_vao();
//	mdl_obj.push_back(new_mod);
//	collider_obj.push_back(new_collider);
//}
//
//
//void Graphics::temp_Obj::minmax() {
//	glm::vec2 sq1, sq2, sq3, sq4;
//	float minx1, minx2, maxx1, maxx2, miny1, miny2, maxy1, maxy2;
//	sq1 = glm::vec2(trans_stuff.mdl_to_ndc_xform * glm::vec3(-0.5f, -0.5f, 1.f));
//	sq2 = glm::vec2(trans_stuff.mdl_to_ndc_xform * glm::vec3(0.5f, -0.5f, 1.f));
//	sq3 = glm::vec2(trans_stuff.mdl_to_ndc_xform * glm::vec3(0.5f, 0.5f, 1.f));
//	sq4 = glm::vec2(trans_stuff.mdl_to_ndc_xform * glm::vec3(-0.5f, 0.5f, 1.f));
//	minx1 = std::min(sq1.x, sq2.x);
//	minx2 = std::min(sq3.x, sq4.x);
//	min.x = std::min(minx1, minx2) * width / 2;
//	miny1 = std::min(sq1.y, sq2.y);
//	miny2 = std::min(sq3.y, sq4.y);
//	min.y = std::min(miny1, miny2) * height / 2;
//	maxx1 = std::max(sq1.x, sq2.x);
//	maxx2 = std::max(sq3.x, sq4.x);
//	max.x = std::max(maxx1, maxx2) * width / 2;
//	maxy1 = std::max(sq1.y, sq2.y);
//	maxy2 = std::max(sq3.y, sq4.y);
//	max.y = std::max(maxy1, maxy2) * height / 2;
//}
//
//
//void Graphics::temp_physics() {
//	if (ImGui::IsKeyPressed(GLFW_KEY_W)) {
//		mdl_obj[sel].trans_stuff.translation.y -= 0.01f;
//		collider_obj[sel].trans_stuff.translation.y -= 0.01f;
//	}
//	if (ImGui::IsKeyPressed(GLFW_KEY_A)) {
//		mdl_obj[sel].trans_stuff.translation.x -= 0.01f;
//		collider_obj[sel].trans_stuff.translation.x -= 0.01f;
//	}
//	if (ImGui::IsKeyPressed(GLFW_KEY_S)) {
//		mdl_obj[sel].trans_stuff.translation.y += 0.01f;
//		collider_obj[sel].trans_stuff.translation.y += 0.01f;
//	}
//	if (ImGui::IsKeyPressed(GLFW_KEY_D)) {
//		mdl_obj[sel].trans_stuff.translation.x += 0.01f;
//		collider_obj[sel].trans_stuff.translation.x += 0.01f;
//	}
//}


bool Graphics::simple_collision(glm::vec2 minA, glm::vec2 maxA, glm::vec2 minB, glm::vec2 maxB) {
	if (maxA.x > minB.x && maxA.y > minB.y && minA.x < maxB.x && minA.y < maxB.y)
		return true;
	else
		return false;
}

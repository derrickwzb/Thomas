#include "thpch.h"
#include "Thomas/Renderer/Render.h"
#include "Thomas/Core/application.h"

//#include "Thomas/Renderer/Helper.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
//#include <imgui_impl_glfw_gl3.h>
#include <random>
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "GLFW/glfw3.h"


/// <Declarations>
//////////////////////////////////////////////////////////////////////////////////////	
std::vector<Render::Object> Render::mdl_obj;
std::vector <Render::Object> Render::collider_obj;
double pi = 3.14159265358979323846;
static std::default_random_engine dre;								// To create random location for the new obj
static int toggle{};																// To check if any obejct is being clicked
GLuint txt_0, txt_1, txt_2;
int width, height;
double xpos, ypos;




void Render::init() {

	width = 0;
	height = 0;
	Thomas::Application& app = Thomas::Application::Get();
	GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
	glfwGetWindowSize(window, &width, &height);

	aspect_ratio = (float)width / (float)height;
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glViewport(0, 0, width, height);
	txt_0 = Gen_Text("../textures/bigboss.png");
	txt_1 = Gen_Text("../textures/background.png");
	txt_2 = Gen_Text("../textures/sprite.png");
	Object test_obj, test_collider;
	test_obj.shape = obj_shape;
	test_obj.scaling = glm::vec2(1.f, 1.f);
	test_obj.translation = glm::vec2(0, 0);
	test_obj.setup_shdrpgm();
	test_obj.setup_vao();
	test_collider.shape = obj_shape;
	test_collider.scaling = test_obj.scaling;
	test_collider.translation = test_obj.translation;
	test_collider.setup_shdrpgm();
	test_collider.setup_vao();
	mdl_obj.push_back(test_obj);
	collider_obj.push_back(test_collider);
}


void Render::update() {
	Thomas::Application& app = Thomas::Application::Get();
	GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
	glfwGetCursorPos(window, &xpos, &ypos);
	GLdouble CursorX, CursorY;
	CursorX = xpos - width / 2;
	CursorY = (ypos - height / 2) * -1.f;
	temp_physics();

	for (int i = 0; i < mdl_obj.size(); ++i) {
		if (mdl_obj[i].text_file == 1)
			mdl_obj[i].texid = txt_0;
		else if (mdl_obj[i].text_file == 2)
			mdl_obj[i].texid = txt_1;
		else if (mdl_obj[i].text_file == 3)
			mdl_obj[i].texid = txt_2;
		mdl_obj[i].minmax();
		collider_obj[i].minmax();
		// Animation
		if (mdl_obj[i].animation_but == 1) {
			mdl_obj[i].animation(11);
		}
		
	}
	// Computing the scaling, rotation and translation matrix
	for (int i = 0; i < mdl_obj.size(); ++i) {
		mdl_obj[i].Camera2D_Init();
		glm::mat3 scale_mat = { mdl_obj[i].scaling.x, 0, 0, 0, mdl_obj[i].scaling.y, 0, 0, 0, 1 };
		glm::mat3 rot_mat = { cos(mdl_obj[i].rotation * (pi / 180)), sin(mdl_obj[i].rotation * (pi / 180)), 0, -sin(mdl_obj[i].rotation * (pi / 180)), cos(mdl_obj[i].rotation * (pi / 180)), 0, 0, 0, 1 };
		glm::mat3 trans_mat = { 1, 0, 0, 0, 1, 0, mdl_obj[i].translation.x, mdl_obj[i].translation.y, 1 };
		mdl_obj[i].mdl_to_ndc_xform = mdl_obj[i].world_to_ndc_xform * trans_mat * rot_mat * scale_mat;

		collider_obj[i].Camera2D_Init();
		glm::mat3 collider_scale_mat = { collider_obj[i].scaling.x, 0, 0, 0, collider_obj[i].scaling.y, 0, 0, 0, 1 };
		glm::mat3 collider_translation_mat = { 1, 0, 0, 0, 1, 0, collider_obj[i].translation.x, collider_obj[i].translation.y, 1 };
		collider_obj[i].mdl_to_ndc_xform = collider_obj[i].world_to_ndc_xform * collider_translation_mat * rot_mat * collider_scale_mat;
	}
	// Using mouse to move the object around
	//////////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < mdl_obj.size(); ++i) {
		//std::cout << mdl_obj[i].min.x << std::endl;
		if (mdl_obj[i].shape == 1) {
			glm::vec2 up_rad = glm::vec2(CursorX, CursorY) - mdl_obj[i].center;
			float new_rad = sqrt((up_rad.x * up_rad.x) + (up_rad.y * up_rad.y));
			if (new_rad <= mdl_obj[i].radius && ImGui::IsMouseDown(0) && toggle == 0) {
				sel = i;
				toggle = 1;
				
				
			}
		}
		else if (mdl_obj[i].shape == 0) {
			//std::cout << sel << "    "<< i << std::endl;
			if ((CursorX > mdl_obj[i].min.x && CursorX<mdl_obj[i].max.x && CursorX>mdl_obj[i].min.y && CursorX < mdl_obj[i].max.y) && ImGui::IsMouseDown(0) && toggle == 0) {
				sel = i;
				toggle = 1;
				std::cout << sel << std::endl;
			}
			/*if ((GLHelper::Cursor_X > collider_obj[i].min.x && GLHelper::Cursor_X<collider_obj[i].max.x && GLHelper::Cursor_Y>collider_obj[i].min.y && GLHelper::Cursor_Y < collider_obj[i].max.y) && ImGui::IsMouseDown(0)) {
				collider_obj[i].collision_detected = 1;
			}*/
			if (i != sel) {
				if (simple_collision(collider_obj[sel].min, collider_obj[sel].max, collider_obj[i].min, collider_obj[i].max)) {
					collider_obj[i].collision_detected = 1;
				}
				else {
					collider_obj[i].collision_detected = 0;
				}
			}
			
		}
		if (collider_obj[sel].reset_but == 1) {
			collider_obj[sel].translation = mdl_obj[sel].translation;
			collider_obj[sel].scaling = mdl_obj[sel].scaling;
			collider_obj[sel].reset_but = 0;
		}

		if (toggle != 0) {
			glm::vec2 move = glm::vec2(CursorX, CursorY);
			glm::vec2 diff_dist = glm::vec2(mdl_obj[sel].translation.x - collider_obj[sel].translation.x, mdl_obj[sel].translation.y - collider_obj[sel].translation.y);
			mdl_obj[sel].translation.x = (move.x / (width / 2));
			mdl_obj[sel].translation.y = -(move.y / (height / 2));
			collider_obj[sel].translation.x = (move.x / (width / 2)) - diff_dist.x;
			collider_obj[sel].translation.y = -(move.y / (height / 2)) - diff_dist.y;
		}
		if (ImGui::IsMouseReleased(0)) {
			toggle = 0;
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////
}


void Render::draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < mdl_obj.size(); ++i) {
		mdl_obj[i].draw();
		if (mdl_obj[i].BBtog == 1)
			collider_obj[i].draw_collider();
	}
}


void Render::cleanup() {
}


void Render::Object::setup_vao() {
	int slices = 50;
	double two_pi = 2 * pi;
	double angle = two_pi / slices;
	std::vector<glm::vec2> pos_vtx;
	std::vector<glm::vec2> txt_vtx;
	std::vector<GLushort> idx_vtx;
	if (this->shape == 0) {
		pos_vtx.push_back(glm::vec2(-0.5f, -0.5f));
		pos_vtx.push_back(glm::vec2(0.5f, -0.5f));
		pos_vtx.push_back(glm::vec2(0.5f, 0.5f));
		pos_vtx.push_back(glm::vec2(-0.5f, 0.5f));

		txt_vtx.push_back(glm::vec2(0.f, 0.f));
		txt_vtx.push_back(glm::vec2(1.f, 0.f));
		txt_vtx.push_back(glm::vec2(1.f, 1.f));
		txt_vtx.push_back(glm::vec2(0.f, 1.f));

		idx_vtx = { 0,1,2,2,3,0 };
		primitive_type = GL_TRIANGLES;
	}
	else {
		pos_vtx.push_back(glm::vec2(0.f, 0.f));
		for (int i = 1; i <= slices; ++i) {
			pos_vtx.push_back(glm::vec2(cos(i * angle) / 2.f, sin(i * angle) / 2.f));
			if (i == slices) {
				glm::vec2 rad = glm::vec2(width / 2, height / 2) * glm::vec2(this->mdl_to_ndc_xform * glm::vec3(cos(i * angle) / 2.f, sin(i * angle) / 2.f, 1.f));
				rad = rad - this->center;
				this->radius = sqrt((rad.x * rad.x) + (rad.y * rad.y));
			}
		}
		for (int i = 0; i <= slices + 1; ++i) {
			if (i == slices + 1)
				idx_vtx.push_back(1);
			else
				idx_vtx.push_back(i);
		}
		primitive_type = GL_TRIANGLE_FAN;
	}

	glCreateBuffers(1, &vbo_hdl);

	glNamedBufferStorage(vbo_hdl, sizeof(glm::vec2) * pos_vtx.size() + sizeof(glm::vec2) * txt_vtx.size(), nullptr, GL_DYNAMIC_STORAGE_BIT);
	glNamedBufferSubData(vbo_hdl, 0, sizeof(glm::vec2) * pos_vtx.size(), pos_vtx.data());
	glNamedBufferSubData(vbo_hdl, sizeof(glm::vec2) * pos_vtx.size(), sizeof(glm::vec2) * txt_vtx.size(), txt_vtx.data());

	glCreateVertexArrays(1, &vaoid);

	glEnableVertexArrayAttrib(vaoid, 0);
	glVertexArrayVertexBuffer(vaoid, 3, vbo_hdl, 0, sizeof(glm::vec2));
	glVertexArrayAttribFormat(vaoid, 0, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoid, 0, 3);

	glEnableVertexArrayAttrib(vaoid, 1);
	glVertexArrayVertexBuffer(vaoid, 4, vbo_hdl, sizeof(glm::vec2) * pos_vtx.size(), sizeof(glm::vec2));
	glVertexArrayAttribFormat(vaoid, 1, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoid, 1, 4);

	idx_elem_cnt = idx_vtx.size();
	GLuint ebo_hdl;
	glCreateBuffers(1, &ebo_hdl);
	glNamedBufferStorage(ebo_hdl, sizeof(GLushort) * idx_elem_cnt, reinterpret_cast<GLvoid*>(idx_vtx.data()), GL_DYNAMIC_STORAGE_BIT);
	glVertexArrayElementBuffer(vaoid, ebo_hdl);
	glBindVertexArray(0);
}


void Render::Object::setup_shdrpgm() {
	std::vector<std::pair<GLenum, std::string>> shdr_files{
	std::make_pair(GL_VERTEX_SHADER, "../shaders/engine_shdr.vert"),
	std::make_pair(GL_FRAGMENT_SHADER, "../shaders/engine_shdr.frag") };
	Shader shdr_pgm;
	shdr_pgm.CompileLinkValidate(shdr_files);
	if (GL_FALSE == shdr_pgm.IsLinked()) {
		std::cout << "Unable to compile/link/validate shader programs\n";
		std::cout << shdr_pgm.GetLog() << "\n";
		std::exit(EXIT_FAILURE);
	}
	Render::Object::shdr_pgm = shdr_pgm;
}


void Render::Object::draw() {
	int texture_toggle{};
	shdr_pgm.Use();
	GLint uniform_var_loc1 = glGetUniformLocation(shdr_pgm.GetHandle(), "uModelToNDC");
	if (uniform_var_loc1 >= 0) {
		glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, glm::value_ptr(mdl_to_ndc_xform));
	}
	else {
		std::cout << "Uniform variable doesn't exist!!!\n";
		std::exit(EXIT_FAILURE);
	}
	if (text_file != 0)
		texture_toggle = 1;
	else
		texture_toggle = 0;
	GLint txttog = glGetUniformLocation(shdr_pgm.GetHandle(), "TEXT_tog");
	glUniform1i(txttog, texture_toggle);
	GLint color = glGetUniformLocation(shdr_pgm.GetHandle(), "tri_color");
	glUniform3fv(color, 1, glm::value_ptr(glm::vec3(0, 0, 0)));
	GLuint tex_loc = glGetUniformLocation(shdr_pgm.GetHandle(), "uTex2d");
	glUniform1i(tex_loc, 1);
	glBindTextureUnit(1, texid);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindVertexArray(vaoid);
	glDrawElements(primitive_type, idx_elem_cnt, GL_UNSIGNED_SHORT, NULL);
	glBindVertexArray(0);
	shdr_pgm.UnUse();
}


void Render::Object::draw_collider() {
	shdr_pgm.Use();
	GLint uniform_var_loc1 = glGetUniformLocation(shdr_pgm.GetHandle(), "uModelToNDC");
	if (uniform_var_loc1 >= 0) {
		glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, glm::value_ptr(mdl_to_ndc_xform));
	}
	else {
		std::cout << "Uniform variable doesn't exist!!!\n";
		std::exit(EXIT_FAILURE);
	}
	GLint color = glGetUniformLocation(shdr_pgm.GetHandle(), "tri_color");
	glUniform3fv(color, 1, glm::value_ptr(glm::vec3(0, 0, 0)));

	if (collision_detected == 0)
		glUniform3fv(color, 1, glm::value_ptr(glm::vec3(0, 1, 0)));
	else
		glUniform3fv(color, 1, glm::value_ptr(glm::vec3(1, 0, 0)));
	glBindVertexArray(vaoid);
	glLineWidth(5.f);
	glDrawElements(GL_LINE_STRIP, idx_elem_cnt, GL_UNSIGNED_SHORT, NULL);
	glBindVertexArray(0);
	shdr_pgm.UnUse();
}


void Render::Add_Obj() {
	std::uniform_real_distribution<float> urdf(-1.0, 1.0);
	Object new_mod, new_collider;
	new_mod.shape = obj_shape;
	new_mod.scaling = glm::vec2{ 1.f / 10.f, 1.f / 10.f };
	new_mod.translation = glm::vec2(urdf(dre), urdf(dre));
	new_mod.setup_shdrpgm();
	new_mod.setup_vao();
	new_collider.shape = new_mod.shape;
	new_collider.scaling = new_mod.scaling;
	new_collider.translation = new_mod.translation;
	new_collider.setup_shdrpgm();
	new_collider.setup_vao();
	mdl_obj.push_back(new_mod);
	collider_obj.push_back(new_collider);
}


void Render::Object::Camera2D_Init() {
	GLFWwindow* r_Window;
	r_Window = glfwGetCurrentContext();
	GLsizei fb_width, fb_height;
	glfwGetFramebufferSize(r_Window, &fb_width, &fb_height);
	float ar = static_cast<GLfloat>(fb_width) / fb_height;
	glm::mat3 view_xform = { 1,0,0,0,1,0,(this->translation.x * ar) - this->translation.x,0,1 };
	glm::mat3 camwin_to_ndc_xform = { 1 / ar,0,0,0,-1,0,0,0,1 };
	this->world_to_ndc_xform = camwin_to_ndc_xform * view_xform;
}


GLuint Render::Gen_Text(const char* txt_file) {
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(txt_file, &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	stbi_image_free(data);
	return texture;
}


void Render::Object::minmax() {
	if (shape == 0) {
		glm::vec2 sq1, sq2, sq3, sq4;
		float minx1, minx2, maxx1, maxx2, miny1, miny2, maxy1, maxy2;
		sq1 = glm::vec2(this->mdl_to_ndc_xform * glm::vec3(-0.5f, -0.5f, 1.f));
		sq2 = glm::vec2(this->mdl_to_ndc_xform * glm::vec3(0.5f, -0.5f, 1.f));
		sq3 = glm::vec2(this->mdl_to_ndc_xform * glm::vec3(0.5f, 0.5f, 1.f));
		sq4 = glm::vec2(this->mdl_to_ndc_xform * glm::vec3(-0.5f, 0.5f, 1.f));
		minx1 = std::min(sq1.x, sq2.x);
		minx2 = std::min(sq3.x, sq4.x);
		this->min.x = std::min(minx1, minx2) * width / 2;
		miny1 = std::min(sq1.y, sq2.y);
		miny2 = std::min(sq3.y, sq4.y);
		this->min.y = std::min(miny1, miny2) * height / 2;
		maxx1 = std::max(sq1.x, sq2.x);
		maxx2 = std::max(sq3.x, sq4.x);
		this->max.x = std::max(maxx1, maxx2) * width / 2;
		maxy1 = std::max(sq1.y, sq2.y);
		maxy2 = std::max(sq3.y, sq4.y);
		this->max.y = std::max(maxy1, maxy2) * height / 2;
	}
	else {
		this->center = glm::vec2(this->mdl_to_ndc_xform * glm::vec3(0.f, 0.f, 1.f));
		this->center = glm::vec2(width / 2, height / 2) * this->center;
		glm::vec2 rad = glm::vec2(width / 2, height / 2) * glm::vec2(this->mdl_to_ndc_xform * glm::vec3(cos(2 * pi) / 2.f, sin(2 * pi) / 2.f, 1.f));
		rad = rad - this->center;
		this->radius = sqrt((rad.x * rad.x) + (rad.y * rad.y));
	}
}


void Render::Object::animation(int slices) {
	float length = 1.f / slices;
	float start_pos{};
	float end_pos{};
	counter++;
	if (counter % 10 == 0) {
		start_pos = switch_text * length;
		end_pos = (switch_text + 1) * length;
		std::vector<glm::vec2> txt_vtx;
		txt_vtx.push_back(glm::vec2(start_pos, 0.f));
		txt_vtx.push_back(glm::vec2(end_pos, 0.f));
		txt_vtx.push_back(glm::vec2(end_pos, 1.f));
		txt_vtx.push_back(glm::vec2(start_pos, 1.f));
		glNamedBufferSubData(vbo_hdl, sizeof(glm::vec2) * 4, sizeof(glm::vec2) * txt_vtx.size(), txt_vtx.data());
		++switch_text;
		if (switch_text == slices - 1)
			switch_text = 0;
	}
}


void Render::temp_physics() {
	if (ImGui::IsKeyPressed(GLFW_KEY_W)) {
		mdl_obj[sel].translation.y -= 0.01f;
		collider_obj[sel].translation.y -= 0.01f;
	}
	if (ImGui::IsKeyPressed(GLFW_KEY_A)) {
		mdl_obj[sel].translation.x -= 0.01f;
		collider_obj[sel].translation.x -= 0.01f;
	}
	if (ImGui::IsKeyPressed(GLFW_KEY_S)) {
		mdl_obj[sel].translation.y += 0.01f;
		collider_obj[sel].translation.y += 0.01f;
	}
	if (ImGui::IsKeyPressed(GLFW_KEY_D)) {
		mdl_obj[sel].translation.x += 0.01f;
		collider_obj[sel].translation.x += 0.01f;
	}
}


bool Render::simple_collision(glm::vec2 minA, glm::vec2 maxA, glm::vec2 minB, glm::vec2 maxB){
	if (maxA.x > minB.x && maxA.y > minB.y && minA.x < maxB.x && minA.y < maxB.y)
		return true;
	else
		return false;
}

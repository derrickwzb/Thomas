/*!*************************************************************************
\file:								Texture_system.cpp
\author:						Xie Zhi Xiong
\par DP email:			xiong.x@digipen.edu
\par Course:				CSD2125
\par Programming:	CSD2400 Game project
\date:							31/10/2022
\brief:
	This file contains the definitions of the member functions for
	Texture_system class.
****************************************************************************/
// Includes
#include "thpch.h"
#include "Thomas/Renderer/Texture_system.h"
#include <stb_image.h>
#include "GL/glew.h"
#include "Thomas/Core/application.h"

namespace Thomas {
	// Gen_Text(const char* txt_file)
	// Called to generate texture with the input parameter, then return the handle generated.
	uint32_t Texture_system::Gen_Text(const char* txt_file) {
		uint32_t texture;
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

	// animation(int slices, float* counter, float speed, int* switch_text, GLuint vbo_hdl)
	// Called to create animation 
	void Texture_system::animation(Texture& text_data/*float* counter, float speed, int* switch_text*/, uint32_t vbo_hdl) {
		text_data.max_text = text_data.slices - 1;
		text_data.text_len = 1.f / text_data.slices;
		float start_pos{};
		float end_pos{};
		text_data.counter += text_data.speed * Application::timestep;
		if (text_data.counter >=1.f) {
			start_pos = text_data.switch_text * text_data.text_len;
			end_pos = (text_data.switch_text +1) * text_data.text_len;
			std::vector<glm::vec2> txt_vtx;
			txt_vtx.push_back(glm::vec2(start_pos, 0.f));
			txt_vtx.push_back(glm::vec2(end_pos, 0.f));
			txt_vtx.push_back(glm::vec2(end_pos, 1.f));
			txt_vtx.push_back(glm::vec2(start_pos, 1.f));
			glNamedBufferSubData(vbo_hdl, sizeof(glm::vec2) * 4, sizeof(glm::vec2) * txt_vtx.size(), txt_vtx.data());
			++text_data.switch_text;
			if (text_data.switch_text == text_data.slices - 1)
				text_data.switch_text = 0;
			text_data.counter = 0.f;
		}
	}

	// animation_image(Texture& text_data, uint32_t vbo_hdl)
	// Called to cut animation image
	void Texture_system::animation_image(Texture& text_data, uint32_t vbo_hdl) {
		float start_pos{};
		float end_pos{};
		start_pos = text_data.switch_text * text_data.text_len;
		end_pos = (text_data.switch_text + 1) * text_data.text_len;
		std::vector<glm::vec2> txt_vtx;
		txt_vtx.push_back(glm::vec2(start_pos, 0.f));
		txt_vtx.push_back(glm::vec2(end_pos, 0.f));
		txt_vtx.push_back(glm::vec2(end_pos, 1.f));
		txt_vtx.push_back(glm::vec2(start_pos, 1.f));
		glNamedBufferSubData(vbo_hdl, sizeof(glm::vec2) * 4, sizeof(glm::vec2) * txt_vtx.size(), txt_vtx.data());
	}

	// animation_off(Texture& text_data, uint32_t vbo_hdl)
	// Called to off the animation 
	void Texture_system::animation_off(uint32_t vbo_hdl) {
		std::vector<glm::vec2> txt_vtx;
		txt_vtx.push_back(glm::vec2(0.f, 0.f));
		txt_vtx.push_back(glm::vec2(1.f, 0.f));
		txt_vtx.push_back(glm::vec2(1.f, 1.f));
		txt_vtx.push_back(glm::vec2(0.f, 1.f));
		glNamedBufferSubData(vbo_hdl, sizeof(glm::vec2) * 4, sizeof(glm::vec2) * txt_vtx.size(), txt_vtx.data());
	}
}
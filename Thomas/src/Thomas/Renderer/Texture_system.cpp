#include "thpch.h"
#include "Thomas/Renderer/Texture_system.h"
#include <stb_image.h>
#include "GL/glew.h"

//#define STB_IMAGE_IMPLEMENTATION

namespace Thomas {
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
		/*txt_cont.push_back(texture);*/
	}


	void Texture_system::animation(int slices, int* counter, int* switch_text, uint32_t vbo_hdl) {
		float length = 1.f / slices;
		float start_pos{};
		float end_pos{};
		int temp_counter{};
		int temp_switch{};
		(*counter)++;
		if ((*counter) % 10 == 0) {
			start_pos = *(switch_text)*length;
			end_pos = (*(switch_text)+1) * length;
			std::vector<glm::vec2> txt_vtx;
			txt_vtx.push_back(glm::vec2(start_pos, 0.f));
			txt_vtx.push_back(glm::vec2(end_pos, 0.f));
			txt_vtx.push_back(glm::vec2(end_pos, 1.f));
			txt_vtx.push_back(glm::vec2(start_pos, 1.f));
			glNamedBufferSubData(vbo_hdl, sizeof(glm::vec2) * 4, sizeof(glm::vec2) * txt_vtx.size(), txt_vtx.data());
			++* (switch_text);
			if (*(switch_text) == slices - 1)
				*(switch_text) = 0;
		}
	}
}
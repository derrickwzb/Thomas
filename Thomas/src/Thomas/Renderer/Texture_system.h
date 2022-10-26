#pragma once
#include <iostream>
#include <vector>
#include <stb_image.h>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION

namespace Thomas {
	class Texture_system {
	public:
		/*std::vector<GLuint> txt_cont;*/
		GLuint Gen_Text(const char* txt_file);
		void animation(int slices, int* counter, int* switch_text, GLuint vbo_hdl);
	};

	// Temp Individual Components
	inline static Texture_system	text_sys;
}

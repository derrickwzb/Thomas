#pragma once
#include <iostream>
#include <vector>

//#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>


namespace Thomas {
	class Texture_system {
	public:
		/*std::vector<GLuint> txt_cont;*/
		unsigned int Gen_Text(const char* txt_file);
		void animation(int slices, int* counter, int* switch_text, unsigned int vbo_hdl);
	};

	// Temp Individual Components
	static Texture_system	text_sys;
}

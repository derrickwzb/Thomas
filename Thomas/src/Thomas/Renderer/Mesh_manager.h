#pragma once
#include <GL/glew.h> // for access to OpenGL API declarations 
#include "Thomas/Renderer/Shader.h"
#include <vector>

namespace Thomas {
	class Mesh {
	public:
		// Data Members
		std::vector<glm::vec2> pos_vtx;
		std::vector<glm::vec2> txt_vtx;
		std::vector<GLushort> idx_vtx;
		GLenum			primitive_type;
		GLuint				vbo_hdl{};
		GLuint				vaoid{};
		GLuint				idx_elem_cnt{};

		// Member Functions
		void setup_vao();
	};
}
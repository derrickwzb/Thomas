#pragma once
//#include <GL/glew.h> // for access to OpenGL API declarations 
//#include "Thomas/Renderer/Shader.h"
//#include "GL/glew.h"
#include "glm/glm.hpp"

#include <vector>

namespace Thomas {
	class Mesh {
	public:
		// Data Members
		std::vector<glm::vec2> pos_vtx;
		std::vector<glm::vec2> txt_vtx;
		std::vector<unsigned short> idx_vtx;
		unsigned int			primitive_type;
		unsigned int				vbo_hdl{};
		unsigned int				vaoid{};
		unsigned int				idx_elem_cnt{};

		// Member Functions
		void setup_vao();
	};
}
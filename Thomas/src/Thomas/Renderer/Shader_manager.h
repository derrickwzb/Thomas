#pragma once
#include "Thomas/Renderer/Shader.h"

namespace Thomas {
	class Shader_manager {
	public:
		// Data Members
		Shader		shdr_pgm;

		// Member Functions
		void setup_shdr_pgm();
	};
}
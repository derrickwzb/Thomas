#include "thpch.h"
#include "Thomas/Renderer/Shader_manager.h"

namespace Thomas {
	void Shader_manager::setup_shdr_pgm() {
		std::vector<std::pair<GLenum, std::string>> shdr_files{
		std::make_pair(GL_VERTEX_SHADER, "../Assets/shaders/engine_shdr.vert"),
		std::make_pair(GL_FRAGMENT_SHADER, "../Assets/shaders/engine_shdr.frag") };
		shdr_pgm.CompileLinkValidate(shdr_files);
		if (GL_FALSE == shdr_pgm.IsLinked()) {
			std::cout << "Unable to compile/link/validate shader programs\n";
			std::cout << shdr_pgm.GetLog() << "\n";
			std::exit(EXIT_FAILURE);
		}
	}
}
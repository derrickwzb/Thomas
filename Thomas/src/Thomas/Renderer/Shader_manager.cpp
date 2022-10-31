#include "thpch.h"
#include "Thomas/Renderer/Shader_manager.h"

namespace Thomas {
	void Shader_manager::setup_shdr_pgm(std::string vert, std::string frag) {
		std::vector<std::pair<GLenum, std::string>> shdr_files{
		std::make_pair(GL_VERTEX_SHADER, vert),
		std::make_pair(GL_FRAGMENT_SHADER, frag) };
		shdr_pgm.CompileLinkValidate(shdr_files);
		if (GL_FALSE == shdr_pgm.IsLinked()) {
			std::cout << "Unable to compile/link/validate shader programs\n";
			std::cout << shdr_pgm.GetLog() << "\n";
			std::exit(EXIT_FAILURE);
		}
	}
}
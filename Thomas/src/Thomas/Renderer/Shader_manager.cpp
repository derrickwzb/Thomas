/*!*************************************************************************
\file:								Shader_manager.cpp
\author:						Xie Zhi Xiong
\par DP email:			xiong.x@digipen.edu
\par Course:				CSD2125
\par Programming:	CSD2400 Game project
\date:							31/10/2022
\brief:
	This file contains the definitions of the member functions for
	Shader_manager class.
****************************************************************************/
// Includes
#include "thpch.h"
#include "Thomas/Renderer/Shader_manager.h"
#include "GL/glew.h"

namespace Thomas {
	// setup_shdr_pgm(std::string vert, std::string frag)
	// Called to set up the shader program for the Shader_manager object
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
#pragma once
/*!*************************************************************************
\file:								Texture_system.h
\author:						Xie Zhi Xiong
\par DP email:			xiong.x@digipen.edu
\par Course:				CSD2125
\par Programming:	CSD2400 Game project
\date:							31/10/2022
\brief:
	This file contains the declarations for Texture_system class.
****************************************************************************/
// Includes
#include <iostream>
#include <vector>
#include <stb_image.h>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION

namespace Thomas {
	class Texture_system {
	public:
		// Member Functions 
		GLuint Gen_Text(const char* txt_file);
		void animation(int slices, float* counter, float speed, int* switch_text, GLuint vbo_hdl);
	};
	inline static Texture_system	text_sys;
}

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
#include <glm/gtc/type_ptr.hpp>
#include <Thomas/Renderer/Texture.h>

namespace Thomas {
	class Texture_system {
	public:
		// Member Functions 
		uint32_t Gen_Text(const char* txt_file);
		void animation(Texture& text_data, uint32_t vbo_hdl);
		void animation_image(Texture& text_data, uint32_t vbo_hdl);
		void animation_off(uint32_t vbo_hdl);


	};
	inline static Texture_system	text_sys;
}

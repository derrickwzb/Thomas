#pragma once
/*!*************************************************************************
\file:								Fonts.cpp
\author:						Xie Zhi Xiong
\par DP email:			xiong.x@digipen.edu
\par Course:				CSD2125
\par Programming:	CSD2400 Game project
\date:							31/10/2022
\brief:
	This file contains the declaration for Fonts class.
****************************************************************************/
// Includes
#include <iostream>
#include "ft2build.h"
#include <glm/gtc/matrix_transform.hpp>
#include <Thomas/Renderer/Shader_manager.h>
#include <glm/gtc/type_ptr.hpp>
#include FT_FREETYPE_H

namespace Thomas {
	class Fonts {
	public:
		// Data Members
		struct Character {
			unsigned int TextureID;			// ID handle of the glyph texture
			glm::ivec2 Size;						// Size of glyph
			glm::ivec2 Bearing;					// Offset from baseline to left/top of glyph
			unsigned int Advance;			// Offset to advance to next glyph
		};
		std::map<char, Character>		Characters;
		unsigned int							VAO;
		unsigned int							VBO;
		Shader_manager						font_shdr;
		FT_Library								ft;
		inline static FT_Face				face;
		std::string								font_type;
		// Member Functions 
		void Fonts_init();
		void RenderText(std::string text, float x, float y, float scale, float z_axis, glm::vec3 color);
	};
}

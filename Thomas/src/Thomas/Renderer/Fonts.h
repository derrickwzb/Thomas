#pragma once
#include <iostream>
#include <ft2build.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Thomas/Renderer/Shader_manager.h>
#include <glm/gtc/type_ptr.hpp>
#include FT_FREETYPE_H

namespace Thomas {
	class Fonts {
	public:
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
		inline static FT_Face									face;

		// Function to init the font
		void Fonts_init();

		// Function to render the font
		void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);
	};
}

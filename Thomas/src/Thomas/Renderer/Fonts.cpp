#include <thpch.h>
#include <Thomas/Renderer/Fonts.h>
//#include <Thomas/Renderer/Graphics.h>
#include "Thomas/Core/application.h"
#include "GLFW/glfw3.h"
#include "Thomas/Renderer/Asset_Manager.h"


namespace Thomas {
	void Fonts::Fonts_init() {

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		font_shdr.setup_shdr_pgm(stash.Shader_Storage["fonts.vert"], stash.Shader_Storage["fonts.frag"]);
		Thomas::Application& app = Thomas::Application::Get();
		int width, height;
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
		glfwGetWindowSize(window, &width, &height);
		glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
		font_shdr.shdr_pgm.Use();
		glUniformMatrix4fv(glGetUniformLocation(font_shdr.shdr_pgm.GetHandle(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		if (FT_Init_FreeType(&ft))
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

		if (FT_New_Face(ft, stash.Font_Storage["Arial.ttf"].c_str(), 0, &face))
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		else {
			FT_Set_Pixel_Sizes(face, 0, 48);

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			for (unsigned char c = 0; c < 128; c++) {
				if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
					std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
					continue;
				}

				unsigned int texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					face->glyph->bitmap.width,
					face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					face->glyph->bitmap.buffer
				);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				Character character = {
					texture,
					glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
					glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
					face->glyph->advance.x
				};
				Characters.insert(std::pair<char, Character>(c, character));
			}
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		FT_Done_Face(face);
		FT_Done_FreeType(ft);

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		font_shdr.shdr_pgm.UnUse();
	}

	void Fonts::RenderText(std::string text, float x, float y, float scale, glm::vec3 color) {
		font_shdr.shdr_pgm.Use();
		GLint c = glGetUniformLocation(font_shdr.shdr_pgm.GetHandle(), "textColor");
		glUniform3fv(c, 1, glm::value_ptr(color));
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(VAO);
		for (int i = 0; i < text.length(); ++i) {
			Character ch = Characters[text[i]];

			float xpos = x + ch.Bearing.x * scale;
			float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

			float w = ch.Size.x * scale;
			float h = ch.Size.y * scale;

			float vertices[6][4] = {
				{ xpos,			ypos + h,	0.0f, 0.0f },
				{ xpos,			ypos,	  	0.0f, 1.0f },
				{ xpos + w,	ypos,		1.0f,	1.0f },

				{ xpos,			ypos + h, 0.0f, 0.0f },
				{ xpos + w,	ypos,		1.0f,	1.0f },
				{ xpos + w,  ypos + h, 1.0f, 0.0f }
			};

			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			x += (ch.Advance >> 6) * scale;
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		font_shdr.shdr_pgm.UnUse();
	}
}
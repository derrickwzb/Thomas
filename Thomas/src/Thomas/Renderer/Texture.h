#pragma once
#include <GL/glew.h>

namespace Thomas {
	class Texture {
	public:
		GLuint texid{};
		int text_file{};
		int animation_but{};
		float counter{};
		float speed{};
		int switch_text{};
	};
}

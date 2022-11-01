#pragma once
#include <iostream>
#include <filesystem>
#include <map>
//#include <GL/glew.h>
//#include <Thomas/Renderer/Texture_system.h>

namespace Thomas {
	class Asset_Manager {
	public:
		inline static std::map <std::string, uint32_t> Text_Storage;
		inline static std::map <std::string, std::string> Font_Storage;
		inline static std::map <std::string, std::string> Shader_Storage;

		void Load_Texture();
		void Load_Font();
		void Load_Shader();
	};
	inline static Asset_Manager stash;
}

#include "thpch.h"
#include <Thomas/Renderer/Asset_Manager.h>

namespace Thomas {
	void Asset_Manager::Load_Texture() {
		std::string texture = "../Assets/textures";
		for (auto& file : std::filesystem::directory_iterator(texture)) {
			GLuint temp = Thomas::text_sys.Gen_Text(file.path().string().c_str());
			Text_Storage.emplace(file.path().filename().string(), temp);
			std::cout << file.path().filename().string() << "              " << temp << std::endl;
		}
	}

	void Asset_Manager::Load_Font() {
		std::string font = "../Assets/fonts";
		for (auto& file : std::filesystem::directory_iterator(font)) {
			Font_Storage.emplace(file.path().filename().string(), file.path().string());
		}
	}

	void Asset_Manager::Load_Shader() {
		std::string shaders = "../Assets/shaders";
		for (auto& file : std::filesystem::directory_iterator(shaders)) {
			Shader_Storage.emplace(file.path().filename().string(), file.path().string());
		}
	}
}
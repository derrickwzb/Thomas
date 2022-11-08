/*!*************************************************************************
\file:								Asset_Manager.cpp
\author:						Xie Zhi Xiong
\par DP email:			xiong.x@digipen.edu
\par Course:				CSD2125
\par Programming:	CSD2400 Game project
\date:							31/10/2022
\brief:
	This file contains the definitions of the member functions for 
	Asset_Manager class.
****************************************************************************/
// Includes
#include "thpch.h"
#include <Thomas/Renderer/Asset_Manager.h>
#include <Thomas/Renderer/Texture_system.h>

// Definitions 
namespace Thomas {
	
	//  Load_Texture()
	// 1. Loop thru the texture folder 
	// 2. Generate each texture file using the Gen_Text()
	// 3. Store in the Text_Storage map
	void Asset_Manager::Load_Texture() {
		std::string texture = "../Assets/textures";
		for (auto& file : std::filesystem::directory_iterator(texture)) {
			uint32_t temp = Thomas::text_sys.Gen_Text(file.path().string().c_str());
			Text_Storage.emplace(file.path().filename().string(), temp);
		}
	}

	// Load_Font()
	// 1. Loop thru the font folder
	// 2. Store in the Font_Storage map
	void Asset_Manager::Load_Font() {
		std::string font = "../Assets/fonts";
		for (auto& file : std::filesystem::directory_iterator(font)) {
			Font_Storage.emplace(file.path().filename().string(), file.path().string());
		}
	}

	// Load_Shader()
	// 1. Loop thru the shader folder
	// 2. Store in the Shader_Storage map
	void Asset_Manager::Load_Shader() {
		std::string shaders = "../Assets/shaders";
		for (auto& file : std::filesystem::directory_iterator(shaders)) {
			Shader_Storage.emplace(file.path().filename().string(), file.path().string());
		}
	}

	void Asset_Manager::Load_Audio() {
		std::string audio = "../Assets/audio";
		for (auto& file : std::filesystem::directory_iterator(audio)) {
			Audio_Storage.emplace(file.path().filename().string(), file.path().string());
		}
	}

}
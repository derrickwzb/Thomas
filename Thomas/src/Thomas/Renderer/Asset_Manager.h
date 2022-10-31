#pragma once
/*!*************************************************************************
\file:								Asset_Manager.h
\author:						Xie Zhi Xiong
\par DP email:			xiong.x@digipen.edu
\par Course:				CSD2125
\par Programming:	CSD2400 Game project
\date:							31/10/2022
\brief:
	This file contains the declaration of the Asset_Manager class
****************************************************************************/
// Includes
#include <iostream>
#include <filesystem>
#include <map>
#include <GL/glew.h>

namespace Thomas {
	class Asset_Manager {
	public:
		// Data Members
		inline static std::map <std::string, GLuint> Text_Storage;
		inline static std::map <std::string, std::string> Font_Storage;
		inline static std::map <std::string, std::string> Shader_Storage;

		// Member Functions 
		void Load_Texture();
		void Load_Font();
		void Load_Shader();
	};
	inline static Asset_Manager stash;
}

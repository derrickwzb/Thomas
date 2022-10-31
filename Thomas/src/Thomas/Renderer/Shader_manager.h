#pragma once
/*!*************************************************************************
\file:								Shader_manager.h
\author:						Xie Zhi Xiong
\par DP email:			xiong.x@digipen.edu
\par Course:				CSD2125
\par Programming:	CSD2400 Game project
\date:							31/10/2022
\brief:
	This file contains the declaration for Shader_manager class.
****************************************************************************/
// Includes
#include "Thomas/Renderer/Shader.h"

namespace Thomas {
	class Shader_manager {
	public:
		// Data Members
		Shader		shdr_pgm;

		// Member Functions
		void setup_shdr_pgm(std::string vert, std::string frag);
	};
}
#pragma once

/*!*************************************************************************
\file:								Texture.h
\author:						Xie Zhi Xiong
\par DP email:			xiong.x@digipen.edu
\par Course:				CSD2125
\par Programming:	CSD2400 Game project
\date:							31/10/2022
\brief:
	This file contains the declarations for Texture class.
****************************************************************************/
namespace Thomas {
	class Texture {
	public:
		uint32_t texid{};
		int text_file{};
		int animation_but{};
		float counter{};
		float speed{};
		int switch_text{};
	};
}

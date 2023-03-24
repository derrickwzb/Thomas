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

#include <string>

namespace Thomas {
	class Texture {
	public:
		uint32_t		texid{};
		int				text_file{};
		int				animation_but{};
		float				counter{};
		float				speed{10.f};
		float				slices{1.f};
		float				text_len{};
		float				max_text{};
		float				switch_text{};
		std::string	filename{};
		bool				button_hover = false;
		bool				text_show = true;
	};
}

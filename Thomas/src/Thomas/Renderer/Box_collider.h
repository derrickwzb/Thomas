#pragma once
/*!*************************************************************************
\file:								Box_collider.h
\author:						Xie Zhi Xiong
\par DP email:			xiong.x@digipen.edu
\par Course:				CSD2125
\par Programming:	CSD2400 Game project
\date:							31/10/2022
\brief:
	This file contains the declaration for Box_collider class.
****************************************************************************/
// Includes
#include "Thomas/Renderer/Graphics.h"

namespace Thomas {
	class Box_collider {
	public:
		//	Data Members
		int										reset_but{};
		int										collision_detected{};
		int										box_tog{};
		Mesh									box_mesh;
		Shader_manager					box_shader;
		Transform							box_trans;
	};
}
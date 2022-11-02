#pragma once
/*!*************************************************************************
\file:								Camera.h
\author:						Xie Zhi Xiong
\par DP email:			xiong.x@digipen.edu
\par Course:				CSD2125
\par Programming:	CSD2400 Game project
\date:							31/10/2022
\brief:
	This file contains the declaration for Camera class.
****************************************************************************/
// Includes
#include "Thomas/Renderer/Shader.h"
#include "Thomas/Renderer/Transform.h"

namespace Thomas {
	class Camera : public Transform {
	public:
		// Data Members
		float c_height;
		float c_width;
		float ar;
		glm::vec2 right;
		glm::vec2 up;
		float 	height{ 2 };
		float		min_height{ 3 };
		float		max_height{ 20 };
		int	cam_tog{};
		int	zoom_tog{};
		glm::mat3		view_xform{};
		glm::mat3		camwin_to_ndc_xform{};
		glm::mat3		world_to_ndc_xform{};

		// Keypress
		bool camtype_flag{ false };		// Change from 1st to 3rd person
		bool zoom_flag{ false };			// Zoom in and out
		bool left_turn_flag{ false };		// Turn left 
		bool right_turn_flag{ false };	// Turn right
		bool move_flag{ false };			// Move

		// Member Functions
		void Camera2D_Init();
		void Camera2D_Resize(uint32_t width, uint32_t height);
		void Camera2D_Update();
	};
}
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
		float c_width;
		float c_height;
		float c_ar;
		glm::vec2 right;
		glm::vec2 up;
		float 	height{2};
		int	cam_tog{};
		glm::mat3		view_xform{};
		glm::mat3		projection{};
		glm::mat3		world_to_ndc_xform{};

		// Keypress
		bool camtype_flag{ false };		// Change from 1st to 3rd person
		bool zoom_flag{ false };			// Zoom in and out
		bool left_turn_flag{ false };		// Turn left 
		bool right_turn_flag{ false };	// Turn right
		bool move_flag{ false };			// Move

		// Member Functions
		void Camera2D_Init();
		void Camera2D_Resize(float width, float height);
		void Camera2D_Update(int viewport_width, int viewport_height);
	};
}
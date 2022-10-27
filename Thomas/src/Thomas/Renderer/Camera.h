#pragma once
#include "Thomas/Renderer/Shader.h"
#include "Thomas/Renderer/Transform.h"
//#include "Thomas/Core/application.h"


namespace Thomas {
	class Camera : public Transform {
	public:
		// Data Members
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
		int cam_mode{};
		bool camtype_flag{ false };		// Change from 1st to 3rd person
		bool zoom_flag{ false };			// Zoom in and out
		bool left_turn_flag{ false };		// Turn left 
		bool right_turn_flag{ false };	// Turn right
		bool move_flag{ false };			// Move

		// Member Functions
		void Camera2D_Init();
		void Camera2D_compute_world_to_ndc_xform();
		void Camera2D_Update();
		void Camera2D_Update(Transform& selected_obj);
	};
}
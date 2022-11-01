/*!*************************************************************************
\file:								Camera.cpp
\author:						Xie Zhi Xiong
\par DP email:			xiong.x@digipen.edu
\par Course:				CSD2125
\par Programming:	CSD2400 Game project
\date:							31/10/2022
\brief:
	This file contains the definitions of the member functions for
	Camera class.
****************************************************************************/
// Includes
#include "thpch.h"
#include "Thomas/Renderer/Camera.h"
#include <math.h>
#define _USE_MATH_DEFINES

namespace Thomas {

	// Camera2D_Init()
	// Set the aspect ratio for the camera
	void Camera::Camera2D_Init() {
		GLsizei fb_width, fb_height;
		Application& app = Thomas::Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
		glfwGetWindowSize(window, &fb_width, &fb_height);
		ar = static_cast<GLfloat>(fb_width) / fb_height;
	}

	// Camera2D_ARresize(uint32_t width, uint32_t height)
	// Resize the aspect ratio
	void Camera::Camera2D_ARresize(uint32_t width, uint32_t height) {
		ar = static_cast<GLfloat>(width / height);
	}

	// Camera2D_compute_world_to_ndc_xform()
	// Compute the world_to_ndc matrix
	void Camera::Camera2D_compute_world_to_ndc_xform() {
		view_xform = { 1,0,0,0,1,0,(translation.x * ar) - translation.x,0,1 };
		camwin_to_ndc_xform = { 1 / (ar * height),0,0,0,-1 / height,0,0,0,1 };
		world_to_ndc_xform = camwin_to_ndc_xform * view_xform;
	}

	// Camera2D_Update()
	// Called to update the camera
	void Camera::Camera2D_Update() {
		// Switching the camera
		if (camtype_flag == GL_TRUE) {
			cam_tog = (cam_tog == 0) ? 1 : 0;
			camtype_flag = GL_FALSE;
		}

		// Camera rotating left
		if (left_turn_flag == GL_TRUE) {
			rotation++;
			up = { -(sinf(rotation * (M_PI / 180))), cosf(rotation * (M_PI / 180)) };
			right = { cosf(rotation * (M_PI / 180)), sinf(rotation * (M_PI / 180)) };
		}

		// Camera rotating right
		if (right_turn_flag == GL_TRUE) {
			rotation--;
			up = { -(sinf(rotation * (M_PI / 180))), cosf(rotation * (M_PI / 180)) };
			right = { cosf(rotation * (M_PI / 180)), sinf(rotation * (M_PI / 180)) };
		}
		
		// Camera moving forward
		if (move_flag == GL_TRUE)
			translation += (0.1f * up);

		// Camera zoom
		if (zoom_flag == GL_TRUE) {
			if (zoom_tog == 0) {
				height++;
				if (height >= max_height)
					zoom_tog = 1;
			}
			else {
				height--;
				if (height <= min_height)
					zoom_tog = 0;
			}
		}

		// Reset rotation 
		if (rotation > 360)
			rotation = 0;
		if (rotation < -360)
			rotation = 0;

		// Computations 
		up = { -(sinf(rotation * (M_PI / 180))), cosf(rotation * (M_PI / 180)) };
		right = { cosf(rotation * (M_PI / 180)), sinf(rotation * (M_PI / 180)) };
		view_xform = { 1,0,0,0,1,0,-translation.x,-translation.y,1 };
		camwin_to_ndc_xform = { 2.f / (ar * height),0,0,0,-2.f / height,0,0,0,1 };
		if (cam_tog == 1)
			view_xform = { right.x, up.x, 0, right.y, up.y, 0, -(glm::dot(right,translation)), -(glm::dot(up,translation)), 1 };
		world_to_ndc_xform = camwin_to_ndc_xform * view_xform;
	}

	// Camera2D_Update(ransform& selected_obj)
	//	Function overload from Camera2D_Update()
	void Camera::Camera2D_Update(Transform& selected_obj) {
		if (camtype_flag == GL_TRUE) {
			cam_tog = (cam_tog == 0) ? 1 : 0;
			camtype_flag = GL_FALSE;
		}

		if (left_turn_flag == GL_TRUE) {
			selected_obj.rotation++;
			up = { -(sinf(selected_obj.rotation * (M_PI / 180))), cosf(selected_obj.rotation * (M_PI / 180)) };
			right = { cosf(selected_obj.rotation * (M_PI / 180)), sinf(selected_obj.rotation * (M_PI / 180)) };
		}

		if (right_turn_flag == GL_TRUE) {
			selected_obj.rotation--;
			up = { -(sinf(selected_obj.rotation * (M_PI / 180))), cosf(selected_obj.rotation * (M_PI / 180)) };
			right = { cosf(selected_obj.rotation * (M_PI / 180)), sinf(selected_obj.rotation * (M_PI / 180)) };
		}

		if (move_flag == GL_TRUE)
			selected_obj.translation += (0.1f * up);

		if (zoom_flag == GL_TRUE) {
			if (zoom_tog == 0) {
				height++;
				if (height >= max_height)
					zoom_tog = 1;
			}
			else {
				height--;
				if (height <= min_height)
					zoom_tog = 0;
			}
		}

		if (selected_obj.rotation > 360)
			selected_obj.rotation = 0;
		if (selected_obj.rotation < -360)
			selected_obj.rotation = 0;

		up = { -(sinf(selected_obj.rotation * (M_PI / 180))), cosf(selected_obj.rotation * (M_PI / 180)) };
		right = { cosf(selected_obj.rotation * (M_PI / 180)), sinf(selected_obj.rotation * (M_PI / 180)) };
		view_xform = { 1,0,0,0,1,0,-selected_obj.translation.x,-selected_obj.translation.y,1 };
		camwin_to_ndc_xform = { 2.f / (ar * height),0,0,0,-2.f / height,0,0,0,1 };
		if (cam_tog == 1)
			view_xform = { right.x, up.x, 0, right.y, up.y, 0, -(glm::dot(right,selected_obj.translation)), -(glm::dot(up,selected_obj.translation)), 1 };
		world_to_ndc_xform = camwin_to_ndc_xform * view_xform;
	}

}
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
#include "GL/glew.h"
#include <math.h>
#include "GLFW/glfw3.h"
#include "Thomas/Core/application.h"
#define _USE_MATH_DEFINES

namespace Thomas {

	// Camera2D_Init()
	// Set the aspect ratio for the camera
	void Camera::Camera2D_Init() {
		GLsizei fb_width, fb_height;
		Application& app = Thomas::Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
		glfwGetWindowSize(window, &fb_width, &fb_height);
		c_width = (float)(fb_width);
		c_height = (float)(fb_height);
		c_ar = c_width / c_height;
	}

	// Camera2D_Resize()
	// Resize the aspect ratio
	void Camera::Camera2D_Resize(float width, float height) {
		c_ar = width / height;
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
			up = { -(sinf(rotation * static_cast<float>(M_PI / 180.f))), cosf(rotation * static_cast<float>(M_PI / 180.f)) };
			right = { cosf(rotation * static_cast<float>(M_PI / 180.f)), sinf(rotation * static_cast<float>(M_PI / 180.f)) };
		}

		// Camera rotating right
		if (right_turn_flag == GL_TRUE) {
			rotation--;
			up = { -(sinf(rotation * static_cast<float>(M_PI / 180.f))), cosf(rotation * static_cast<float>(M_PI / 180.f)) };
			right = { cosf(rotation * static_cast<float>(M_PI / 180.f)), sinf(rotation * static_cast<float>(M_PI / 180.f)) };
		}
		
		// Camera moving forward
		if (move_flag == GL_TRUE)
			translation += (0.001f * up);

		// Reset rotation 
		if (rotation > 360)
			rotation = 0;
		if (rotation < -360)
			rotation = 0;

		scaling.x = 1 / (c_ar * height);
		scaling.y = 1 / height;

		// Computations 
		up = { -(sinf(rotation * static_cast<float>(M_PI / 180.f))), cosf(rotation * static_cast<float>(M_PI / 180.f)) };
		right = { cosf(rotation * static_cast<float>(M_PI / 180.f)), sinf(rotation * static_cast<float>(M_PI / 180.f)) };
		projection = { scaling.x,0,0,0,-scaling.y,0,0,0,1 };
		view_xform = { 1,0,0,0,1,0,-translation.x, -translation.y,1 };
		if (cam_tog == 1)
			view_xform = { right.x, up.x, 0, right.y, up.y, 0, -(glm::dot(right,translation)), -(glm::dot(up,translation)), 1 };
		world_to_ndc_xform = projection * view_xform;
	}

}
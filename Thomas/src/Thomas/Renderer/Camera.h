#pragma once
#include "Thomas/Renderer/Shader.h"
#include "Thomas/Renderer/Transform.h"
#include "GLFW/glfw3.h"

class Camera : public Transform{
public:
	// Data Members
	glm::mat3		world_to_ndc_xform{};

	// Member Functions
	void Camera2D_Init();
};

#pragma once
#include "Thomas/Renderer/Shader.h"
#include <math.h>
#define _USE_MATH_DEFINES


class Transform{
public:
	//	Data Members
	glm::vec2			translation{};
	float					rotation{};
	glm::vec2			scaling{};
	glm::mat3		mdl_to_ndc_xform{};

	// Member Functions
	void compute_mdl_to_ndc_xform();
};

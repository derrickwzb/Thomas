#include "thpch.h"
#include "Thomas/Renderer/Transform.h"
#include <math.h>
#define _USE_MATH_DEFINES


void Transform::compute_mdl_to_ndc_xform() {
	glm::mat3 scale_mat = { scaling.x, 0, 0, 0, scaling.y, 0, 0, 0, 1 };
	glm::mat3 rot_mat = { cos(rotation * ( M_PI/ 180)), sin(rotation * (M_PI/ 180)), 0, -sin(rotation * (M_PI/ 180)), cos(rotation * (M_PI / 180)), 0, 0, 0, 1 };
	glm::mat3 trans_mat = { 1, 0, 0, 0, 1, 0, translation.x, translation.y, 1 };
	mdl_to_ndc_xform = trans_mat * rot_mat * scale_mat;
}

/*!*************************************************************************
\file:								Transform.cpp
\author:						Xie Zhi Xiong
\par DP email:			xiong.x@digipen.edu
\par Course:				CSD2125
\par Programming:	CSD2400 Game project
\date:							31/10/2022
\brief:
	This file contains the definitions of the member functions for
	Transform class.
****************************************************************************/
// Includes
#include "thpch.h"
#include "Thomas/Renderer/Transform.h"
#include "Thomas//Renderer/Graphics.h"
#include <math.h>
#define _USE_MATH_DEFINES

namespace Thomas {
	
	// compute_mdl_to_ndc_xform()
	// Called to calculate the mdl_to_ndc_xform matrix
	void Transform::compute_mdl_to_ndc_xform() {
		glm::mat3 scale_mat = { scaling.x, 0, 0, 0, scaling.y, 0, 0, 0, 1 };
		glm::mat3 rot_mat = { cos(rotation * (M_PI / 180)), sin(rotation * (M_PI / 180)), 0, -sin(rotation * (M_PI / 180)), cos(rotation * (M_PI / 180)), 0, 0, 0, 1 };
		glm::mat3 trans_mat = { 1, 0, 0, 0, 1, 0, translation.x, translation.y, 1 };
		mdl_to_ndc_xform = trans_mat * rot_mat * scale_mat;
	}
	
	// minmax_global()
	// Called to generate the global vertices
	void Transform::minmax_global() {
		glm::vec2 sq1, sq2, sq3, sq4;
		float minx1, minx2, maxx1, maxx2, miny1, miny2, maxy1, maxy2;

		sq1 = glm::vec2(Graphics::cam_stuff.world_to_ndc_xform * mdl_to_ndc_xform * glm::vec3(-0.5f, -0.5f, 1.f));
		sq2 = glm::vec2(Graphics::cam_stuff.world_to_ndc_xform * mdl_to_ndc_xform * glm::vec3(0.5f, -0.5f, 1.f));
		sq3 = glm::vec2(Graphics::cam_stuff.world_to_ndc_xform * mdl_to_ndc_xform * glm::vec3(0.5f, 0.5f, 1.f));
		sq4 = glm::vec2(Graphics::cam_stuff.world_to_ndc_xform * mdl_to_ndc_xform * glm::vec3(-0.5f, 0.5f, 1.f));

		global_vertice0 = Vec2(sq1.x, sq1.y);
		global_vertice1 = Vec2(sq2.x, sq2.y);
		global_vertice2 = Vec2(sq3.x, sq3.y);
		global_vertice3 = Vec2(sq4.x, sq4.y);

		minx1 = std::min(sq1.x, sq2.x);
		minx2 = std::min(sq3.x, sq4.x);
		global_min.x = std::min(minx1, minx2) * (Graphics::cam_stuff.c_width / 2);
		miny1 = std::min(sq1.y, sq2.y);
		miny2 = std::min(sq3.y, sq4.y);
		global_min.y = std::min(miny1, miny2) * (Graphics::cam_stuff.c_height / 2);
		maxx1 = std::max(sq1.x, sq2.x);
		maxx2 = std::max(sq3.x, sq4.x);
		global_max.x = std::max(maxx1, maxx2) * (Graphics::cam_stuff.c_width / 2);
		maxy1 = std::max(sq1.y, sq2.y);
		maxy2 = std::max(sq3.y, sq4.y);
		global_max.y = std::max(maxy1, maxy2) * (Graphics::cam_stuff.c_height / 2);
	}

	// minmax_screen(float width, float height)
	// Called to generate the screen vertices
	void Transform::minmax_screen(float width, float height) {
		glm::vec2 sq1, sq2, sq3, sq4;
		float minx1, minx2, maxx1, maxx2, miny1, miny2, maxy1, maxy2;

		sq1 = glm::vec2(Graphics::cam_stuff.world_to_ndc_xform * mdl_to_ndc_xform * glm::vec3(-0.5f, -0.5f, 1.f));
		sq2 = glm::vec2(Graphics::cam_stuff.world_to_ndc_xform * mdl_to_ndc_xform * glm::vec3(0.5f, -0.5f, 1.f));
		sq3 = glm::vec2(Graphics::cam_stuff.world_to_ndc_xform * mdl_to_ndc_xform * glm::vec3(0.5f, 0.5f, 1.f));
		sq4 = glm::vec2(Graphics::cam_stuff.world_to_ndc_xform * mdl_to_ndc_xform * glm::vec3(-0.5f, 0.5f, 1.f));

		screen_vertice0 = Vec2(sq1.x, sq1.y);
		screen_vertice1 = Vec2(sq2.x, sq2.y);
		screen_vertice2 = Vec2(sq3.x, sq3.y);
		screen_vertice3 = Vec2(sq4.x, sq4.y);

		minx1 = std::min(sq1.x, sq2.x);
		minx2 = std::min(sq3.x, sq4.x);
		screen_min.x = std::min(minx1, minx2) * (width / 2);
		miny1 = std::min(sq1.y, sq2.y);
		miny2 = std::min(sq3.y, sq4.y);
		screen_min.y = std::min(miny1, miny2) * (height / 2);
		maxx1 = std::max(sq1.x, sq2.x);
		maxx2 = std::max(sq3.x, sq4.x);
		screen_max.x = std::max(maxx1, maxx2) * (width / 2);
		maxy1 = std::max(sq1.y, sq2.y);
		maxy2 = std::max(sq3.y, sq4.y);
		screen_max.y = std::max(maxy1, maxy2) * (height / 2);
	}
}
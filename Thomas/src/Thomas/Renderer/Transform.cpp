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
	
	// minmax(int width, int height)
	// Called to generate the vertices of the object and calculate the min max 
	void Transform::minmax(float width, float height) {
		glm::vec2 sq1, sq2, sq3, sq4;
		float minx1, minx2, maxx1, maxx2, miny1, miny2, maxy1, maxy2;

		sq1 = glm::vec2(Graphics::cam_stuff.world_to_ndc_xform * mdl_to_ndc_xform * glm::vec3(-0.5f, -0.5f, 1.f));
		sq2 = glm::vec2(Graphics::cam_stuff.world_to_ndc_xform * mdl_to_ndc_xform * glm::vec3(0.5f, -0.5f, 1.f));
		sq3 = glm::vec2(Graphics::cam_stuff.world_to_ndc_xform * mdl_to_ndc_xform * glm::vec3(0.5f, 0.5f, 1.f));
		sq4 = glm::vec2(Graphics::cam_stuff.world_to_ndc_xform * mdl_to_ndc_xform * glm::vec3(-0.5f, 0.5f, 1.f));

		vertice0 = Vec2(sq1.x, sq1.y);
		vertice1 = Vec2(sq2.x, sq2.y);
		vertice2 = Vec2(sq3.x, sq3.y);
		vertice3 = Vec2(sq4.x, sq4.y);
		
	
	

		minx1 = std::min(sq1.x, sq2.x);
		minx2 = std::min(sq3.x, sq4.x);
		min.x = std::min(minx1, minx2) * (width / 2);
		miny1 = std::min(sq1.y, sq2.y);
		miny2 = std::min(sq3.y, sq4.y);
		min.y = std::min(miny1, miny2) * (height / 2);
		maxx1 = std::max(sq1.x, sq2.x);
		maxx2 = std::max(sq3.x, sq4.x);
		max.x = std::max(maxx1, maxx2) * (width / 2);
		maxy1 = std::max(sq1.y, sq2.y);
		maxy2 = std::max(sq3.y, sq4.y);
		max.y = std::max(maxy1, maxy2) * (height / 2);
	}

}
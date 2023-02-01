#pragma once
/*!*************************************************************************
\file:								Transform.cpp
\author:						Xie Zhi Xiong
\par DP email:			xiong.x@digipen.edu
\par Course:				CSD2125
\par Programming:	CSD2400 Game project
\date:							31/10/2022
\brief:
	This file contains the declarations for Transform class.
****************************************************************************/
// Includes
#include "Thomas/Renderer/Shader.h"
#include "Thomas/Math/Vector2D.h"
#include "Thomas/Math/Matrix3x3.h"
#include <math.h>
#include <vector>
#define _USE_MATH_DEFINES

namespace Thomas {
	class Transform {
	public:
		//	Data Members
		glm::vec2			translation{};
		float					rotation{};
		glm::vec2			scaling{};
		glm::mat3		mdl_to_ndc_xform{};
		float					z_axis{};
		bool					mouse_following{ FALSE };
		bool					mouse_clicking = false;
		bool					transform_Lock = false;

		// Vertices for global (Used for object collision)
		Vec2					global_vertice0;
		Vec2					global_vertice1;
		Vec2					global_vertice2;
		Vec2					global_vertice3;

		// Vertices for screen (Imgui Viewport, use for mouse picking)
		Vec2					screen_vertice0;
		Vec2					screen_vertice1;
		Vec2					screen_vertice2;
		Vec2					screen_vertice3;

		std::vector<Vec2> vertices;

		glm::vec2			global_min{};
		glm::vec2			global_max{};

		glm::vec2			screen_min{};
		glm::vec2			screen_max{};

		// object global size x for width y for height
		glm::vec2			global_size{};

		// object screen size x for width y for height
		glm::vec2			screen_size{};

		float alpha_val{1.f};

		glm::vec3 color{};
		// Member Functions
		void compute_mdl_to_ndc_xform();
		void minmax_global();
		void minmax_screen(float width, float height);
		glm::vec2 world_to_screen(glm::vec2 world_coords);
		glm::vec2 screen_to_world(glm::vec2 screen_coords);
		glm::mat4 getTransform();
	};
}
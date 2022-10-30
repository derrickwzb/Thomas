#pragma once
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

		// Vertices for collision side
		Vec2					vertice0;
		Vec2					vertice1;
		Vec2					vertice2;
		Vec2					vertice3;

		//temp
		glm::vec2			min{};
		glm::vec2			max{};

		void minmax(int width, int height);

		// Member Functions
		void compute_mdl_to_ndc_xform();
	};
}
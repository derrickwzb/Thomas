#pragma once
#include "Thomas/Maths/Math.hpp"

namespace Thomas {

	enum ComponentTypeId
	{
		//Invalid component id
		CT_None = 0,
		CT_Point,
		CT_Colour,
		CT_Triangle,
		CT_Rigidbody,
		CT_Bounds,
		CT_BoxCollider2D,
		CT_CircleCollider2D,
		CT_ColliderDistance2D,
		CT_LineSegment,
		CT_Ray,

		//Max
		CT_MaxComponents
	};

	struct Position
	{
		float x;
		float y;
		Position() = default;
		Position(const Position&) = default;
	};

	struct Colour 
	{
		float r;
		float g;
		float b;
		float a;
		Colour() = default;
		Colour(const Colour&) = default;
	};

	struct Triangle {
		float positionx;
		float positiony;
		float positionz;
	};

	struct Rigidbody2DComponent
	{
		// object current position
		Vector2D posCurr = {0.f, 0.f};
		// object current velocity
		Vector2D velCurr = { 0.f, 0.f };
		// object current direction
		float dirCurr = { 0.f };

		// Storage for runtime
		void* RuntimeBody = nullptr;

		Rigidbody2DComponent() = default;
		Rigidbody2DComponent(const Rigidbody2DComponent&) = default;
	};
}

#pragma once
#include "Thomas/Math/Math.hpp"

namespace Thomas {

	enum ComponentTypeId
	{
		//Invalid component id
		CT_None = 0,
		CT_Point,
		CT_Colour,
		CT_Triangle,
		CT_Transform,
		CT_Shader_manager,
		CT_Mesh,
		CT_Texture,
		CT_Camera,
		CT_Box_collider,
		CT_RigidBody,
		CT_BoxCollider2D,

		//Max component number
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

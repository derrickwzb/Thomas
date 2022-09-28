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
		
	public:
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


	struct Bounds
	{
		Vec2 centre;
		Vec2 extents;
		Vec2 max;
		Vec2 min;
		Vec2 size;

		Bounds() = default;
		Bounds(const Bounds&) = default;
	};

	class Collider2D
	{
	public:

		float bounciness;
		Vec2 offset;
		bool isTrigger;
		float friction;
		Bounds bounds;
		//virtual ColliderDistance2D Distance(Collider2D _collider) const;

	};

	class BoxCollider2D : public Collider2D
	{

	public:
		Vector2D size;
	};

	class CircleCollider2D : public Collider2D
	{
	public:
		float radius;
		float mass{ 1.0f };
	};

	struct ColliderDistance2D
	{
		float distance;
		bool isOverlapped;
		bool isValid;
		Vec2 normal;
		Vec2 pointA;
		Vec2 pointB;
	};

	class Collision2D
	{

	public:

		Bounds temp;
		Vec2 relativeVelocity;
		Collider2D otherCollider;
		bool enabled;
	};

	//class LineSegment
	//{
	//public:
	//	Vec2	point0;
	//	Vec2	point1;
	//	Vec2	normal;
	//};

	struct LineSegment
	{
		Vector2D pt0;
		Vector2D pt1;
		Vector2D normal;
	};

	struct Ray
	{
	public:
		Vec2 direction;
		Vec2 origin;
	};
}

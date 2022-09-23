

#include "Bounds.hpp"
//#include "main.h"
#include "Vector2D.hpp"

#ifndef COLLISION2D_H_
#define COLLISION2D_H_


class Collision2D
{


public:


	Bounds temp;
	Vec2 relativeVelocity;
	//Collider2D otherCollider;
	bool enabled;
};

bool CollisionIntersection_RectRect(const Bounds& aabb1, const Vec2& vel1,
	const Bounds& aabb2, const Vec2& vel2);

#endif

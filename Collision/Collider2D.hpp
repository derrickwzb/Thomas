#include "Vector2D.hpp"
#include "Bounds.hpp"

#ifndef COLLIDER2D_H_
#define COLLIDER2D_H_

class Collider2D
{
public:

	float bounciness;
	Vec2 offset;
	bool isTrigger;
	float friction;
	Bounds bounds;

	virtual float Distance() const = 0;



}

#endif
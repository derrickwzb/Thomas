

#ifndef BOUNDS_H_
#define BOUNDS_H_

#include "Vector2D.hpp"
struct Bounds
{

	Vec2 centre;
	Vec2 extents;
	Vec2 max;
	Vec2 min;
	Vec2 size;
	Bounds();
	~Bounds() {};
	Bounds(Vec2 _centre, Vec2 _size);


};

#endif



#include "Bounds.hpp"
//#include "main.h"
#include "Vector2D.hpp"
#include "CircleCollider2D.hpp"
#include "LineSegment.hpp"
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



bool CollisionIntersection_CircleCircle(const CircleCollider2D& circleA, const Vector2D& velA,
	const CircleCollider2D& circleB, const Vector2D& velB,
	Vector2D& interPtA, Vector2D& interPtB,
	float& interTime);

bool CollisionIntersection_RayCircle(const Ray& ray, const CircleCollider2D& circle, float& interTime);

bool CollisionIntersection_CircleLineSegment(const CircleCollider2D& circle, const Vector2D& ptEnd,
	const LineSegment& lineSeg, Vector2D& interPt,
	Vector2D& normalAtCollision, float& interTime,
	bool& checkLineEdges);

bool CheckMovingCircleToLineEdge(bool withinBothLines, const CircleCollider2D& circle,
	const Vector2D& ptEnd, const LineSegment& lineSeg, Vector2D& interPt,
	Vector2D& normalAtCollision, float& interTime);




#endif

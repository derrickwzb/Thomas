

#include "Collider2D.hpp"
#include "Bounds.hpp"
#include "CircleCollider2D.hpp"
#include "Ray.hpp"
#include "LineSegment.hpp"
class Collision2D
{
public:
    static bool CollisionIntersection_RectRect(const Bounds &aabb1, const Vector2D &vel1,
											   const Bounds &aabb2, const Vector2D&vel2);

	static bool CollisionIntersection_CircleCircle(const CircleCollider2D& circleA, const Vector2D& velA,
												   const CircleCollider2D& circleB, const Vector2D& velB,
												   Vector2D& interPtA, Vector2D& interPtB,
												   float& interTime);

	static bool CollisionIntersection_RayCircle(const Ray& ray, const CircleCollider2D& circle, float& interTime);

	static bool CheckMovingCircleToLineEdge(bool withinBothLines, const CircleCollider2D& circle,
											const Vector2D& ptEnd, const LineSegment& lineSeg, Vector2D& interPt,
											Vector2D& normalAtCollision, float& interTime)




}



#include "Collider2D.hpp"
#include "Bounds.hpp"

class Collision2D
{
public:
    static bool CollisionIntersection_RectRect(const Bounds &aabb1, const Vector2D &vel1,
									const Bounds &aabb2, const Vector2D&vel2);
}

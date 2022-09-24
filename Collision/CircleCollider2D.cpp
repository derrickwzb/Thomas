#include "CircleCollider2D.hpp"

CircleCollider2D::CircleCollider2D(const CircleCollider2D& _circle)
{
	radius = _circle.radius;
	mass = _circle.mass;
}

CircleCollider2D::CircleCollider2D() : radius { 0.f }, mass{ 1.0f }
{

}

float CircleCollider2D::Distance() const
{
	return 0.0f;
}

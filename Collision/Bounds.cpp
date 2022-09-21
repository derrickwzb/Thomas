#include "Bounds.hpp"

Bounds::Bounds(Vector2D _centre, Vector2D _size)
{
	centre = _centre;
	size = _size;
	extents = _size / 2;

	max = centre + extents;
	min = centre - extents;


}
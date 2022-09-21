
#include "Vector2D.h"

struct Bounds
{

	Vector2D centre;
	Vector2D extents;
	Vector2D max;
	Vector2D min;
	Vector2D size;
	Bounds() {};
	~Bounds() {};
	Bounds(Vector2D _centre, Vector2D _size);


};

#include "../Math/Vector2D.h"
#include "Bounds.hpp"

class Collider2D
{
public:

	float bounciness;
	Vector2D offset;
	bool isTrigger;
	float friction;
	Bounds bounds;

	virtual float Distance() const = 0;



}
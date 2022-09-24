
#include "Collider2D.hpp"

class BoxCollider2D : public Collider2D
{

public:

	Vector2D size;


	virtual float Distance() const override;



};
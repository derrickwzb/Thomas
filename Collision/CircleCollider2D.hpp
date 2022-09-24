#include "Collider2D.hpp"

class CircleCollider2D : public Collider2D
{
public:
    float radius;
    float mass{ 1.0f };

    CircleCollider2D(const CircleCollider2D& _circle);
    CircleCollider2D();
    virtual float Distance() const override;
};
#include "Vector2D.hpp"

#ifndef RAY_H_
#define RAY_H_

class Ray
{
public:
    Vec2 direction;
    Vec2 origin;
    Ray();
    Ray(Vec2 const& direction, Vec2 const& origin);


};

#endif
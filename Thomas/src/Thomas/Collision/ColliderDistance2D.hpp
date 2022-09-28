#pragma once
#include "Thomas/Math/Math.hpp"

namespace Thomas
{
    struct ColliderDistance2D
    {
        float distance;
        bool isOverlapped;
        bool isValid;
        Vec2 normal;
        Vec2 pointA;
        Vec2 pointB;
    };
}
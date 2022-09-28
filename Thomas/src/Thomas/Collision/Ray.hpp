/******************************************************************************/
/*!
\file		Ray.hpp
\author 	Keith Lua, weijiekeith.lua, 2101223
\par    	email: weijiekeith.lua\@digipen.edu
\date   	25/9/2022
\brief		This file represents the interface of the source file
			Ray.cpp, it contains the function prototype declarations
			and class definition. The functions in the respective .cpp file
			are its member functions. The Ray class is representation of a ray.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/
#pragma once
#include "Thomas/Math/Math.hpp"

#ifndef RAY_H_
#define RAY_H_

namespace Thomas
{
    class Ray
    {
    public:
        Vec2 direction;
        Vec2 origin;
        /**************************************************************************/
        /*!
            This is the default constructor of the Ray class.
        */
        /**************************************************************************/
        Ray();

        /**************************************************************************/
        /*!
            This is the parameterized constructor of the Bounds struct.
        */
        /**************************************************************************/
        Ray(Vec2 const& _direction, Vec2 const& _origin);


    };
}

#endif
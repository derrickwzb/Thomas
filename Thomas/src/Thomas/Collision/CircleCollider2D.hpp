/******************************************************************************/
/*!
\file		CircleCollider2D.hpp
\author 	Keith Lua, weijiekeith.lua, 2101223
\par    	email: weijiekeith.lua\@digipen.edu
\date   	25/9/2022
\brief		This file represents the interface of the source file
            CircleCollider2D.cpp, it contains the function prototype 
            declarations and class definition. The functions in the 
            respective .cpp file are its member functions. The BoxCollider2D 
            class is a representation of a collider for circles.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/
#pragma once
#include "Collider2D.hpp"

namespace Thomas
{
    //This circle collider stores the radius of the cthe circle
    class CircleCollider2D : public Collider2D
    {
    public:
        float radius;
        float mass{ 1.0f };

        /**************************************************************************/
        /*!
            This is the default constructor of the CircleCollider2D class.
        */
        /**************************************************************************/
        CircleCollider2D();

        /**************************************************************************/
        /*!
            This is the copy constructor of the CircleCollider2D class.
        */
        /**************************************************************************/
        CircleCollider2D(const CircleCollider2D& _circle);


        //virtual ColliderDistance2D Distance(Collider2D _collider) const override;
    };
}

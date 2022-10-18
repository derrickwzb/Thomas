/******************************************************************************/
/*!
\file		CircleCollider2D.cpp
\author 	Keith Lua, weijiekeith.lua, 2101223
\par    	email: weijiekeith.lua\@digipen.edu
\date   	25/9/2022
\brief		This file represents the implementation of a functions
			and class specified in interface (header) file CircleCollider2D.hpp.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "thpch.h"
#include "CircleCollider2D.hpp"

namespace Thomas
{
	/**************************************************************************/
	/*!
		This is the default constructor of the CircleCollider2D class.
	*/
	/**************************************************************************/
	CircleCollider2D::CircleCollider2D() : radius{ 0.f }, mass{ 1.0f }
	{

	}

	/**************************************************************************/
	/*!
		This is the copy constructor of the CircleCollider2D class.
	*/
	/**************************************************************************/
	CircleCollider2D::CircleCollider2D(const CircleCollider2D& _circle)
	{
		radius = _circle.radius;
		mass = _circle.mass;
	}

}

/******************************************************************************/
/*!
\file		Ray.cpp
\author 	Keith Lua, weijiekeith.lua, 2101223
\par    	email: weijiekeith.lua\@digipen.edu
\date   	25/9/2022
\brief		This file represents the implementation of functions
			and class specified in interface (header) file Ray.hpp.
			The file consists of member functions of Ray class.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/

#include "Ray.hpp"

/**************************************************************************/
/*!
	This is the default constructor of the Bounds struct.
*/
/**************************************************************************/
Ray::Ray() : direction{ 0,0 }, origin{ 0,0 }
{

}

/**************************************************************************/
/*!
	This is the parameterized constructor of the Bounds struct.
*/
/**************************************************************************/
Ray::Ray(Vec2 const& _direction, Vec2 const& _origin) : direction{0,0}, origin{0,0}
{
	direction = _direction;
	origin = _origin;
}
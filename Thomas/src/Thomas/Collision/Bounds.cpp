/******************************************************************************/
/*!
\file		Bounds.cpp
\author 	Keith Lua, weijiekeith.lua, 2101223
\par    	email: weijiekeith.lua\@digipen.edu
\date   	25/9/2022
\brief		This file represents the implementation of a Bounds struct 
			that are specified in interface (header) file Bounds.hpp. 
			The file consist of member functions of Bounds struct.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/

#include "thpch.h"
#include "Collision.h"

namespace Thomas
{

	/**************************************************************************/
	/*!
		This is the default constructor of the Bounds struct.
	*/
	/**************************************************************************/
	Bounds::Bounds() {};

	/**************************************************************************/
	/*!
		This is the parameterized constructor of the Bounds struct.
	*/
	/**************************************************************************/
	Bounds::Bounds(Vec2 _centre, Vec2 _size)
	{
		centre = _centre;
		size = _size;
	}
}

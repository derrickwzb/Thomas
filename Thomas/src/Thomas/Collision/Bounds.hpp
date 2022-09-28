/******************************************************************************/
/*!
\file		Bounds.hpp
\author 	Keith Lua, weijiekeith.lua, 2101223
\par    	email: weijiekeith.lua\@digipen.edu
\date   	25/9/2022
\brief		This file represents the interface of the source file
			Bounds.cpp, it contains the function prototype declarations
			and struct definition. The functions in the respective .cpp file
			are its member functions. The Bounds struct is a representation
			of a axis aligned bounding box (AABB).

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/

#pragma once
#ifndef BOUNDS_H_
#define BOUNDS_H_

#include "Thomas/Maths/Math.hpp"

namespace Thomas
{
	struct Bounds
	{

		Vec2 centre;
		Vec2 extents;
		Vec2 max;
		Vec2 min;
		Vec2 size;

		/**************************************************************************/
		/*!
			This is the default constructor of the Bounds struct.
		*/
		/**************************************************************************/
		Bounds();

		/**************************************************************************/
		/*!
			This is the destructor of the Bounds struct.
		*/
		/**************************************************************************/
		~Bounds() {};

		/**************************************************************************/
		/*!
			This is the parameterized constructor of the Bounds struct.
		*/
		/**************************************************************************/
		Bounds(Vec2 _centre, Vec2 _size);


	};
}
#endif

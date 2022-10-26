/******************************************************************************/
/*!
\file		Collider2D.hpp
\author 	Keith Lua, weijiekeith.lua, 2101223
\par    	email: weijiekeith.lua\@digipen.edu
\date   	25/9/2022
\brief		This file represents the interface of the source file
			Collider2D.cpp, it contains the function prototype declarations
			and class definition. The functions in the respective .cpp file
			are its member functions. The Collider2D class is a parent class
			of all collider types.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/

#pragma once
#include "Thomas/Math/Math.hpp"
#include "Bounds.hpp"

#ifndef COLLIDER2D_H_
#define COLLIDER2D_H_
namespace Thomas
{
	class Collider2D
	{
	public:

		float bounciness;
		Vec2 offset;
		bool isTrigger;
		float friction;
		Bounds bounds;
		//std::vector<Vec2> vertices;
		std::array<std::array<int, 2>, 4> vertices;

	};
}
#endif
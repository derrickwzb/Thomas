/******************************************************************************/
/*!
\file		BoxCollider2D.hpp
\author 	Keith Lua, weijiekeith.lua, 2101223
\par    	email: weijiekeith.lua\@digipen.edu
\date   	25/9/2022
\brief		This file represents the interface of the source file
			BoxCollider2D.cpp, it contains the function prototype declarations
			and class definition. The functions in the respective .cpp file
			are its member functions. The BoxCollider2D class is a 
			representation of a collider for axis aligned boxes.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include "Collider2D.hpp"
namespace Thomas
{
	class BoxCollider2D : public Collider2D
	{

	public:

		Vector2D size;
		//virtual ColliderDistance2D Distance(Collider2D _collider) const override;
	};
}

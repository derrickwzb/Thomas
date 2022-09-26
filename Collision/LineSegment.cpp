/******************************************************************************/
/*!
\file		LineSegment.cpp
\author 	Keith Lua, weijiekeith.lua, 2101223
\par    	email: weijiekeith.lua\@digipen.edu
\date   	25/9/2022
\brief		This file represents the implementation of a functions
			and class specified in interface (header) file LineSegment.hpp.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "LineSegment.hpp"

/**************************************************************************/
/*!
	This is the default constructor of the LineSegment class.
*/
/**************************************************************************/
LineSegment::LineSegment() : point0{ 0,0, }, point1{ 0,0 }, normal{0,0}
{

}
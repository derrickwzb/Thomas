/******************************************************************************/
/*!
\file		LineSegment.hpp
\author 	Keith Lua, weijiekeith.lua, 2101223
\par    	email: weijiekeith.lua\@digipen.edu
\date   	25/9/2022
\brief		This file represents the interface of the source file
			LineSegment.cpp, it contains the function prototype declarations
			and class definition.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "Vector2D.hpp"

#ifndef LINESEGMENT_H_
#define LINESEGMENT_H_

class LineSegment
{
public:
	Vec2	point0;
	Vec2	point1;
	Vec2	normal;

	/**************************************************************************/
	/*!
		This is the default constructor of the LineSegment class.
	*/
	/**************************************************************************/
	LineSegment();
};

#endif 


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
#include <vector>
#ifndef COLLIDER2D_H_
#define COLLIDER2D_H_
namespace Thomas
{
	//Collider2D is where the vertices of the objects are stored as well as their min and max
	class Collider2D
	{
	public:

		//float bounciness;
		//Vec2 offset;
		//bool isTrigger;
		//float friction;

		//Stores the boundary of the shape
		bool isKinematic = true;
		bool isTrigger = false;
		Bounds bounds;

		//Stores the vertices of the shape. It's sorted in the clockwise order.
		std::vector<Vec2> verticesList;
		std::array<std::array<float, 2>, 4> vertices;
		void ArrayToVector()
		{
			if (verticesList.size() < vertices.size())
			{
				for (int i = 0; i < vertices.size(); ++i)
				{
					Vec2 vector;
					int j, k;
					for (j = 0, k = j + 1; j < vertices[i].size(); j += 2, ++k)
					{
						vector.x = vertices[i][j];
						vector.y = vertices[i][k];
						verticesList.push_back(vector);
					}
				}
			}
		}
	};
}
#endif
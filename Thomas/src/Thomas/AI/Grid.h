/******************************************************************************/
/*!
\file   Grid.h
\author Keith Lua
\par    email: weijiekeith.lua\@digipen.edu
\par    DigiPen login: weijiekeith.lua
\par    Course: CSD-2125 HLP3
\date   3/2/2023
\brief
	This file is the implementation of a Grid Component

*/
/******************************************************************************/

#pragma once



#include "Thomas/AI/Node.h"
#include "Thomas/Math/Vector2D.h"
#include "Thomas/AI/AStarPathfindingObstacle.h"
namespace Thomas
{
    class Grid
    {
    public:



		//2D vector to represent the grid
		std::vector<std::vector<Node*>> nodeGrids;

		//Size of the grid
        Vec2 gridWorldSize;

		//Radius of the node.(Half-Width)
        float nodeRadius;

		//Diameter of the node. (Width)
        float nodeDiameter;

		//Width is the number of nodes that made up the width of the grid
        int gridWidth;

		//Height is the number of nodes that made up the height of the grid
        int gridHeight;

		//Origin of the grid
		Vec2 origin;
		


	};

	
	
	



}

//#endif
/******************************************************************************/
/*!
\file   AStarPathfindingObstacle.h
\author Keith Lua
\par    email: weijiekeith.lua\@digipen.edu
\par    DigiPen login: weijiekeith.lua
\par    Course: CSD-2125 HLP3
\date   3/2/2023
\brief
	This file is the implementation of a AStarPathfindingObstacle Component

*/
/******************************************************************************/

#pragma once


namespace Thomas
{


	class AStarPathfindingObstacle
	{
	public:

		//Flag to mark that the obstacle has been changed
		bool hasChanged = true;

		//Size of the obstacles
		Vec2 size;

		//Previous position of the obstacle
		Vec2 prevPosition;

		//Current Positon of the obstacle
		Vec2 position;

		//ID of the obstacle
		int ID = 0;

	};
	static int _id;
}

//#endif

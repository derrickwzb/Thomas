
#pragma once

//#include "thpch.h"

//#ifndef ASTARPATHFINDINGOBSTACLE_H
//#define ASTARPATHFINDINGOBSTACLE_H


namespace Thomas
{


	class AStarPathfindingObstacle
	{
	public:
		//Transform* seeker;
		bool hasChanged = true;
		Vec2 size;
		Vec2 prevPosition;
		Vec2 position;

		int ID = 0;

	};
	static int _id;
}

//#endif

//#include "main.h"

#include "Collision2D.hpp"

float g_dt = 5;
bool CollisionIntersection_RectRect(const Bounds & aabb1, const Vec2 &vel1,
									const Bounds& aabb2, const Vec2 &vel2)
{
	//Check for static collision detection between rectangles (before moving). 

	//bool overlapX = aabb1.max.x > aabb2.min.x && aabb1.min.x < aabb2.max.x;
	//bool overlapY = aabb2.max.y > aabb2.min.y && aabb1.min.y < aabb2.max.y;
	//
	//if (overlapX && overlapY) //Check if overlap in both x and y axis.
	//{
	//	return true;
	//}
	//aabb1
	
	bool xAxisNotColliding = (aabb1.max.x < aabb2.min.x) || (aabb1.min.x > aabb2.max.x);
	bool yAxisNotColliding = (aabb1.max.y < aabb2.min.y) || (aabb1.min.y > aabb2.max.y);

	if (xAxisNotColliding || yAxisNotColliding)
		return false;

	//Initialize and calculate the new velocity of Vb
	float tFirst = 0;
	float tLast = g_dt;

	Vec2 dFirst = { 0, 0 };
	Vec2 dLast = { 0, 0 };

	Vec2 velRel = { 0 , 0 };
	Vec2 velB = vel2;
	Vec2 velA = vel1;
	//Vector2DSUb(&velRel, &velB, &velA);
	velRel = velB - velA;

	//AEVec2Sub(&velA, &velA, &velA);

	velA -= velA;
	if (velRel.x == 0.0f && velRel.y == 0.0f)
		return true;

	if (velRel.x < 0) ///ALONG X AXIS OBJECT MOVING TO LEFT
	{
		
		if (aabb1.min.x > aabb2.max.x) //Object 2 moving away from Object 1
		{
			return false;
		}
		if (aabb1.max.x < aabb2.min.x) //Object 2 moving towards Object 1
		{
			dFirst.x = aabb1.max.x - aabb2.min.x;
			if ((dFirst.x / velRel.x) > tFirst)  //Check for Maximum tFirst
			{
				tFirst = dFirst.x / velRel.x;
			}
		}
		if (aabb1.min.x < aabb2.max.x) //Object 2 moving towards Object 1
		{
			dLast.x = aabb1.min.x - aabb2.max.x;
			if ((dLast.x / velRel.x) < tLast) //Check for Minimum tLast
			{
				tLast = dLast.x / velRel.x;
			}
		}
	}
	if (velRel.x > 0)  ///ALONG X AXIS OBJECT MOVING TO RIGHT
	{

		if (aabb1.min.x > aabb2.max.x) //Object 2 moving towards Object 1
		{
			dFirst.x = aabb1.min.x - aabb2.max.x;
			if ((dFirst.x / velRel.x) > tFirst) //Check for Maximum tFirst
			{
				tFirst = dFirst.x / velRel.x;
			}
		}
		if (aabb1.max.x > aabb2.min.x) //Object 2 moving towards Object 1
		{
			dLast.x = aabb1.max.x - aabb2.min.x;
			if ((dLast.x / velRel.x) < tLast) //Check for Minimum tLast
			{
				tLast = dLast.x / velRel.x;
			}
		}
		if (aabb1.max.x < aabb2.min.x) //Object 2 moving away from Object 1
		{
			return false;
		}

	}
	//if (velRel.x == 0)  //Check if one of the game object is static
	//{
	//	if (overlapX == false)  //Check if overlap is false
	//	{
	//		return false;
	//	}
	//	
	//}

	if (velRel.y < 0)  ///ALONG Y AXIS OBJECT MOVING DOWN
	{
		if (aabb1.min.y > aabb2.max.y) //Object 2 moving away from Object 1
		{
			return false;
		}
		if (aabb1.max.y < aabb2.min.y)
		{
			dFirst.y = aabb1.max.y - aabb2.min.y;
			if ((dFirst.y / velRel.y) > tFirst) //Check for Maximum tFirst
			{
				tFirst = dFirst.y / velRel.y;
			}
		}
		if (aabb1.min.y < aabb2.max.y) //Check for Minimum tLast
		{
			dLast.y = aabb1.min.y - aabb2.max.y;
			if ((dLast.y / velRel.y) < tLast)
			{
				tLast = dLast.y / velRel.y;
			}
		}
	}
	if (velRel.y > 0)  ///ALONG Y AXIS OBJECT MOVING UP
	{
		if (aabb1.min.y > aabb2.max.y) //Object 2 moving towards Object 1
		{
			dFirst.y = aabb1.min.y - aabb2.max.y;
			if ((dFirst.y / velRel.y) > tFirst) //Check for Maximum tFirst
			{
				tFirst = dFirst.y / velRel.y;
			}
		}
		if (aabb1.max.y > aabb2.min.y) //Object 2 moving towards Object 1
		{
			dLast.y = aabb1.max.y - aabb2.min.y;
			if ((dLast.y / velRel.y) < tLast) //Check for Minimum tLast
			{
				tLast = dLast.y / velRel.y;
			}
		}
		if (aabb1.max.y < aabb2.min.y) //Object 2 moving away from Object 1
		{
			return false;
		}
	}

	//if (velRel.y == 0) //Check if one of the game object is static
	//{
	//	if (overlapY == false) //Check if overlap is false
	//	{
	//		return false;
	//	}
	//}

	if (tFirst > tLast) //This is false as it does not make sense 
	{
		return false;
	}
	return true;

}


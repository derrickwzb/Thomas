/******************************************************************************/
/*!
\file		Collision2D.hpp
\author 	Keith Lua, weijiekeith.lua, 2101223
\par    	email: weijiekeith.lua\@digipen.edu
\date   	25/9/2022
\brief		This file represents the interface of the source file
			Collision2D.cpp, it contains the function prototype declarations
			and class definition. The Collision2D class contains all the
			collision details of two colliding objects.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/
#pragma once
#include "Thomas/Math/Math.hpp"
#include "CircleCollider2D.hpp"
#include "LineSegment.hpp"
#include "Ray.hpp"

#ifndef COLLISION2D_H_
#define COLLISION2D_H_

namespace Thomas
{
	class Collision2D
	{

	public:

		Bounds temp;
		Vec2 relativeVelocity;
		Collider2D otherCollider;
		bool enabled;
	};

	/**************************************************************************/
	/*!
		This function checks for collision between two game objects of
		rectangle shape. It tests for static collision between two game objects
		and if there's an overlap, before testing for collision between the
		two moving objects. It returns true if there is a collision and
		false if there isn't.
	*/
	/**************************************************************************/
	bool CollisionIntersection_RectRect(const Bounds& aabb1, const Vec2& vel1,
		const Bounds& aabb2, const Vec2& vel2);


	/******************************************************************************/
	/*!
		This function will check for the intersection betweeen two circles, then
		and return true if the conditons are met.
		It calculates then updates the corresponding parameters based on the
		physics.
	 */
	 /******************************************************************************/
	bool CollisionIntersection_CircleCircle(const CircleCollider2D& circleA, const Vector2D& velA,
		const CircleCollider2D& circleB, const Vector2D& velB,
		Vector2D& interPtA, Vector2D& interPtB,
		float& interTime);


	/******************************************************************************/
	/*!
		This function will check for the intersection betweeen a ray and a circle
		and return true if the conditons are met.
		It calculates then updates the interTime value based on the other two
		parameters.
	 */
	 /******************************************************************************/
	bool CollisionIntersection_RayCircle(const Ray& ray, const CircleCollider2D& circle, float& interTime);


	/******************************************************************************/
	/*!
		This function will check for collision between circle and line segment
		then returns true if the conditons are met.
		It calculates then updates the corresponding parameters based on the
		physics.
	 */
	 /******************************************************************************/
	bool CollisionIntersection_CircleLineSegment(const CircleCollider2D& circle, const Vector2D& ptEnd,
		const LineSegment& lineSeg, Vector2D& interPt,
		Vector2D& normalAtCollision, float& interTime,
		bool& checkLineEdges);


	/******************************************************************************/
	/*!
	*	This function will check for collision between cicle and line's edge,
		then returns true if the conditons are met.
		It calculates then updates the corresponding parameters based on the
		physics.
	*/
	/******************************************************************************/
	bool CheckMovingCircleToLineEdge(bool withinBothLines, const CircleCollider2D& circle,
		const Vector2D& ptEnd, const LineSegment& lineSeg, Vector2D& interPt,
		Vector2D& normalAtCollision, float& interTime);




	/******************************************************************************/
	/*!
		This function will calculate new values as a response to a
		circle to pillar colllision then updates the parameters accorrdingly
		to create a reflection effect.
	 */
	 /******************************************************************************/
	void CollisionResponse_CirclePillar(const Vec2& normal,
		const float& interTime,
		const Vec2& ptStart,
		const Vec2& ptInter,
		Vec2& ptEnd,
		Vec2& reflectedVectorNormalized);





	/******************************************************************************/
	/*!
		This function will calculate new values as a response to a
		circle to circle colllision then updates the parameters accorrdingly
		to create a reflection effect.
	 */
	 /******************************************************************************/
	void CollisionResponse_CircleCircle(Vec2& normal,
		const float interTime,
		Vec2& velA,
		const float& massA,
		Vec2& interPtA,
		Vec2& velB,
		const float& massB,
		Vec2& interPtB,
		Vec2& reflectedVectorA,
		Vec2& ptEndA,
		Vec2& reflectedVectorB,
		Vec2& ptEndB);

	//bool CollisionIntersection_RectRect(const Bounds& aabb1, const Vec2& vel1, const Bounds& aabb2, const Vec2& vel2);

	//SAT Collision Detection is used to check for intersection between two polygons
	bool SATPolygonIntersection(std::vector<Vec2>& verticesA, std::vector<Vec2>& verticesB, Vec2& normal, float& depth);

	//This functions will projectthe vertices onto an axis and then obtain the 
	//minimum and maximum length of the projection
	void ProjectVertices(std::vector<Vec2>& vertices, Vec2& axis, float& min, float& max);

	//This function will allows us to find the centre of the polygon.
	Vec2 FindArithmeticMean(std::vector<Vec2>& vertices);

	//This functions will project the vertices onto an axis and then obtain the 
	//minimum and maximum length of the projection
	void UpdateVertices(std::vector<Vec2>& vertices, Mtx33 matrix);
	
}

#endif

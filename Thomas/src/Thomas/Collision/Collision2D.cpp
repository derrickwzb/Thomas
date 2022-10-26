/******************************************************************************/
/*!
\file		Collision2D.cpp
\author 	Keith Lua, weijiekeith.lua, 2101223
\par    	email: weijiekeith.lua\@digipen.edu
\date   	25/9/2022
\brief		This file represents the implementation of functions
			and class specified in interface (header) file Collision2D.hpp. 
			The file consists of functions that check for 
			collision/intersection between two objects.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/
#include "thpch.h"
#include "Collision2D.hpp"
#include <cmath>

namespace Thomas
{
	float g_dt = 5;

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
		const Bounds& aabb2, const Vec2& vel2)
	{
		//Check for static collision detection between rectangles (before moving). 
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
		velRel = velB - velA;

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

		if (tFirst > tLast) //This is false as it does not make sense 
		{
			return false;
		}
		return true;

	}



	/******************************************************************************/
	/*!
		This function will check for collision between circle and line segment
		then returns true if the conditons are met.
		It calculates then updates the corresponding parameters based on the
		physics.
	 */
	 /******************************************************************************/
	bool CollisionIntersection_CircleLineSegment(const CircleCollider2D& circle,
		const Vec2& ptEnd,
		const LineSegment& lineSeg,
		Vec2& interPt,
		Vec2& normalAtCollision,
		float& interTime,
		bool& checkLineEdges)
	{

		//Bs = position of circle(circle.bounds.centre) at start
		//Be = end position/point of the circle(ptEnd)
		//Bi = intersection position/point(interPt)
		//R = radius of the circle(circle.radius)
		//V = Be - Bs
		//N = normalized normal of line segment(lineSeg.normal)
		//M = outward normal to V 

		//Velocity = Be - Bs
		Vec2 velocity = ptEnd - circle.bounds.centre;

		//M = outward normal to V 
		Vec2 velOutwardNormal;
		velOutwardNormal.x = velocity.y;
		velOutwardNormal.y = -velocity.x;

		//N.Bs - N.P0 <= -R
		float NdotBs_Sub_NdotP0 = Vector2DDotProduct(lineSeg.normal, circle.bounds.centre) -
			Vector2DDotProduct(lineSeg.normal, lineSeg.point0);

		if (NdotBs_Sub_NdotP0 <= -circle.radius) //Check if circle starting from inside half space
		{
			//P0' = P0 - R * N
			Vec2 P0_prime = lineSeg.point0 - circle.radius * lineSeg.normal;

			//P1' = P1 - R * N
			Vec2 P1_prime = lineSeg.point1 - circle.radius * lineSeg.normal;


			//M.BsP0'
			float MdotBsP0Prime = Vector2DDotProduct(velOutwardNormal, P0_prime - circle.bounds.centre);

			//M.BsP1'
			float MdotBsP1Prime = Vector2DDotProduct(velOutwardNormal, P1_prime - circle.bounds.centre);

			//if ( M.BsP0' * M.BsP1' <  0 )
			if ((MdotBsP0Prime * MdotBsP1Prime) < 0)
			{
				//(N.V)
				float NdotV = Vector2DDotProduct(lineSeg.normal, velocity);
				if (NdotV == 0)
				{
					return false;
				}
				//Ti = ( N.P0 - N.Bs - R) / (N.V)
				float NdotP0 = Vector2DDotProduct(lineSeg.normal, lineSeg.point0);
				float NdotBs = Vector2DDotProduct(lineSeg.normal, circle.bounds.centre);
				interTime = (NdotP0 - NdotBs - circle.radius) / NdotV;

				//If (0 <= Ti <= 1)
				if (interTime >= 0 && interTime <= 1)
				{
					//Bi = Bs + V * Ti
					interPt = circle.bounds.centre + velocity * interTime;

					//Normal of reflection = -N
					normalAtCollision = -lineSeg.normal;

					//Collision
					return true;
				}

			}
			else
			{
				checkLineEdges = false;
				return CheckMovingCircleToLineEdge(checkLineEdges, circle, ptEnd,
					lineSeg, interPt, normalAtCollision, interTime);

			}

		}
		else if (NdotBs_Sub_NdotP0 >= circle.radius) //Check if circle starting from outside half space
		{
			//P0' = P0 + R * N
			Vec2 P0_prime = lineSeg.point0 + circle.radius * lineSeg.normal;

			//P1' = P1 + R * N
			Vec2 P1_prime = lineSeg.point1 + circle.radius * lineSeg.normal;


			//if ( M.BsP0' * M.BsP1' <  0 )
			float MdotBsP0Prime = Vector2DDotProduct(velOutwardNormal, P0_prime - circle.bounds.centre);
			float MdotBsP1Prime = Vector2DDotProduct(velOutwardNormal, P1_prime - circle.bounds.centre);

			if (MdotBsP0Prime * MdotBsP1Prime < 0)
			{
				float NdotV = Vector2DDotProduct(lineSeg.normal, velocity);
				if (NdotV == 0)
				{
					return false;
				}
				//Ti = ( N.P0 - N.Bs + R) / (N.V)
				float NdotP0 = Vector2DDotProduct(lineSeg.normal, lineSeg.point0);
				float NdotBs = Vector2DDotProduct(lineSeg.normal, circle.bounds.centre);

				interTime = (NdotP0 - NdotBs + circle.radius) / NdotV;

				//If (0 <= Ti <= 1)
				if (interTime >= 0 && interTime <= 1)
				{
					//Bi = Bs + V * Ti
					interPt = circle.bounds.centre + velocity * interTime;

					//Normal of reflection = N
					normalAtCollision = lineSeg.normal;

					//Collision
					return true;
				}

			}
			else
			{
				checkLineEdges = false;
				return CheckMovingCircleToLineEdge(checkLineEdges, circle, ptEnd,
					lineSeg, interPt, normalAtCollision, interTime);

			}
		}
		else
		{
			checkLineEdges = true;
			return CheckMovingCircleToLineEdge(checkLineEdges, circle, ptEnd,
				lineSeg, interPt, normalAtCollision, interTime);

		}

		return false; // no intersection
	}



	/******************************************************************************/
	/*!
	*	This function will check for collision between cicle and line's edge,
		then returns true if the conditons are met.
		It calculates then updates the corresponding parameters based on the
		physics.
	*/
	/******************************************************************************/
	bool CheckMovingCircleToLineEdge(bool withinBothLines,
		const CircleCollider2D& circle,
		const Vec2& ptEnd,
		const LineSegment& lineSeg,
		Vec2& interPt,
		Vec2& normalAtCollision,
		float& interTime)
	{

		//V = Be - Bs
		Vec2 velocity = ptEnd - circle.bounds.centre;

		//Vhat or V Normallized
		Vec2 velocityNormalized;
		Vector2DNormalize(velocityNormalized, velocity);


		if (withinBothLines)
		{
			//BsP0 = P0 - Bs
			Vec2 BsP0 = lineSeg.point0 - circle.bounds.centre;

			//BsP0 = P1 - P0
			Vec2 P0P1 = lineSeg.point1 - lineSeg.point0;
			//P0 side
			if (Vector2DDotProduct(BsP0, P0P1) > 0) //P0 side
			{
				//If BsP0.Vhat
				float BsP0dotVhat = Vector2DDotProduct(BsP0, velocityNormalized);

				//If BsP0.Vhat < 0
				if (BsP0dotVhat < 0)
				{
					return false;
				}


				//m > 0
				if (BsP0dotVhat > 0)
				{
					Vec2 velocityOutwardNormal{ velocity.y, -velocity.x };

					//M = Normalized outward normal of V 
					Vec2 velocityOutwardNormalNormalized;
					Vector2DNormalize(velocityOutwardNormalNormalized, velocityOutwardNormal);

					//float dist0 = BsP0.M
					float shortestDist = Vector2DDotProduct(BsP0, velocityOutwardNormalNormalized);

					//abs(dist0) > R
					if (abs(shortestDist) > circle.radius)
					{
						//No collision
						return false;
					}

					//s = sqrt(R*R - dist0*dist0)
					float perpendicularDist = sqrtf(circle.radius * circle.radius - shortestDist * shortestDist);

					//V.Length();	
					float lengthOfVelocity = Vector2DLength(velocity);

					if (lengthOfVelocity == 0)
					{
						return false;
					}
					//float ti = (m ?s) / V.Length();
					interTime = (BsP0dotVhat - perpendicularDist) / lengthOfVelocity;

					//If ti <= 1
					if (interTime <= 1)
					{
						//Bi = Bs + V * ti
						interPt = circle.bounds.centre + velocity * interTime;

						//P0Bi = Bi - P0
						Vec2 P0Bi = interPt - lineSeg.point0;

						//Normal of reflection is P0Bi normalized
						Vector2DNormalize(normalAtCollision, P0Bi);



						return true;


					}

				}

			}
			else
			{
				//m = BsP1.VhatVec2 velocityNormalized;
				Vector2DNormalize(velocityNormalized, velocity);

				//BsP0 = P0 - Bs
				Vec2 BsP1 = lineSeg.point1 - circle.bounds.centre;

				//BsP1.V hat
				float BsP1dotVhat = Vector2DDotProduct(BsP1, velocityNormalized);

				//BsP1.V hat
				if (BsP1dotVhat < 0) /* No collision */
				{
					return false;
				}
				//m > 0
				if (BsP1dotVhat > 0)
				{
					//Normalized outward normal of V 
					Vec2 velocityOutwardNormalNormalized{ velocityNormalized.y, -velocityNormalized.x };

					//float dist0 = BsP1.M
					float shortestDist = Vector2DDotProduct(BsP1, velocityOutwardNormalNormalized);

					//abs(dist1) > R
					if (abs(shortestDist) > circle.radius)
					{
						//No collision
						return false;
					}

					//s = sqrt(R*R - dist0*dist0)
					float perpendicularDist = sqrtf(circle.radius * circle.radius - shortestDist * shortestDist);

					//V.Length();
					float lengthOfVelocity = Vector2DLength(velocity);
					if (lengthOfVelocity == 0)
					{
						return false;
					}
					//float ti = (m ?s) / V.Length();
					interTime = (BsP1dotVhat - perpendicularDist) / lengthOfVelocity;

					//If ti <= 1
					if (interTime <= 1)
					{
						//Bi = Bs + V * ti
						interPt = circle.bounds.centre + velocity * interTime;

						//P1Bi = Bi - P1
						Vec2 P1Bi = interPt - lineSeg.point1;

						//Normal of reflection is P1Bi normalized
						Vector2DNormalize(normalAtCollision, P1Bi);

						return true;
					}
				}
			}
		}
		else
		{



			bool P0Side = false;
			//BsP1 = P0 - Bs
			Vec2 BsP0 = lineSeg.point0 - circle.bounds.centre;
			//BsP1 = P1 - Bs
			Vec2 BsP1 = lineSeg.point1 - circle.bounds.centre;

			//M is normalized outward normal of  V
			Vec2 velocityOutwardNormalNormalized{ velocityNormalized.y, -velocityNormalized.x };

			//float dist0 = BsP0.M
			float shortestDistP0Side = Vector2DDotProduct(BsP0, velocityOutwardNormalNormalized);

			//float dist1 = BsP1.M
			float shortestDistP1Side = Vector2DDotProduct(BsP1, velocityOutwardNormalNormalized);

			//abs dist0
			float shortestDistP0Side_Abs = abs(shortestDistP0Side);

			//abs dist1
			float shortestDistP1Side_Abs = abs(shortestDistP1Side);


			if (shortestDistP0Side_Abs > circle.radius && shortestDistP1Side_Abs > circle.radius)
			{
				return false;
			}
			else if (shortestDistP0Side_Abs <= circle.radius && shortestDistP1Side_Abs <= circle.radius)
			{
				//float m0 = BsP0.Vhat
				float BsP0dotVhat = Vector2DDotProduct(BsP0, velocityNormalized);

				//float m1 = BsP1.Vhat
				float BsP1dotVhat = Vector2DDotProduct(BsP1, velocityNormalized);

				//float m0_absoluteValue = abs(m0)
				float BsP0dotVhat_Abs = abs(BsP0dotVhat);

				//float m1_absoluteValue = abs(m1)
				float BsP1dotVhat_Abs = abs(BsP1dotVhat);


				if (BsP0dotVhat_Abs < BsP1dotVhat_Abs)
				{
					P0Side = true;
				}
				else
				{
					P0Side = false;
				}
			}
			else if (shortestDistP0Side_Abs <= circle.radius)
			{
				P0Side = true;
			}
			else
			{
				P0Side = false;
			}
			if (P0Side)
			{
				//BsP0.Vhat
				float BsP0dotVhat = Vector2DDotProduct(BsP0, velocityNormalized);

				//BsP0.V hat < 0
				if (BsP0dotVhat < 0)
				{
					return false;
				}
				else
				{
					//s = sqrt(R*R - dist0*dist0)
					float perpendicularDist = sqrtf(circle.radius * circle.radius - shortestDistP0Side * shortestDistP0Side);

					//V.Length();
					float lengthOfVelocity = Vector2DLength(velocity);

					if (lengthOfVelocity == 0)
					{
						return false;
					}

					//float ti = (m ?s) / V.Length();
					interTime = (BsP0dotVhat - perpendicularDist) / lengthOfVelocity;

					//If ti <= 1
					if (interTime <= 1)
					{
						//Bi = Bs + V * ti
						interPt = circle.bounds.centre + velocity * interTime;

						//P1Bi = Bi - P1
						Vec2 P0Bi = interPt - lineSeg.point0;

						//Normal of reflection is P1Bi normalized
						Vector2DNormalize(normalAtCollision, P0Bi);

						return true;
					}
				}
			}
			else
			{
				//BsP1.V hat
				float BsP1dotVhat = Vector2DDotProduct(BsP1, velocityNormalized);

				//BsP1.V hat < 0 
				if (BsP1dotVhat < 0)
				{
					return false;
				}
				else
				{
					//s = sqrt(R*R - dist0*dist0)
					float perpendicularDist = sqrtf(circle.radius * circle.radius - shortestDistP1Side * shortestDistP1Side);

					//V.Length();
					float lengthOfVelocity = Vector2DLength(velocity);

					if (lengthOfVelocity == 0)
					{
						return false;
					}
					//float ti = (m ?s) / V.Length();
					interTime = (BsP1dotVhat - perpendicularDist) / lengthOfVelocity;

					//If ti <= 1
					if (interTime <= 1)
					{
						//Bi = Bs + V * ti
						interPt = circle.bounds.centre + velocity * interTime;

						//P1Bi = Bi - P1
						Vec2 P1Bi = interPt - lineSeg.point1;

						//Normal of reflection is P1Bi normalized
						Vector2DNormalize(normalAtCollision, P1Bi);

						return true;
					}
				}
			}
		}
		return false;
	}



	/******************************************************************************/
	/*!
		This function will check for the intersection betweeen two circles, then
		and return true if the conditons are met.
		It calculates then updates the corresponding parameters based on the
		physics.
	 */
	 /******************************************************************************/
	bool CollisionIntersection_CircleCircle(const CircleCollider2D& circleA,
		const Vec2& velA,
		const CircleCollider2D& circleB,
		const Vec2& velB,
		Vec2& interPtA,
		Vec2& interPtB,
		float& interTime)
	{
		Ray ray;
		ray.direction = velA - velB;
		ray.origin = circleA.bounds.centre;
		CircleCollider2D staticCircle = circleB;
		staticCircle.radius += circleA.radius;
		if (CollisionIntersection_RayCircle(ray, staticCircle, interTime))
		{
			//BiA = BsA + V * Ti
			interPtA = circleA.bounds.centre + velA * interTime;
			//BiB = BsB + V * Ti
			interPtB = circleB.bounds.centre + velB * interTime;
			return true;
		}
		return false;


	}



	/******************************************************************************/
	/*!
		This function will check for the intersection betweeen a ray and a circle
		and return true if the conditons are met.
		It calculates then updates the interTime value based on the other two
		parameters.
	 */
	 /******************************************************************************/
	bool CollisionIntersection_RayCircle(const Ray& ray,
		const CircleCollider2D& circle,
		float& interTime)
	{
		//BsC = C - Bs
		Vec2 BsC = circle.bounds.centre - ray.origin;

		//V hat or V normalized
		Vec2 velocityNormalized;
		Vector2DNormalize(velocityNormalized, ray.direction);

		//m = BsC.Vhat
		float BsCdotVhat = Vector2DDotProduct(BsC, velocityNormalized);

		//BsC.Vhat < 0
		if (BsCdotVhat < 0)
		{
			return false;
		}
		//m > 0
		if (BsCdotVhat > 0)
		{
			//M = Normalized outward normal of V 
			Vec2 velocityOutwardNormalNormalized{ velocityNormalized.y, -velocityNormalized.x };

			//float dist0 = BsC.M
			float shortestDist = Vector2DDotProduct(BsC, velocityOutwardNormalNormalized);

			//abs(dist0) > R
			if (abs(shortestDist) > circle.radius)
			{
				//No collision
				return false;
			}

			//s = sqrt(R*R - dist0*dist0)
			float perpendicularDist = sqrtf(circle.radius * circle.radius - shortestDist * shortestDist);

			//|| V ||  ( V.Length())
			float lengthOfVelocity = Vector2DLength(ray.direction);
			if (lengthOfVelocity == 0)
			{
				return false;
			}
			//s >= 0
			if (perpendicularDist >= 0)
			{
				//float ti = (m ?s) / ||V||
				interTime = (BsCdotVhat - perpendicularDist) / lengthOfVelocity;

				if (interTime <= 1 && interTime >= 0)
				{
					return true;
				}
			}
		}
		return false;
	}



	/******************************************************************************/
	/*!
		This function will calculate new values as a response to a
		circle to line segment colllision then updates the parameters accorrdingly
		to create a reflection effect.
	 */
	 /******************************************************************************/
	void CollisionResponse_CircleLineSegment(const Vec2& ptInter,
		const Vec2& normal,
		Vec2& ptEnd,
		Vec2& reflected)
	{

		//i = Be - Bi
		Vec2 penetration = ptEnd - ptInter;

		//R = i - 2 * (i.N) * N
		Vec2 reflectedUnnormalized = penetration - 2 * Vector2DDotProduct(penetration, normal) * normal;


		//Be = Bi + R
		ptEnd = ptInter + reflectedUnnormalized;

		//Normalized of the reflected vector
		Vector2DNormalize(reflected, ptEnd - ptInter);
	}



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
		Vec2& reflectedVectorNormalized)
	{
		//UNREFERENCED_PARAMETER(ptStart);
		//UNREFERENCED_PARAMETER(interTime);

		//i = Be - Bi
		Vec2 penetration = ptEnd - ptInter;

		//R = i - 2 * (i.N) * N
		Vec2 reflectedUnnormalized = penetration - 2 * Vector2DDotProduct(penetration, normal) * normal;

		//Be = Bi + R
		ptEnd = ptInter + reflectedUnnormalized;

		//Normalized of the reflected vector
		Vector2DNormalize(reflectedVectorNormalized, reflectedUnnormalized);
	}



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
		Vec2& ptEndB)
	{
		//d = BiA - BiB noraml vector between two circles.
		Vec2 normalVector = interPtA - interPtB;

		//d hat or d normalized
		Vec2 normalVectorNormalized;
		Vector2DNormalize(normalVectorNormalized, normalVector);

		//Change of coordinate system
		//aA = CA.d
		float CaDotN = Vector2DDotProduct(velA, normal);
		//aB = CB.d
		float CbDotN = Vector2DDotProduct(velB, normal);

		//        Relative Projected Velocity 
		//||P|| = 2*ma*mb*(aA - aB) / mA + mB
		float changeInMomentum = 2.0f * massA * massB * (CaDotN - CbDotN) / (massA + massB);

		//cA' = cA - (2(aA - aB)/mA + mB)mb * d
		reflectedVectorA = velA - (changeInMomentum / massA) * normalVectorNormalized;

		//cB' = cB + (2(aA - aB)/mA + mB)mb * d
		reflectedVectorB = velB + (changeInMomentum / massB) * normalVectorNormalized;

		//            kA = ||cA'||
		//BeA = BiA + kAcA'(te - ti) 
		//float lengthOfReflectedVectorA = Vector2DLength(reflectedVectorA);
		ptEndA = interPtA + reflectedVectorA * (1.0f - interTime);

		//            kB = ||cB'||
		//BeB = BiB + kBcB'(te - ti) 
		//float lengthOfReflectedVectorB = Vector2DLength(reflectedVectorB);
		ptEndB = interPtB + reflectedVectorB * (1.0f - interTime);
	}
	bool SATPolygonIntersection(std::vector<Vec2>& verticesA, std::vector<Vec2>& verticesB, Vec2& normal, float& depth)
	{
		Vector2DZero(normal);
		depth = std::numeric_limits<float>::max();

		for (int i = 0; i < (int)(verticesA.size()); ++i)
		{
			Vec2 edge = verticesA[(i + 1) % (int)(verticesA.size())] - verticesA[i];
			Vec2 axis(-(edge.y), edge.x);
			Vector2DNormalize(axis, axis);
			float maxA;
			float minA;
			float maxB;
			float minB;
			ProjectVertices(verticesA, axis, minA, maxA);
			ProjectVertices(verticesB, axis, minB, maxB);
			if (minA >= maxB || minB >= maxA)
			{
				return false;
			}

			float axisDepth = Min(maxB - minA, maxA - minB);
			if (axisDepth < depth)
			{
				depth = axisDepth;
				normal = axis;
			}

		}
		for (int i = 0; i < (int)(verticesB.size()); ++i)
		{
			Vec2 edge = verticesB[(i + 1) % (int)(verticesB.size())] - verticesB[i];
			Vec2 axis(-(edge.y), edge.x);
			Vector2DNormalize(axis, axis);
			float maxA;
			float minA;
			float maxB;
			float minB;
			ProjectVertices(verticesA, axis, minA, maxA);
			ProjectVertices(verticesB, axis, minB, maxB);
			if (minA >= maxB || minB >= maxA)
			{
				return false;
			}
			float axisDepth = Min(maxB - minA, maxA - minB);
			if (axisDepth < depth)
			{
				depth = axisDepth;
				normal = axis;
			}

		}

		depth /= Vector2DLength(normal);


		Vec2 centerA = FindArithmeticMean(verticesA);
		Vec2 centerB = FindArithmeticMean(verticesB);
		Vec2 direction = centerB - centerA;
		if (Vector2DDotProduct(direction, normal) < 0.f)
		{
			normal = -normal;

		}

		return true;

	}

	void ProjectVertices(std::vector<Vec2>& vertices, Vec2& axis, float& min, float& max)
	{
		/*std::vector<float> projectedA;
		std::vector<float> projectedB;*/
		max = std::numeric_limits<float>::min();
		min = std::numeric_limits<float>::max();

		for (int i = 0; i < (int)(vertices.size()); ++i)
		{
			float proj = Vector2DDotProduct(axis, vertices[i]);
			if (proj > max)
			{
				max = proj;
			}
			if (proj < min)
			{
				min = proj;
			}
		}


	}

	Vec2 FindArithmeticMean(std::vector<Vec2>& vertices)
	{
		float sumX = 0.f;
		float sumY = 0.f;
		for (int i = 0; i < (int)(vertices.size()); ++i)
		{
			sumX += vertices[i].x;
			sumY += vertices[i].y;
		}
		return Vec2(sumX / (float)(vertices.size()), sumY / (float)(vertices.size()));

	}

	void UpdateVertices(std::vector<Vec2>& vertices, Mtx33 matrix)
	{
		for (int i = 0; i < (int)(vertices.size()); ++i)
		{
			vertices[i] = matrix * vertices[i];
		}
	}
}

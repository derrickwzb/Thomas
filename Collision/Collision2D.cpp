#include "Collision2D.hpp"
#include "../Math/Math.hpp"

bool Collision2D::CollisionIntersection_RectRect(const Bounds & aabb1, const Vector2D &vel1,
									const Bounds& aabb2, const Vector2D &vel2)
{
	//Check for static collision detection between rectangles (before moving). 

	bool xAxisNotColliding = (aabb1.max.x < aabb2.min.x) || (aabb1.min.x > aabb2.max.x);
	bool yAxisNotColliding = (aabb1.max.y < aabb2.min.y) || (aabb1.min.y > aabb2.max.y);

	if (xAxisNotColliding || yAxisNotColliding)
		return false;

	//aabb1
	
	//Initialize and calculate the new velocity of Vb
	float tFirst = 0;
	float tLast = g_dt;

	Vector2D dFirst = { 0, 0 };
	Vector2D dLast = { 0, 0 };

	Vector2D velRel = { 0 , 0 };
	Vector2D velB = vel2;
	Vector2D velA = vel1;
	//Vector2DSUb(&velRel, &velB, &velA);
	velRel = velB - velA;

	//AEVec2Sub(&velA, &velA, &velA);

	velA -= velA;


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
	if (velRel.x == 0)  //Check if one of the game object is static
	{
		if (overlapX == false)  //Check if overlap is false
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

	if (velRel.y == 0) //Check if one of the game object is static
	{
		if (overlapY == false) //Check if overlap is false
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
//Temporay Commented off
 
/******************************************************************************/
/*!
	This function will check for the intersection betweeen two circles, then
	and return true if the conditons are met.
	It calculates then updates the corresponding parameters based on the
	physics.
 */
 /******************************************************************************/
bool Collision2D::CollisionIntersection_CircleCircle(const CircleCollider2D& circleA,
	const Vector2D& velA,
	const CircleCollider2D& circleB,
	const Vector2D& velB,
	Vector2D& interPtA,
	Vector2D& interPtB,
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
	Vector2D BsC = circle.bounds.centre - ray.origin;

	//V hat or V normalized
	Vector2D velocityNormalized;
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
		Vector2D velocityOutwardNormalNormalized{ velocityNormalized.y, -velocityNormalized.x };

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
			return 0;
		}
		//s >= 0
		if (perpendicularDist >= 0)
		{
			//float ti = (m – s) / ||V||
			interTime = (BsCdotVhat - perpendicularDist) / lengthOfVelocity;

			if (interTime <= 1 && interTime >= 0)
			{
				return true;
			}
		}
	}
	return false;


}


int CollisionIntersection_CircleLineSegment(const CircleCollider2D& circle,
	const Vector2D& ptEnd,
	const LineSegment& lineSeg,
	Vector2D& interPt,
	Vector2D& normalAtCollision,
	float& interTime,
	bool& checkLineEdges)
{

	//Bs = position of circle(circle.m_center) at start
	//Be = end position/point of the circle(ptEnd)
	//Bi = intersection position/point(interPt)
	//R = radius of the circle(circle.m_radius)
	//V = Be - Bs
	//N = normalized normal of line segment(lineSeg.m_normal)
	//M = outward normal to V 

	//Velocity = Be - Bs
	Vector2D velocity = ptEnd - circle.bounds.centre;

	//M = outward normal to V 
	Vector2D velOutwardNormal;
	velOutwardNormal.x = velocity.y;
	velOutwardNormal.y = -velocity.x;

	//N.Bs - N.P0 <= -R
	float NdotBs_Sub_NdotP0 = Vector2DDotProduct(lineSeg.normal, circle.bounds.centre) -
		Vector2DDotProduct(lineSeg.normal, lineSeg.point0);

	if (NdotBs_Sub_NdotP0 <= -circle.radius) //Check if circle starting from inside half space
	{
		//P0' = P0 - R * N
		Vector2D P0_prime = lineSeg.m_pt0 - circle.radius * lineSeg.m_normal;

		//P1' = P1 - R * N
		Vector2D P1_prime = lineSeg.m_pt1 - circle.radius * lineSeg.m_normal;


		//M.BsP0'
		float MdotBsP0Prime = Vector2DDotProduct(velOutwardNormal, P0_prime - circle.bounds.centre);

		//M.BsP1'
		float MdotBsP1Prime = Vector2DDotProduct(velOutwardNormal, P1_prime - circle.bounds.centre);

		//if ( M.BsP0' * M.BsP1' <  0 )
		if ((MdotBsP0Prime * MdotBsP1Prime) < 0)
		{
			//(N.V)
			float NdotV = Vector2DDotProduct(lineSeg.m_normal, velocity);
			if (NdotV == 0)
			{
				return 0;
			}
			//Ti = ( N.P0 - N.Bs - R) / (N.V)
			float NdotP0 = Vector2DDotProduct(lineSeg.m_normal, lineSeg.m_pt0);
			float NdotBs = Vector2DDotProduct(lineSeg.m_normal, circle.bounds.centre);
			interTime = (NdotP0 - NdotBs - circle.radius) / NdotV;

			//If (0 <= Ti <= 1)
			if (interTime >= 0 && interTime <= 1)
			{
				//Bi = Bs + V * Ti
				interPt = circle.bounds.centre + velocity * interTime;

				//Normal of reflection = -N
				normalAtCollision = -lineSeg.m_normal;

				//Collision
				return 1;
			}

		}
		else
		{
			checkLineEdges = false;
			return CheckMovingCircleToLineEdge(checkLineEdges, circle, ptEnd,
				lineSeg, interPt, normalAtCollision, interTime);

		}

	}
	else if (NdotBs_Sub_NdotP0 >= circle.m_radius) //Check if circle starting from outside half space
	{
		//P0' = P0 + R * N
		Vector2D P0_prime = lineSeg.m_pt0 + circle.radius * lineSeg.m_normal;

		//P1' = P1 + R * N
		Vector2D P1_prime = lineSeg.m_pt1 + circle.radius * lineSeg.m_normal;


		//if ( M.BsP0' * M.BsP1' <  0 )
		float MdotBsP0Prime = Vector2DDotProduct(velOutwardNormal, P0_prime - circle.bounds.centre);
		float MdotBsP1Prime = Vector2DDotProduct(velOutwardNormal, P1_prime - circle.bounds.centre);

		if (MdotBsP0Prime * MdotBsP1Prime < 0)
		{
			float NdotV = Vector2DDotProduct(lineSeg.m_normal, velocity);
			if (NdotV == 0)
			{
				return 0;
			}
			//Ti = ( N.P0 - N.Bs + R) / (N.V)
			float NdotP0 = Vector2DDotProduct(lineSeg.m_normal, lineSeg.m_pt0);
			float NdotBs = Vector2DDotProduct(lineSeg.m_normal, circle.bounds.centre);

			interTime = (NdotP0 - NdotBs + circle.m_radius) / NdotV;

			//If (0 <= Ti <= 1)
			if (interTime >= 0 && interTime <= 1)
			{
				//Bi = Bs + V * Ti
				interPt = circle.bounds.centre + velocity * interTime;

				//Normal of reflection = N
				normalAtCollision = lineSeg.m_normal;

				//Collision
				return 1;
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

	return 0; // no intersection
}

bool CheckMovingCircleToLineEdge(bool withinBothLines,
	const CircleCollider2D& circle,
	const Vector2D& ptEnd,
	const LineSegment& lineSeg,
	Vector2D& interPt,
	Vector2D& normalAtCollision,
	float& interTime)
{

	//V = Be - Bs
	Vector2D velocity = ptEnd - circle.bounds.centre;

	//Vhat or V Normallized
	Vector2D velocityNormalized;
	Vector2DNormalize(velocityNormalized, velocity);


	if (withinBothLines)
	{
		//BsP0 = P0 - Bs
		Vector2D BsP0 = lineSeg.point0 - circle.bounds.centre;

		//BsP0 = P1 - P0
		Vector2D P0P1 = lineSeg.point1 - lineSeg.point0;
		//P0 side
		if (Vector2DDotProduct(BsP0, P0P1) > 0) //P0 side
		{
			//If BsP0.Vhat
			float BsP0dotVhat = Vector2DDotProduct(BsP0, velocityNormalized);

			//If BsP0.Vhat < 0
			if (BsP0dotVhat < 0)
			{
				return 0;
			}


			//m > 0
			if (BsP0dotVhat > 0)
			{
				Vector2D velocityOutwardNormal{ velocity.y, -velocity.x };

				//M = Normalized outward normal of V 
				Vector2D velocityOutwardNormalNormalized;
				Vector2DNormalize(velocityOutwardNormalNormalized, velocityOutwardNormal);

				//float dist0 = BsP0.M
				float shortestDist = Vector2DDotProduct(BsP0, velocityOutwardNormalNormalized);

				//abs(dist0) > R
				if (abs(shortestDist) > circle.radius)
				{
					//No collision
					return 0;
				}

				//s = sqrt(R*R - dist0*dist0)
				float perpendicularDist = sqrtf(circle.radius * circle.radius - shortestDist * shortestDist);

				//V.Length();	
				float lengthOfVelocity = Vector2DLength(velocity);

				if (lengthOfVelocity == 0)
				{
					return 0;
				}
				//float ti = (m – s) / V.Length();
				interTime = (BsP0dotVhat - perpendicularDist) / lengthOfVelocity;

				//If ti <= 1
				if (interTime <= 1)
				{
					//Bi = Bs + V * ti
					interPt = circle.bounds.centre + velocity * interTime;

					//P0Bi = Bi - P0
					Vector2D P0Bi = interPt - lineSeg.m_pt0;

					//Normal of reflection is P0Bi normalized
					Vector2DNormalize(normalAtCollision, P0Bi);



					return 1;


				}

			}

		}
		else
		{
			//m = BsP1.VhatCSD1130::Vec2 velocityNormalized;
			Vector2DNormalize(velocityNormalized, velocity);

			//BsP0 = P0 - Bs
			Vector2D BsP1 = lineSeg.point1 - circle.bounds.centre;

			//BsP1.V hat
			float BsP1dotVhat = Vector2DDotProduct(BsP1, velocityNormalized);

			//BsP1.V hat
			if (BsP1dotVhat < 0) /* No collision */
			{
				return 0;
			}
			//m > 0
			if (BsP1dotVhat > 0)
			{
				//Normalized outward normal of V 
				Vector2D velocityOutwardNormalNormalized{ velocityNormalized.y, -velocityNormalized.x };

				//float dist0 = BsP1.M
				float shortestDist = Vector2DDotProduct(BsP1, velocityOutwardNormalNormalized);

				//abs(dist1) > R
				if (abs(shortestDist) > circle.radius)
				{
					//No collision
					return 0;
				}

				//s = sqrt(R*R - dist0*dist0)
				float perpendicularDist = sqrtf(circle.radius * circle.radius - shortestDist * shortestDist);

				//V.Length();
				float lengthOfVelocity = Vector2DLength(velocity);
				if (lengthOfVelocity == 0)
				{
					return 0;
				}
				//float ti = (m – s) / V.Length();
				interTime = (BsP1dotVhat - perpendicularDist) / lengthOfVelocity;

				//If ti <= 1
				if (interTime <= 1)
				{
					//Bi = Bs + V * ti
					interPt = circle.bounds.centre + velocity * interTime;

					//P1Bi = Bi - P1
					Vector2D P1Bi = interPt - lineSeg.point1;

					//Normal of reflection is P1Bi normalized
					Vector2DNormalize(normalAtCollision, P1Bi);

					return 1;
				}
			}
		}
	}
	else
	{



		bool P0Side = false;
		//BsP1 = P0 - Bs
		Vector2D BsP0 = lineSeg.point0 - circle.bounds;
		//BsP1 = P1 - Bs
		Vector2D BsP1 = lineSeg.point1 - circle.bounds.centre;

		//M is normalized outward normal of  V
		Vector2D velocityOutwardNormalNormalized{ velocityNormalized.y, -velocityNormalized.x };

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
			return 0;
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
				return 0;
			}
			else
			{
				//s = sqrt(R*R - dist0*dist0)
				float perpendicularDist = sqrtf(circle.radius * circle.radius - shortestDistP0Side * shortestDistP0Side);

				//V.Length();
				float lengthOfVelocity = Vector2DLength(velocity);

				if (lengthOfVelocity == 0)
				{
					return 0;
				}

				//float ti = (m – s) / V.Length();
				interTime = (BsP0dotVhat - perpendicularDist) / lengthOfVelocity;

				//If ti <= 1
				if (interTime <= 1)
				{
					//Bi = Bs + V * ti
					interPt = circle.bounds.centre + velocity * interTime;

					//P1Bi = Bi - P1
					Vector2D P0Bi = interPt - lineSeg.point0;

					//Normal of reflection is P1Bi normalized
					Vector2DNormalize(normalAtCollision, P0Bi);

					return 1;
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
				return 0;
			}
			else
			{
				//s = sqrt(R*R - dist0*dist0)
				float perpendicularDist = sqrtf(circle.radius * circle.radius - shortestDistP1Side * shortestDistP1Side);

				//V.Length();
				float lengthOfVelocity = Vector2DLength(velocity);

				if (lengthOfVelocity == 0)
				{
					return 0;
				}
				//float ti = (m – s) / V.Length();
				interTime = (BsP1dotVhat - perpendicularDist) / lengthOfVelocity;

				//If ti <= 1
				if (interTime <= 1)
				{
					//Bi = Bs + V * ti
					interPt = circle.bounds.centre + velocity * interTime;

					//P1Bi = Bi - P1
					Vector2D P1Bi = interPt - lineSeg.point1;

					//Normal of reflection is P1Bi normalized
					Vector2DNormalize(normalAtCollision, P1Bi);

					return 1;
				}
			}
		}
	}
	return 0;
}

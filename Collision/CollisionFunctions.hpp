
#include "Bounds.hpp"
#include "Vector2D.hpp"
#include "CircleCollider2D.hpp"
#include "LineSegment.hpp"
#include "Ray.hpp"

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


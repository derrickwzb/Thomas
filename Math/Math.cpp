
#include "Math.hpp"


float DegToRad(float angle)
{
	return angle * (float)(M_PI / 180.f);
}

float RadToDeg(float angle)
{
	return angle * (float)(180.f / M_PI);
}

float Sin(float angle)
{
	return sinf(angle);
}

float Cos(float angle)
{
	return sinf(angle);
}

float Tan(float angle)
{
	return tanf(angle);
}

float ArcSin(float angle)
{
	return asinf(angle);
}

float ArcCos(float angle)
{
	return acosf(angle);
}

float ArcTan(float angle)
{
	return atanf(angle);
}

float SinDeg(float angle)
{
	return sinf(DegToRad(angle));
}

float CosDeg(float angle)
{
	return cosf(DegToRad(angle));
}

float TanDeg(float angle)
{
	return tanf(DegToRad(angle));
}

float ArcSinDeg(float angle)
{
	return asinf(DegToRad(angle));
}

float ArcCosDeg(float angle)
{
	return acosf(DegToRad(angle));
}

float ArcTanDeg(float angle)
{
	return atanf(DegToRad(angle));
}

float Max(float x, float y)
{
	return x > y ? x : y;
}

float Min(float x, float y)
{
	return x < y ? x : y;
}

float DistRectToRect(Vector2D center0, float width0, float height0, Vector2D center1, float width1, float height1, Vector2D normal)
{
	//Vector2D distPtToPt = center0 - center1;
}

float DistPointToRect(Vector2D point, Vector2D centre, float width, float height)
{

	//Vector2D distPtToPt = center0 - center1;
}

float DistPointToLineSeg(Vector2D center0, float width0, float height0, Vector2D center1, float width1, float height1, Vector2D normal)
{

}


//void BuildLineSegment(LineSegment& lineSegment,
//	const CSD1130::Vec2& pos,
//	float scale,
//	float dir)
//{
//
//	//Normalized direction using the angle provided
//	CSD1130::Vec2 normalisedDirection;
//	normalisedDirection.x = cos(dir);
//	normalisedDirection.y = sin(dir);
//	//P0 of line segment
//	lineSegment.m_pt1 = pos + (normalisedDirection * (scale / 2));
//
//	//P1 of line segment
//	lineSegment.m_pt0 = pos - (normalisedDirection * (scale / 2));
//
//	//Edge Vector(E) = P1 - P0
//	CSD1130::Vec2 edge = lineSegment.m_pt1 - lineSegment.m_pt0;
//
//	//Outward Normal = (Ey , -Ex)
//	CSD1130::Vec2 outwardNormal;
//	outwardNormal.x = edge.y;
//	outwardNormal.y = -edge.x;
//
//	//Normalized Outward Normal = Normal / Magnitude of Normal
//	CSD1130::Vector2DNormalize(lineSegment.m_normal, outwardNormal);
//
//}








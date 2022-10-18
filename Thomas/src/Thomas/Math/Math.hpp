#define _USE_MATH_DEFINES
#include <limits>
#include <math.h>
#include <cmath>
#include "Vector2D.h"
#include "Matrix3x3.h"

namespace Thomas
{
	float DegToRad(float deg);

	float RadToDeg(float rad);

	float Sin_Rad(float angle);

	float Cos_Rad(float angle);

	float Tan_Rad(float angle);

	float ArcSin_Rad(float angle);

	float ArcCos_Rad(float angle);

	float ArcTan_Rad(float angle);

	float Sin_Deg(float angle);

	float Cos_Deg(float angle);

	float Tan_Deg(float angle);

	float ArcSin_Deg(float angle);

	float ArcCos_Deg(float angle);

	float ArcTan_Deg(float angle);

	float Square(float x);

	float SquareRoot(float x);

	float Max(float x, float y);

	float Min(float x, float y);

	float Natural_Log(float x);

	float LogBase10(float x);

	float Pow(float x, float y);

	bool InRange(float x, float min_range, float max_range);

	float Clamp(float x, float min_range, float max_range);

	float Wraparound(float x, float min_range, float max_range);

	float CalcDistPointToCircle(Vector2D* point_pos, Vector2D* center_circle, float radius);

	float DistPointToRect(Vector2D* point_pos, Vector2D* center_rect, float width, float height);

	float DistPointToLineSeg(Vector2D* point_pos, Vector2D* line_start, Vector2D* line_end);

	float CalcDistCircleToCircle(Vector2D* circleA_center, float cirleA_rad, Vector2D* circleB_center, float circleB_rad);

	bool TestPointToCircle(Vector2D* point_pos, Vector2D* circle_center, float radius);

	bool TestPointToRect(Vector2D* point_pos, Vector2D* center_rect, float width, float height);

	float CalcDistRectToRectCenter(Vector2D* center_rectA, Vector2D* center_rectB);

}



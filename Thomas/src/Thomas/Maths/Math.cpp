#include "thpch.h"
#include "Math.hpp"
#include <math.h>
#include <cmath>

namespace Thomas
{
	float DegToRad(float angle)
	{
		return angle * (float)(M_PI / 180.f);
	}

	float RadToDeg(float angle)
	{
		return angle * (float)(180.f / M_PI);
	}

	float Sin_Rad(float angle)
	{
		return sinf(angle);
	}

	float Cos_Rad(float angle)
	{
		return cosf(angle);
	}

	float Tan_Rad(float angle)
	{
		return tanf(angle);
	}

	float ArcSin_Rad(float angle)
	{
		return asinf(angle);
	}

	float ArcCos_Rad(float angle)
	{
		return acosf(angle);
	}

	float ArcTan_Rad(float angle)
	{
		return atanf(angle);
	}

	float Sin_Deg(float angle)
	{
		return sinf(DegToRad(angle));
	}

	float Cos_Deg(float angle)
	{
		return cosf(DegToRad(angle));
	}

	float Tan_Deg(float angle)
	{
		return tanf(DegToRad(angle));
	}

	float ArcSin_Deg(float angle)
	{
		return asinf(DegToRad(angle));
	}

	float ArcCos_Deg(float angle)
	{
		return acosf(DegToRad(angle));
	}

	float ArcTan_Deg(float angle)
	{
		return atanf(DegToRad(angle));
	}

	float Square(float x)
	{
		return x * x;
	}

	float SquareRoot(float x)
	{
		return sqrt(x);
	}

	float Max(float x, float y)
	{
		return x > y ? x : y;
	}

	float Min(float x, float y)
	{
		return x < y ? x : y;
	}

	float Natural_Log(float x)
	{
		return log(x);
	}

	float LogBase10(float x)
	{
		return log10(x);
	}

	float Pow(float x, float y)
	{
		return pow(x, y);
	}

	bool InRange(float x, float min_range, float max_range) {

		if ((x > min_range) && (x < max_range)) {
			return true;
		}

		else {
			return false;
		}

	}

	float Clamp(float x, float min_range, float max_range) {

		if (x < min_range) {
			return min_range;
		}

		else if (x > max_range) {
			return max_range;
		}

		else {
			return x;
		}

	}

	float Wraparound(float x, float min_range, float max_range) {

		float range = max_range - min_range;

		// If x is lesser than x0, return (x + range).
		if (x < min_range) {
			return x + range;
		}

		// If x is higher than x1, return (x - range).
		if (x > max_range) {
			return x - range;
		}

		//Wraparound does not work if x is lesser than (x0 - range)
		// or if x is greater than (x1 + range).
		if (x < (min_range - range)) {
			std::cout << "Warning! Invalid output!" << std::endl;
		}

		if (x > (max_range + range)) {
			std::cout << "Warning! Invalid output!" << std::endl;
		}

	}

	//Returns the shortest distance from the point to the edge of the circle. 
	//This value will be negative if the point is inside the circle.
	float CalcDistPointToCircle(Vector2D point_pos, Vector2D center_circle, float radius) {

		float shortest_distance = shortest_distance = SquareRoot(pow((center_circle.x - point_pos.x), 2) + pow((center_circle.y - point_pos.y), 2)) - radius;
		return shortest_distance;

	}

	float DistPointToRect(Vector2D point_pos, Vector2D center_rect, float width, float height)
	{
		float shortest_distance = 0.0f;
		float Max_x = center_rect.x + 0.5*(width);
		float Max_y = center_rect.y + 0.5*(height);
		float Min_x = center_rect.x - 0.5*(width);
		float Min_y = center_rect.y - 0.5*(height);

		if (point_pos.x < Min_x) {

			if (point_pos.y < Min_y) {
				return shortest_distance = SquareRoot(Square(Min_x - point_pos.x) + Square(Min_y - point_pos.y));
			}

			else if (point_pos.y > Max_y) {
				return shortest_distance = SquareRoot(Square(Min_x - point_pos.x) + Square(Max_y - point_pos.y));
			}

			else if ((point_pos.y >= Min_y) && (point_pos.y <= Max_y)) {
				return shortest_distance = Min_x - point_pos.x;
			}

		}

		else {

			if ((point_pos.x > Min_x) && (point_pos.x < Max_x)) {

				if (point_pos.y < Min_y) {
					return shortest_distance = Min_y = point_pos.y;
				}

				else if (point_pos.y > Max_y) {
					return shortest_distance = point_pos.y - Max_y;
				}

				else {

					if (point_pos.x > Min_x) {

						if (point_pos.y < Min_y) {
							return shortest_distance = SquareRoot(Square(Max_x - point_pos.x) + Square(Min_y - point_pos.y));
						}

						else if (point_pos.y > Max_y) {
							return shortest_distance = SquareRoot(Square(Max_x - point_pos.x) + Square(Max_y - point_pos.y));
						}

						else if ((point_pos.y >= Min_y) && (point_pos.y <= Max_y)) {
							return shortest_distance = point_pos.x - Max_x;
						}

					}

				}
			}

		}

	}

	float DistPointToLineSeg(Vector2D point_pos, Vector2D line_start, Vector2D line_end)
	{
		float line_distance = SquareRoot(Square(line_end.x - line_start.x) + Square(line_end.y - line_start.y));
		Vector2D point_vec = point_pos - line_start;
		Vector2D line_vec = line_end - line_start;
		float projection = Vector2DDotProduct(point_vec, line_vec);
		float shortest_distance = SquareRoot(Square(point_pos.x) + Square(point_pos.y) - Square(projection));
		return shortest_distance;
	}

	float CalcDistCircleToCircle(Vector2D circleA_center, float cirleA_rad, Vector2D circleB_center, float circleB_rad)
	{
		float shortest_distance = 0;
		float Vec_cAcB = SquareRoot(Square(circleB_center.x - circleA_center.x) + Square(circleB_center.y - circleA_center.y));
		return shortest_distance = Vec_cAcB - cirleA_rad - circleB_rad;

	}

	bool TestPointToCircle(Vector2D point_pos, Vector2D circle_center, float radius)
	{
		float distance = SquareRoot(Square(circle_center.x - point_pos.x) + Square(circle_center.y - point_pos.y));

		if (distance > radius) {
			return false;
		}

		else if (distance <= radius) {
			return true;
		}

	}

	bool TestPointToRect(Vector2D point_pos, Vector2D center_rect, float width, float height) {

		float distance = SquareRoot(Square(center_rect.x - point_pos.x) + Square(center_rect.y - point_pos.y));

		if (DistPointToRect(point_pos, center_rect, width, height) <= distance) {
			return true;
		}

		else {
			return false;
		}

	}

	float CalcDistRectToRectCenter(Vector2D center_rectA, Vector2D center_rectB) {

		float distance = SquareRoot(Square(center_rectB.x - center_rectA.x) + Square(center_rectB.y - center_rectB.y));
		return distance;

	}

}










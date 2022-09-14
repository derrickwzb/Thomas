/******************************************************************************/
/*!
\file		Vector2D.cpp
\author 	Keith Lua, weijiekeith.lua, 2101223
\par    	email: weijiekeith.lua\@digipen.edu
\date   	April, 1, 2022
\brief		This file represents the implementation of a Vector2D struct that 
			are specified in interface (header) file Vector2D.h. The functions 
			handles the manipulation of Vector2D structs.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "Vector2D.h"
#include <math.h>
//
//namespace CSD1130
//{
	/**************************************************************************/
	/*!
		This is a parameterized constructor that creates a vector object and 
		assigns its data members with the parameter values.
	 */
	/**************************************************************************/
	Vector2D::Vector2D(float _x, float _y) :x{ 0 }, y{ 0 }
	{
		x = _x;
		y = _y;
	}

	// Assignment operators

	/**************************************************************************/
	/*!
		This operator overload adds the lhs vector with the rhs vector
		and then assigns result to lhs vector and then returns the reference
		to the lhs vector.
	 */
	/**************************************************************************/
	Vector2D& Vector2D::operator += (const Vector2D& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	/**************************************************************************/
	/*!
		This operator overload subtracts the lhs vector with the rhs vector 
		and then assigns result to lhs vector and then returns the reference 
		to the lhs vector.
	 */
	/**************************************************************************/
	Vector2D& Vector2D::operator -= (const Vector2D& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	/**************************************************************************/
	/*!
		This operator overload multiplies the lhs vector with the rhs scalar 
		value and then assigns result to lhs vector and then returns the 
		reference to the lhs vector.
	 */
	/**************************************************************************/
	Vector2D& Vector2D::operator *= (float rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	/**************************************************************************/
	/*!
		This operator overload divides the lhs vector with the rhs scalar value
		and then returns the reference to the lhs vector.
	 */
	/**************************************************************************/
	Vector2D& Vector2D::operator /= (float rhs)
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}

	// Unary operators

	/**************************************************************************/
	/*!
		This operator overload negates/multiplies by -1 any vector
		and then returns the result as a vector.
	 */
	/**************************************************************************/
	Vector2D Vector2D::operator -() const
	{
		Vector2D vector;
		float xValue = x * -1;
		float yValue = y * -1;
		vector.x = xValue;
		vector.y = yValue;
		return vector;
	}

	// Binary operators
	/**************************************************************************/
	/*!
		This operator overload adds the lhs vector with rhs vector
		and then returns the result as a vector.
	 */
	/**************************************************************************/
	Vector2D operator + (const Vector2D& lhs, const Vector2D& rhs)
	{
		Vector2D result;
		result.x = lhs.x + rhs.x;
		result.y = lhs.y + rhs.y;
		return result;
	}

	/**************************************************************************/
	/*!
		This operator overload subtracts the lhs vector with rhs vector
		and then returns the result as a vector.
	 */
	/**************************************************************************/
	Vector2D operator - (const Vector2D& lhs, const Vector2D& rhs)
	{
		Vector2D result;
		result.x = lhs.x - rhs.x;
		result.y = lhs.y - rhs.y;
		return result;
	}

	/**************************************************************************/
	/*!
		This operator overload multiplies the lhs vector with rhs scalar value
		and then returns the result as a vector.
	 */
	/**************************************************************************/
	Vector2D operator * (const Vector2D& lhs, float rhs)
	{
		Vector2D result;
		result.x = lhs.x * rhs;
		result.y = lhs.y * rhs;
		return result;
	}

	/**************************************************************************/
	/*!
		This operator overload multiplies the lhs scalar value with rhs vector
		and then returns the result as a vector.
	 */
	/**************************************************************************/
	Vector2D operator * (float lhs, const Vector2D& rhs)
	{
		Vector2D result;
		result.x = lhs * rhs.x;
		result.y = lhs * rhs.y;
		return result;
	}

	/**************************************************************************/
	/*!
		This operator overload divides the lhs vector with rhs scalar value
		and then returns the result as a vector.
	 */
	/**************************************************************************/
	Vector2D operator / (const Vector2D& lhs, float rhs)
	{

		Vector2D result;
		result.x = lhs.x / rhs;
		result.y = lhs.y / rhs;
		return result;
	}

	/**************************************************************************/
	/*!
		
		This function assign the pResult vector with the normalized/the unit
		vector of pVec0 vector.
		
	 */
	/**************************************************************************/
	void	Vector2DNormalize(Vector2D& pResult, const Vector2D& pVec0)
	{
		pResult = pVec0 / Vector2DLength(pVec0);
	}

	/**************************************************************************/
	/*!
		This function returns the actual length of vector pVec0.
	 */
	/**************************************************************************/
	float	Vector2DLength(const Vector2D& pVec0)
	{
		return sqrtf(((pVec0.x * pVec0.x) + (pVec0.y * pVec0.y)));
	}

	/**************************************************************************/
	/*!
		This function returns the squared length of vector pVec0.
	 */
	/**************************************************************************/
	float	Vector2DSquareLength(const Vector2D& pVec0)
	{
		return (pVec0.x * pVec0.x) + (pVec0.y * pVec0.y);
	}

	/**************************************************************************/
	/*!
		This function returns the actual distance between two 2D points
		represented by vectors pVec0 and pVec1.
	 */
	/**************************************************************************/
	float	Vector2DDistance(const Vector2D& pVec0, const Vector2D& pVec1)
	{
		Vector2D distance = pVec0 - pVec1;

		return Vector2DLength(distance);
	}

	/**************************************************************************/
	/*!
		This function returns the squared distance between two 2D points 
		represented by vectors pVec0 and pVec1.

	 */
	/**************************************************************************/
	float	Vector2DSquareDistance(const Vector2D& pVec0, const Vector2D& pVec1)
	{
		Vector2D distance = pVec0 - pVec1;
		return Vector2DSquareLength(distance);
	}

	/**************************************************************************/
	/*!
		This function returns the dot product of the vectors pVec0 and pVec1
	 */
	/**************************************************************************/
	float	Vector2DDotProduct(const Vector2D& pVec0, const Vector2D& pVec1)
	{
		return pVec0.x * pVec1.x + pVec0.y * pVec1.y;
	}

	/**************************************************************************/
	/*!
		This function returns the cross product magnitude
		of the vectors pVec0 and pVec1.
	 */
	/**************************************************************************/
	float	Vector2DCrossProductMag(const Vector2D& pVec0, const Vector2D& pVec1)
	{
		return  pVec0.x * pVec1.y - pVec1.x * pVec0.y;
	}

//}
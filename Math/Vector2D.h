/******************************************************************************/
/*!
\file		Vector2D.h
\author 	Keith Lua, weijiekeith.lua, 2101223
\par    	email: weijiekeith.lua\@digipen.edu
\date   	April, 1, 2022
\brief		This file represents the interface of the source file
			Vector2D.cpp, it contains the function prototype declarations 
			and struct definitions. The functions in the respective .cpp file
			manages and is responsible for the manipulation of the Vector2D 
			struct.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/

#ifndef VECTOR2D_H_
#define VECTOR2D_H_



	/**************************************************************************/
	/*!
		This struct is an implementation of a 2D Vector consist of functions 
		that manages and manipulates the Vector2D struct object. 
		Its data members x and y represents the component of the vector and the
		m[2] is its matrix equivalent.
	*/
	/**************************************************************************/
	typedef union Vector2D
	{
		struct
		{
			float x, y;
		};

		float m[2];

		// Constructors
		/**************************************************************************/
		/*!
			This is the default constructor of the Vector2D struct.
		*/
		/**************************************************************************/
		Vector2D(): x{ 0 }, y{ 0 }
		{};

		/**************************************************************************/
		/*!
			This is a parameterized constructor that creates a vector object and
			assigns its data members with the parameter values.
		*/
		/**************************************************************************/
		Vector2D(float _x, float _y);

		// Assignment operators
		/**************************************************************************/
		/*!
			This operator overload adds the lhs vector with the rhs vector
			and then assigns result to lhs vector and then returns the reference
			to the lhs vector.
		*/
		/**************************************************************************/
		Vector2D& operator += (const Vector2D &rhs);

		/**************************************************************************/
		/*!
			This operator overload subtracts the lhs vector with the rhs vector
			and then assigns result to lhs vector and then returns the reference
			to the lhs vector.
		*/
		/**************************************************************************/
		Vector2D& operator -= (const Vector2D &rhs);

		/**************************************************************************/
		/*!
			This operator overload multiplies the lhs vector with the rhs scalar
			value and then assigns result to lhs vector and then returns the
			reference to the lhs vector.
		*/
		/**************************************************************************/
		Vector2D& operator *= (float rhs);

		/**************************************************************************/
		/*!
			This operator overload divides the lhs vector with the rhs scalar value
			and then returns the reference to the lhs vector.
		*/
		/**************************************************************************/
		Vector2D& operator /= (float rhs);

		// Unary operators
		/**************************************************************************/
		/*!
			This operator overload negates/multiplies by -1 any vector
			and then returns the result as a vector.
		*/
		/**************************************************************************/
		Vector2D operator -() const;

	} Vector2D, Vec2, Point2D, Pt2;


	// Binary operators
	/**************************************************************************/
	/*!
		This operator overload adds the lhs vector with rhs vector
		and then returns the result as a vector.
	*/
	/**************************************************************************/
	Vector2D operator + (const Vector2D &lhs, const Vector2D &rhs);

	/**************************************************************************/
	/*!
		This operator overload subtracts the lhs vector with rhs vector
		and then returns the result as a vector.
	*/
	/**************************************************************************/
	Vector2D operator - (const Vector2D &lhs, const Vector2D &rhs);

	/**************************************************************************/
	/*!
		This operator overload multiplies the lhs vector with rhs scalar value
		and then returns the result as a vector.
	 */
	 /**************************************************************************/
	Vector2D operator * (const Vector2D &lhs, float rhs);

	/**************************************************************************/
	/*!
		This operator overload multiplies the lhs scalar value with rhs vector
		and then returns the result as a vector.
	 */
	 /**************************************************************************/
	Vector2D operator * (float lhs, const Vector2D &rhs);

	/**************************************************************************/
	/*!
		This operator overload divides the lhs vector with rhs scalar value
		and then returns the result as a vector.
	 */
	 /**************************************************************************/
	Vector2D operator / (const Vector2D &lhs, float rhs);

	/**************************************************************************/
	/*!
		In this function, pResult will be the unit vector of pVec0
	 */
	/**************************************************************************/
	void	Vector2DNormalize(Vector2D &pResult, const Vector2D &pVec0);
	
	/**************************************************************************/
	/*!
		This function returns the length of the vector pVec0 
	 */
	/**************************************************************************/
	float	Vector2DLength(const Vector2D &pVec0);
	
	/**************************************************************************/
	/*!
		This function returns the square of pVec0's length. Avoid the square root 
	 */
	/**************************************************************************/
	float	Vector2DSquareLength(const Vector2D &pVec0);
	
	/**************************************************************************/
	/*!
		In this function, pVec0 and pVec1 are considered as 2D points.
		The distance between these 2 2D points is returned
	 */
	/**************************************************************************/
	float	Vector2DDistance(const Vector2D &pVec0, const Vector2D &pVec1);
	
	/**************************************************************************/
	/*!
		In this function, pVec0 and pVec1 are considered as 2D points.
		The squared distance between these 2 2D points is returned. 
		Avoid the square root
	 */
	/**************************************************************************/
	float	Vector2DSquareDistance(const Vector2D &pVec0, const Vector2D &pVec1);
	
	/**************************************************************************/
	/*!
		This function returns the dot product between pVec0 and pVec1
	 */
	/**************************************************************************/
	float	Vector2DDotProduct(const Vector2D &pVec0, const Vector2D &pVec1);
	
	/**************************************************************************/
	/*!
		This function returns the cross product magnitude 
		between pVec0 and pVec1
	 */
	/**************************************************************************/
	float	Vector2DCrossProductMag(const Vector2D &pVec0, const Vector2D &pVec1);
}

#endif // CSD1130_VECTOR2D_H_
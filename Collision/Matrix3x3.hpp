/******************************************************************************/
/*!
\file		Matrix3x3.h
\author 	Keith Lua, weijiekeith.lua, 2101223
\par    	email: weijiekeith.lua\@digipen.edu
\date   	April, 1, 2022
\brief		This file represents the interface of the source file
			Matrix3x3.cpp, it contains the function prototype declarations 
			and struct definitions. The functions in the respective .cpp file
			handles the manipulation of Matrix3x3 structs.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/

#ifndef MATRIX3X3_H_
#define MATRIX3X3_H_

#include "Vector2D.hpp"
//namespace MyMatrix
//{

	#ifdef _MSC_VER
	// Supress warning: nonstandard extension used : nameless struct/union
	#pragma warning( disable : 4201 )
	#endif

/**************************************************************************/
/*!
	This struct is an implementation of a 3 by 3 Matrix and consist of
	functions that manages and manipulates the Vector2D struct object.
	Its data members represents the rows and columns of the matrix.
 */
 /**************************************************************************/
	typedef union Matrix3x3
	{
		struct
		{
			float m00, m01, m02;
			float m10, m11, m12;
			float m20, m21, m22;
		};

		float m[9];
		float m2[3][3];

		/**************************************************************************/
		/*!
			This is the default constructor of the Matrix3x3 struct.
		*/
		/**************************************************************************/
		Matrix3x3() :m00{ 0 }, m01{ 0 }, m02{ 0 }, m10{ 0 }, m11{ 0 }, m12{ 0 }, m20{ 0 }, m21{ 0 }, m22{ 0 }
		{}


		/**************************************************************************/
		/*!
			This is a conversion constructor that creates a matrix object and
			assigns its data members with the parameter values which
			in this case is a pointer to an array of float values.
		*/
		/**************************************************************************/
		Matrix3x3(const float* pArr);

		/**************************************************************************/
		/*!
			This is a parameterized constructor that creates a matrix object and
			assigns its data members with the parameter values.
		*/
		/**************************************************************************/
		Matrix3x3(float _00, float _01, float _02,
			float _10, float _11, float _12,
			float _20, float _21, float _22);

		/**************************************************************************/
		/*!
			This operator overload assigns and copies values from the rhs matrix
			to the lhs matrix and then returns the reference to the lhs matrix.
		*/
		/**************************************************************************/
		Matrix3x3& operator=(const Matrix3x3& rhs);

		// Assignment operators
		/**************************************************************************/
		/*!
			This operator overload multiplies the lhs matrix with rhs matrix
			and then assigns the result to the lhs matrix then returns the
			reference to it.
		*/
		/**************************************************************************/
		Matrix3x3& operator *= (const Matrix3x3& rhs);

	} Matrix3x3, Mtx33;

	#ifdef _MSC_VER
	// Supress warning: nonstandard extension used : nameless struct/union
	#pragma warning( default : 4201 )
	#endif

/**************************************************************************/
/*!
	This operator overload multiplies a matrix another matrix
	and returns another matrix as the result.
 */
 /**************************************************************************/
	Matrix3x3 operator * (const Matrix3x3& lhs, const Matrix3x3& rhs);

	/**************************************************************************/
	/*!
		This operator multiplies the matrix pMtx with the vector rhs
		and returns the result as a vector
	 */
	 /**************************************************************************/
	Vector2D  operator * (const Matrix3x3& pMtx, const MyVector::Vector2D& rhs);

	/**************************************************************************/
	/*!
		This function sets the matrix pResult to the identity matrix
	 */
	 /**************************************************************************/
	void Mtx33Identity(Matrix3x3& pResult);

	/**************************************************************************/
	/*!
		This function creates a translation matrix from x & y
		and saves it in pResult
	 */
	 /**************************************************************************/
	void Mtx33Translate(Matrix3x3& pResult, float x, float y);

	/**************************************************************************/
	/*!
		This function creates a scaling matrix from x & y
		and saves it in pResult
	 */
	 /**************************************************************************/
	void Mtx33Scale(Matrix3x3& pResult, float x, float y);

	/**************************************************************************/
	/*!
		This matrix creates a rotation matrix from "angle" whose value
		is in radian. Save the resultant matrix in pResult.
	 */
	 /**************************************************************************/
	void Mtx33RotRad(Matrix3x3& pResult, float angle);

	/**************************************************************************/
	/*!
		This matrix creates a rotation matrix from "angle" whose value
		is in degree. Save the resultant matrix in pResult.
	 */
	 /**************************************************************************/
	void Mtx33RotDeg(Matrix3x3& pResult, float angle);

	/**************************************************************************/
	/*!
		This functions calculated the transpose matrix of pMtx
		and saves it in pResult
	 */
	 /**************************************************************************/
	void Mtx33Transpose(Matrix3x3& pResult, const Matrix3x3& pMtx);

	/**************************************************************************/
	/*!
		This function calculates the inverse matrix of pMtx and saves the
		result in pResult. If the matrix inversion fails, pResult
		would be set to NULL.
	*/
	/**************************************************************************/
	void Mtx33Inverse(Matrix3x3* pResult, float* determinant, const Matrix3x3& pMtx);
//}

#endif 
/******************************************************************************/
/*!
\file		Matrix3x3.cpp
\author 	Keith Lua, weijiekeith.lua, 2101223
\par    	email: weijiekeith.lua\@digipen.edu
\date   	April, 1, 2022
\brief		This file is an implementation of a Matrix 3x3 class that
			are specified in interface (header) file Matrix3x3.h. The functions 
			handles the manipulation of Matrix3x3 structs.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#define _USE_MATH_DEFINES
#include <limits>
#include "Matrix3x3.hpp"
#include <math.h>

//namespace MyMatrix
//{



	/**************************************************************************/
	/*!
		This is a conversion constructor that creates a matrix object and
		assigns its data members with the parameter values which
		in this case is a pointer to an array of float values.
	 */
	 /**************************************************************************/
	Matrix3x3::Matrix3x3(const float* pArr) : m00{ 0 }, m01{ 0 }, m02{ 0 }, m10{ 0 }, m11{ 0 }, m12{ 0 }, m20{ 0 }, m21{ 0 }, m22{ 0 }
	{
		m00 = pArr[0]; m01 = pArr[1]; m02 = pArr[2];
		m10 = pArr[3]; m11 = pArr[4]; m12 = pArr[5];
		m20 = pArr[6]; m21 = pArr[7]; m22 = pArr[8];
	}

	/**************************************************************************/
	/*!
		This is a parameterized constructor that creates a matrix object and
		assigns its data members with the parameter values.
	 */
	 /**************************************************************************/
	Matrix3x3::Matrix3x3(float _00, float _01, float _02,
		float _10, float _11, float _12,
		float _20, float _21, float _22) : m00{ 0 }, m01{ 0 }, m02{ 0 }, m10{ 0 }, m11{ 0 }, m12{ 0 }, m20{ 0 }, m21{ 0 }, m22{ 0 }
	{
		m00 = _00; m01 = _01; m02 = _02;
		m10 = _10; m11 = _11; m12 = _12;
		m20 = _20; m21 = _21; m22 = _22;
	}


	/**************************************************************************/
	/*!
		This operator overload assigns and copies values from the rhs matrix
		to the lhs matrix and then returns the reference to the lhs matrix.
	 */
	 /**************************************************************************/
	Matrix3x3& Matrix3x3::operator = (const Matrix3x3& rhs)
	{

		m00 = rhs.m00; m01 = rhs.m01; m02 = rhs.m02;
		m10 = rhs.m10; m11 = rhs.m11; m12 = rhs.m12;
		m20 = rhs.m20; m21 = rhs.m21; m22 = rhs.m22;

		return *this;

	}

	/**************************************************************************/
	/*!
		This operator overload multiplies the lhs matrix with rhs matrix
		and then assigns the result to the lhs matrix then returns the
		reference to it.
	 */
	 /**************************************************************************/
	Matrix3x3& Matrix3x3::operator *= (const Matrix3x3& rhs)
	{
		Matrix3x3 result;
		result.m00 = m00 * rhs.m00 + m01 * rhs.m10 + m02 * rhs.m20;
		result.m01 = m00 * rhs.m01 + m01 * rhs.m11 + m02 * rhs.m21;
		result.m02 = m00 * rhs.m02 + m01 * rhs.m12 + m02 * rhs.m22;

		//Second Row oF Resultant Matrix  10 11 10
		result.m10 = m10 * rhs.m00 + m11 * rhs.m10 + m12 * rhs.m20;
		result.m11 = m10 * rhs.m01 + m11 * rhs.m11 + m12 * rhs.m21;
		result.m12 = m10 * rhs.m02 + m11 * rhs.m12 + m12 * rhs.m22;

		//Third Row oF Resultant Matrix   20 21 22
		result.m20 = m20 * rhs.m00 + m21 * rhs.m10 + m22 * rhs.m20;
		result.m21 = m20 * rhs.m01 + m21 * rhs.m11 + m22 * rhs.m21;
		result.m22 = m20 * rhs.m02 + m21 * rhs.m12 + m22 * rhs.m22;

		m00 = result.m00; m01 = result.m01; m02 = result.m02;
		m10 = result.m10; m11 = result.m11; m12 = result.m12;
		m20 = result.m20; m21 = result.m21; m22 = result.m22;
		return *this;
	}

	/**************************************************************************/
	/*!
		This operator overload multiplies a matrix another matrix
		and returns another matrix as the result.
	 */
	 /**************************************************************************/
	Matrix3x3 operator * (const Matrix3x3& lhs, const Matrix3x3& rhs)
	{
		Matrix3x3 result;

		result.m00 = (lhs.m00 * rhs.m00 + lhs.m01 * rhs.m10 + lhs.m02 * rhs.m20);
		result.m01 = (lhs.m00 * rhs.m01 + lhs.m01 * rhs.m11 + lhs.m02 * rhs.m21);
		result.m02 = (lhs.m00 * rhs.m02 + lhs.m01 * rhs.m12 + lhs.m02 * rhs.m22);

		//Second Row oF Resultant Matrix  10 11 10
		result.m10 = (lhs.m10 * rhs.m00 + lhs.m11 * rhs.m10 + lhs.m12 * rhs.m20);
		result.m11 = (lhs.m10 * rhs.m01 + lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21);
		result.m12 = (lhs.m10 * rhs.m02 + lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22);

		//Third Row oF Resultant Matrix   20 21 22
		result.m20 = (lhs.m20 * rhs.m00 + lhs.m21 * rhs.m10 + lhs.m22 * rhs.m20);
		result.m21 = (lhs.m20 * rhs.m01 + lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21);
		result.m22 = (lhs.m20 * rhs.m02 + lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22);

		return result;
	}

	/**************************************************************************/
	/*!
		This operator overload multiplies a matrix with a vector
		and returns another vector as the result.
	 */
	 /**************************************************************************/
	Vector2D  operator * (const Matrix3x3& pMtx, const MyVector::Vector2D& rhs)
	{
		MyVector::Vector2D result;

		result.x = pMtx.m00 * rhs.x + pMtx.m01 * rhs.y + pMtx.m02 * 1.f;
		result.y = pMtx.m10 * rhs.x + pMtx.m11 * rhs.y + pMtx.m12 * 1.f;
		return result;

	}

	/**************************************************************************/
	/*!
		This function creates an identity matrix and assigns it to pResult
		matrix.
	 */
	 /**************************************************************************/
	void Mtx33Identity(Matrix3x3& pResult)
	{
		pResult.m00 = 1.f; pResult.m01 = 0.f; pResult.m02 = 0.f;
		pResult.m10 = 0.f; pResult.m11 = 1.f; pResult.m12 = 0.f;
		pResult.m20 = 0.f; pResult.m21 = 0.f; pResult.m22 = 1.f;

	}

	/**************************************************************************/
	/*!
		This function creates a translation matrix from x & y
		and assigns it to the pResult matrix.
	 */
	 /**************************************************************************/
	void Mtx33Translate(Matrix3x3& pResult, float x, float y)
	{
		pResult.m00 = 1.f; pResult.m01 = 0.f; pResult.m02 = x;
		pResult.m10 = 0.f; pResult.m11 = 1.f; pResult.m12 = y;
		pResult.m20 = 0.f; pResult.m21 = 0.f; pResult.m22 = 1.f;
	}

	/**************************************************************************/
	/*!
		This function creates a scaling matrix from x & y
		and assigns it to pResult matrix.
	 */
	 /**************************************************************************/
	void Mtx33Scale(Matrix3x3& pResult, float x, float y)
	{
		pResult.m00 = x; pResult.m01 = 0.f; pResult.m02 = 0.f;
		pResult.m10 = 0.f; pResult.m11 = y;  pResult.m12 = 0.f;
		pResult.m20 = 0.f; pResult.m21 = 0.f; pResult.m22 = 1.f;
	}

	/**************************************************************************/
	/*!
		This function creates a rotation matrix from angle in radian
		and assigns it to pResult matrix.
	 */
	 /**************************************************************************/
	void Mtx33RotRad(Matrix3x3& pResult, float angle)
	{
		pResult.m00 = cosf(angle); pResult.m01 = -(sinf(angle)); pResult.m02 = 0.f;
		pResult.m10 = sinf(angle); pResult.m11 = cosf(angle); pResult.m12 = 0.f;
		pResult.m20 = 0.f; pResult.m21 = 0.f; pResult.m22 = 1.f;
	}

	/**************************************************************************/
	/*!
		This function creates a rotation matrix from angle in degree
		and assigns it to pResult matrix.
	 */
	 /**************************************************************************/
	void Mtx33RotDeg(Matrix3x3& pResult, float angle)
	{
		float angleInRad = angle * (float)(M_PI / 180.f);
		pResult.m00 = cosf(angleInRad); pResult.m01 = -(sinf(angleInRad)); pResult.m02 = 0.f;
		pResult.m10 = sinf(angleInRad); pResult.m11 = cosf(angleInRad);    pResult.m12 = 0.f;
		pResult.m20 = 0.f;	pResult.m21 = 0.f;                 pResult.m22 = 1.f;

	}

	/**************************************************************************/
	/*!
		This functions calculates the transpose matrix of pMtx matrix
		and assigns it to pResult matrix.
	 */
	 /**************************************************************************/
	void Mtx33Transpose(Matrix3x3& pResult, const Matrix3x3& pMtx)
	{
		Matrix3x3 transpose;
		transpose.m00 = pMtx.m00; transpose.m01 = pMtx.m10; transpose.m02 = pMtx.m20;
		transpose.m10 = pMtx.m01; transpose.m11 = pMtx.m11; transpose.m12 = pMtx.m21;
		transpose.m20 = pMtx.m02; transpose.m21 = pMtx.m12; transpose.m22 = pMtx.m22;

		pResult = transpose;
	}

	/**************************************************************************/
	/*!
		This function calculates the inverse matrix of pMtx matrix and assigns
		the result to the pResult matrix.
	*/
	/**************************************************************************/
	void Mtx33Inverse(Matrix3x3* pResult, float* determinant, const Matrix3x3& pMtx)
	{
		//m00, m01, m02;
		//m10, m11, m12;
		//m20, m21, m22;


		Matrix3x3 cofactor;
		Matrix3x3 adjugate;
		Matrix3x3 inverse;

		//Matrix of minors by getting the determinants of the sub matrices
		float firstRowDet1 = pMtx.m11 * pMtx.m22 - pMtx.m12 * pMtx.m21; //11 * 22 - 12 * 21
		float firstRowDet2 = pMtx.m10 * pMtx.m22 - pMtx.m12 * pMtx.m20; //10 * 22 - 12 * 20
		float firstRowDet3 = pMtx.m10 * pMtx.m21 - pMtx.m11 * pMtx.m20; //10 * 21 - 11 * 20

		*determinant = pMtx.m00 * firstRowDet1 - pMtx.m01 * firstRowDet2 + pMtx.m02 * firstRowDet3;

		float secondRowDet1 = pMtx.m01 * pMtx.m22 - pMtx.m02 * pMtx.m21; //01 * 22 - 02 * 21
		float secondRowDet2 = pMtx.m00 * pMtx.m22 - pMtx.m02 * pMtx.m20; //00 * 22 - 02 * 20
		float secondRowDet3 = pMtx.m00 * pMtx.m21 - pMtx.m01 * pMtx.m20; //00 * 21 - 01 * 20

		float thirdRowDet1 = pMtx.m01 * pMtx.m12 - pMtx.m02 * pMtx.m11; //01 * 12 - 02 * 11
		float thirdRowDet2 = pMtx.m00 * pMtx.m12 - pMtx.m02 * pMtx.m10; //00 * 12 - 02 * 10
		float thirdRowDet3 = pMtx.m00 * pMtx.m11 - pMtx.m01 * pMtx.m10; //00 * 11 - 01 * 10


		//Negate the matrix in this patern to get the cofactor
		//+ - +
		//- + -
		//+ - +
		cofactor.m00 = firstRowDet1; cofactor.m01 = -(firstRowDet2); cofactor.m02 = firstRowDet3;
		cofactor.m10 = -(secondRowDet1); cofactor.m11 = secondRowDet2; cofactor.m12 = -(secondRowDet3);
		cofactor.m20 = thirdRowDet1; cofactor.m21 = -(thirdRowDet2); cofactor.m22 = thirdRowDet3;

		//Transpose the cofactor to get the adjugate
		Mtx33Transpose(adjugate, cofactor);

		//Multiplying the adjugate with the determinant to get the inverse matrix
		//Check if the determinant is not 0
		if (*determinant != 0.f || *determinant != std::numeric_limits<float>::epsilon())
		{
			inverse.m00 = adjugate.m00 * (1 / *determinant); inverse.m01 = adjugate.m01 * (1 / *determinant); inverse.m02 = adjugate.m02 * (1 / *determinant);
			inverse.m10 = adjugate.m10 * (1 / *determinant); inverse.m11 = adjugate.m11 * (1 / *determinant); inverse.m12 = adjugate.m12 * (1 / *determinant);
			inverse.m20 = adjugate.m20 * (1 / *determinant); inverse.m21 = adjugate.m21 * (1 / *determinant); inverse.m22 = adjugate.m22 * (1 / *determinant);
		}

		*pResult = inverse;
	}
//}


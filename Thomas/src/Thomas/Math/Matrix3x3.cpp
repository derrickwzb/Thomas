#include <cmath>
#include "thpch.h"
#include "Matrix3x3.h"

#define M_PI       3.14159265358979323846f   // define pi

namespace Thomas {

	Matrix3x3::Matrix3x3(const float* pArr) : m00{ *pArr } ,       m01{ *(pArr + 1) } , m02{ *(pArr + 2) } , 
											  m10{ *(pArr + 3) } , m11{ *(pArr + 4) } , m12{ *(pArr + 5) } ,
											  m20{ *(pArr + 6) } , m21{ *(pArr + 7) } , m22{ *(pArr + 8) } {}

	Matrix3x3::Matrix3x3(float _00, float _01, float _02,
		float _10, float _11, float _12,
		float _20, float _21, float _22) : m00{ _00 }, m01{ _01 }, m02{ _02 },
										   m10{ _10 }, m11{ _11 }, m12{ _12 },
										   m20{ _20 }, m21{ _21 }, m22{ _22 } {}

	Matrix3x3& Matrix3x3::operator=(const Matrix3x3& rhs) {

		m00 = rhs.m00; m01 = rhs.m01; m02 = rhs.m02;
		m10 = rhs.m10; m11 = rhs.m11; m12 = rhs.m12;
		m20 = rhs.m20; m21 = rhs.m21; m22 = rhs.m22;
		return *this;
	}

	Matrix3x3& Matrix3x3::operator *= (const Matrix3x3& rhs) {
		
		Matrix3x3 tmpMatrix;

		tmpMatrix.m00 = (m00 * rhs.m00) + (m01 * rhs.m10) + (m02 * rhs.m20);
		tmpMatrix.m01 = (m00 * rhs.m01) + (m01 * rhs.m11) + (m02 * rhs.m21);
		tmpMatrix.m02 = (m00 * rhs.m02) + (m01 * rhs.m12) + (m02 * rhs.m22);

		tmpMatrix.m10 = (m10 * rhs.m00) + (m11 * rhs.m10) + (m12 * rhs.m20);
		tmpMatrix.m11 = (m10 * rhs.m01) + (m11 * rhs.m11) + (m12 * rhs.m21);
		tmpMatrix.m12 = (m10 * rhs.m02) + (m11 * rhs.m12) + (m12 * rhs.m22);

		tmpMatrix.m20 = (m20 * rhs.m00) + (m21 * rhs.m10) + (m22 * rhs.m20);
		tmpMatrix.m21 = (m20 * rhs.m01) + (m21 * rhs.m11) + (m22 * rhs.m21);
		tmpMatrix.m22 = (m20 * rhs.m02) + (m21 * rhs.m12) + (m22 * rhs.m22);

		m00 = tmpMatrix.m00;
		m01 = tmpMatrix.m01;
		m02 = tmpMatrix.m02;

		m10 = tmpMatrix.m10;
		m11 = tmpMatrix.m11;
		m12 = tmpMatrix.m12;

		m20 = tmpMatrix.m20;
		m21 = tmpMatrix.m21;
		m22 = tmpMatrix.m22;

		return *this;

	}

	Matrix3x3 operator * (const Matrix3x3& lhs, const Matrix3x3& rhs) {
		
		Matrix3x3 newMatrix;

		newMatrix.m00 = (lhs.m00 * rhs.m00) + (lhs.m01 * rhs.m10) + (lhs.m02 * rhs.m20);
		newMatrix.m01 = (lhs.m00 * rhs.m01) + (lhs.m01 * rhs.m11) + (lhs.m02 * rhs.m21);
		newMatrix.m02 = (lhs.m00 * rhs.m02) + (lhs.m01 * rhs.m12) + (lhs.m02 * rhs.m22);

		newMatrix.m10 = (lhs.m10 * rhs.m00) + (lhs.m11 * rhs.m10) + (lhs.m12 * rhs.m20);
		newMatrix.m11 = (lhs.m10 * rhs.m01) + (lhs.m11 * rhs.m11) + (lhs.m12 * rhs.m21);
		newMatrix.m12 = (lhs.m10 * rhs.m02) + (lhs.m11 * rhs.m12) + (lhs.m12 * rhs.m22);

		newMatrix.m20 = (lhs.m20 * rhs.m00) + (lhs.m21 * rhs.m10) + (lhs.m22 * rhs.m20);
		newMatrix.m21 = (lhs.m20 * rhs.m01) + (lhs.m21 * rhs.m11) + (lhs.m22 * rhs.m21);
		newMatrix.m22 = (lhs.m20 * rhs.m02) + (lhs.m21 * rhs.m12) + (lhs.m22 * rhs.m22);

		return newMatrix;

	}
	
	Vector2D  operator * (const Matrix3x3& pMtx, const Vector2D& rhs) {

		Vector2D newMatrix;
		newMatrix.x = (pMtx.m00 * rhs.x) + (pMtx.m01 * rhs.y) + pMtx.m02;
		newMatrix.y = (pMtx.m10 * rhs.x) + (pMtx.m11 * rhs.y) + pMtx.m12;
		return newMatrix;

	}

	void Mtx33Identity(Matrix3x3& pResult) {

		pResult.m00 = 1; pResult.m01 = 0; pResult.m02 = 0;
		pResult.m10 = 0; pResult.m11 = 1; pResult.m12 = 0;
		pResult.m20 = 0; pResult.m21 = 0; pResult.m22 = 1;

	}

	void Mtx33Translate(Matrix3x3& pResult, float x, float y) {

		pResult.m00 = 1; pResult.m01 = 0; pResult.m02 = x;
		pResult.m10 = 0; pResult.m11 = 1; pResult.m12 = y;
		pResult.m20 = 0; pResult.m21 = 0; pResult.m22 = 1;

	}

	void Mtx33Scale(Matrix3x3& pResult, float x, float y) {

		pResult.m00 = x; pResult.m01 = 0; pResult.m02 = 0;
		pResult.m10 = 0; pResult.m11 = y; pResult.m12 = 0;
		pResult.m20 = 0; pResult.m21 = 0; pResult.m22 = 1;

	}

	void Mtx33RotRad(Matrix3x3& pResult, float angle) {

		pResult.m00 = cos(angle); pResult.m01 = -sin(angle); pResult.m02 = 0;
		pResult.m10 = sin(angle); pResult.m11 =  cos(angle); pResult.m12 = 0;
		pResult.m20 = 0;          pResult.m21 = 0;           pResult.m22 = 1;

	}

	void Mtx33RotDeg(Matrix3x3& pResult, float angle) {

		float degAngle = (angle * M_PI) / 180.f;
		pResult.m00 = cos(degAngle); pResult.m01 = -sin(degAngle); pResult.m02 = 0;
		pResult.m10 = sin(degAngle); pResult.m11 = cos(degAngle);  pResult.m12 = 0;
		pResult.m20 = 0;             pResult.m21 = 0;              pResult.m22 = 1;

	}

	void Mtx33Transpose(Matrix3x3& pResult, const Matrix3x3& pMtx) {

		pResult.m00 = pMtx.m00; pResult.m01 = pMtx.m10; pResult.m02 = pMtx.m20;
		pResult.m10 = pMtx.m01; pResult.m11 = pMtx.m11; pResult.m12 = pMtx.m21;
		pResult.m20 = pMtx.m02; pResult.m21 = pMtx.m12; pResult.m22 = pMtx.m22;

	}

	void Mtx33Inverse(Matrix3x3* pResult, float* determinant, const Matrix3x3& pMtx) {

		Matrix3x3 tmp;

		*determinant = pMtx.m00 * ((pMtx.m11 * pMtx.m22) - (pMtx.m12 * pMtx.m21))
					 - pMtx.m01 * ((pMtx.m10 * pMtx.m22) - (pMtx.m20 * pMtx.m12))
					 + pMtx.m02 * ((pMtx.m10 * pMtx.m21) - (pMtx.m11 * pMtx.m20));
		
		if (*determinant == 0) {

			pResult = nullptr;
			return;

		}

		tmp.m00 =    (pMtx.m11 * pMtx.m22) - (pMtx.m12 * pMtx.m21); 
		tmp.m01 = -( (pMtx.m10 * pMtx.m22) - (pMtx.m12 * pMtx.m20) );
		tmp.m02 =    (pMtx.m10 * pMtx.m21) - (pMtx.m11 * pMtx.m20);
			
		tmp.m10 = -( (pMtx.m01 * pMtx.m22) - (pMtx.m02 * pMtx.m21) );
		tmp.m11 =    (pMtx.m00 * pMtx.m22) - (pMtx.m02 * pMtx.m20);
		tmp.m12 = -( (pMtx.m00 * pMtx.m21) - (pMtx.m01 * pMtx.m20) );
			
		tmp.m20 =    (pMtx.m01 * pMtx.m12) - (pMtx.m02 * pMtx.m11);
		tmp.m21 = -( (pMtx.m00 * pMtx.m12) - (pMtx.m02 * pMtx.m10) );
		tmp.m22 =    (pMtx.m00 * pMtx.m11) - (pMtx.m01 * pMtx.m10);

		pResult->m00 = tmp.m00 / *determinant;
		pResult->m01 = tmp.m10 / *determinant;
		pResult->m02 = tmp.m20 / *determinant;

		pResult->m10 = tmp.m01 / *determinant;
		pResult->m11 = tmp.m11 / *determinant;
		pResult->m12 = tmp.m21 / *determinant;

		pResult->m20 = tmp.m02 / *determinant;
		pResult->m21 = tmp.m12 / *determinant;
		pResult->m22 = tmp.m22 / *determinant;
	
	}

	void Mtx33Concat(Matrix3x3 &pResult, Matrix3x3 &pMtx1, Matrix3x3 &pMtx2) {

		pResult = pMtx1 * pMtx2;

	}

}
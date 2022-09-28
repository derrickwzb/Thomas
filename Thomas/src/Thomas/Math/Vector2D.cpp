/******************************************************************************/
/*!
\file		Vector2D.cpp
\author 	Brandon Zhuo Jian Yi
\par    	email: zhuo.j@digipen.edu
\date   	March 21, 2022
\brief

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <cmath>
#include "thpch.h"
#include "Vector2D.h"

namespace Thomas {

	Vector2D::Vector2D(float _x, float _y) : x{ _x }, y{ _y } {}
	
	Vector2D& Vector2D::operator += (const Vector2D& rhs) {

		x = x + rhs.x;
		y = y + rhs.y;
		return *this;

	}

	Vector2D& Vector2D::operator -= (const Vector2D& rhs) {

		x = x - rhs.x;
		y = y - rhs.y;
		return *this;

	}

	Vector2D& Vector2D::operator *= (float rhs) {

		x = x * rhs;
		y = y * rhs;
		return *this;

	}

	Vector2D& Vector2D::operator /= (float rhs) {

		x = x / rhs;
		y = y / rhs;
		return *this;

	}

	Vector2D Vector2D::operator -() const {

		Vector2D newVector;
		newVector.x = -x;
		newVector.y = -y;
		return newVector;
		
	}

	Vector2D operator + (const Vector2D& lhs, const Vector2D& rhs) {

		return {lhs.x + rhs.x , lhs.y + rhs.y};

	}

	Vector2D operator - (const Vector2D& lhs, const Vector2D& rhs) {

		return { lhs.x - rhs.x , lhs.y - rhs.y };
	}

	Vector2D operator * (const Vector2D& lhs, float rhs) {

		return { lhs.x * rhs , lhs.y * rhs };

	}

	Vector2D operator * (float lhs, const Vector2D& rhs) {

		return { rhs.x * lhs , rhs.y * lhs };

	}

	Vector2D operator / (const Vector2D& lhs, float rhs) {

		return { lhs.x / rhs ,  lhs.y / rhs };

	}

	void Vector2DNormalize(Vector2D& pResult, const Vector2D& pVec0) {

		float magnitudeSquare = (pVec0.x * pVec0.x) + (pVec0.y * pVec0.y);
		float magnitude = sqrtf(magnitudeSquare);
		pResult.x = pVec0.x / magnitude;
		pResult.y = pVec0.y / magnitude;

	}

	float Vector2DLength(const Vector2D& pVec0) {

		float magnitudeSquare = (pVec0.x * pVec0.x) + (pVec0.y * pVec0.y);
		float magnitude = sqrtf(magnitudeSquare);
		return magnitude;

	}

	float Vector2DSquareLength(const Vector2D& pVec0) {

		float magnitudesquare = (pVec0.x * pVec0.x) + (pVec0.y * pVec0.y);
		return magnitudesquare;

	}

	float Vector2DDistance(const Vector2D& pVec0, const Vector2D& pVec1) {

		float xDistance = pVec1.x - pVec0.x;
		float yDistance = pVec1.y - pVec0.y;
		float distanceSquare = (xDistance * xDistance) + (yDistance * yDistance);
		float distance = sqrtf(distanceSquare);
		return distance;

	}

	float Vector2DSquareDistance(const Vector2D& pVec0, const Vector2D& pVec1) {

		float xDistance = pVec1.x - pVec0.x;
		float yDistance = pVec1.y - pVec0.y;
		float distanceSquare = (xDistance * xDistance) + (yDistance * yDistance);
		return distanceSquare;

	}

	float Vector2DDotProduct(const Vector2D& pVec0, const Vector2D& pVec1) {

		float dotProduct = (pVec0.x * pVec1.x) + (pVec0.y * pVec1.y);
		return dotProduct;

	}

	float Vector2DCrossProductMag(const Vector2D& pVec0, const Vector2D& pVec1) {

		float crossProduct = (pVec0.x * pVec1.y) - (pVec0.y * pVec1.x);
		return crossProduct;

	}

	void Vector2DSet(Vector2D &pResult, float x, float y) {
		
		pResult.x = x;
		pResult.y = y;

	}

	void Vector2DAdd(Vector2D &pResult, Vector2D &pVec1, Vector2D &pVec2) {
		
		pResult.x = pVec1.x + pVec2.x;
		pResult.y = pVec1.y + pVec2.y;

	}

	void Vector2DScale(Vector2D &pResult, Vector2D &pVec1, float scale) {

		pResult.x = pVec1.x * scale;
		pResult.y = pVec1.y * scale;

	}

	void Vector2DFromAngle(Vector2D& pResult, float angle) {

		pResult.x = cosf(angle);
		pResult.y = sinf(angle);

	}

	void Vector2DSub(Vector2D& pResult, Vector2D& pVec1, Vector2D& pVec2) {

		pResult.x = pVec1.x - pVec2.x;
		pResult.y = pVec1.y - pVec2.y;

	}

	void Vector2DZero(Vector2D& pResult) {

		pResult.x = 0;
		pResult.y = 0;

	}

}
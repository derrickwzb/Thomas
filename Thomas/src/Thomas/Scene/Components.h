#pragma once

#include "Thomas/Math/Math.h"

namespace Thomas {

	struct Point
	{
		
	//public:
		//Point();
		float positionx;
		float positiony;
		//void Serialize(std::string& str);
	};

	//Point::Point() {
	//	positionx = 0;
	//	positiony = 0;
	//}

	//void Point::Serialize(std::string& str) {

	//}

	struct Colour {
		float r;
		float g;
		float b;
		float a;
	};

	struct Triangle {
		float positionx;
		float positiony;
		float positionz;
	};

	struct Rigidbody2DComponent
	{
		//enum class BodyType { Static = 0, Dynamic, Kinematic };
		//BodyType Type = BodyType::Static;
		//bool FixedRotation = false;

		// object current position
		Vector2D posCurr = {0.f, 0.f};
		// object current velocity
		Vector2D velCurr = { 0.f, 0.f };
		// object current direction
		float dirCurr = { 0.f };

		// Storage for runtime
		void* RuntimeBody = nullptr;

		Rigidbody2DComponent() = default;
		Rigidbody2DComponent(const Rigidbody2DComponent&) = default;
	};
}

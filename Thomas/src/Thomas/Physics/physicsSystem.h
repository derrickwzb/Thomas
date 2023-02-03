#pragma once
#include "Thomas/Math/Matrix3x3.h"
#include "Thomas/Math/Vector2D.h"
#include "RigidBody.hpp"
#include "Thomas/Scene/Scene.h"

namespace Thomas {
	using EntityID = uint32_t;

	class Physics {

		public:
			void Update(Scene* m_Context, Timestep timestep);
			void addForce(RigidBody &x, float force, Timestep timestep);
			inline void ZeroForce() { m_Force = Vector2D(0, 0); }

			//Friction
			inline void ApplyFriction(Vector2D friction) { m_Friction = friction; }
			inline void ZeroFriction() { m_Friction = Vector2D(0, 0); }

			inline static double Physic_timetaken = 0;

		private:
			Vector2D m_Force;
			Vector2D m_Friction;
	};

	static Physics physicsSystem;
}
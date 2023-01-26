#pragma once
#include "Thomas/Math/Matrix3x3.h"
#include "Thomas/Math/Vector2D.h"
#include "RigidBody.hpp"
#include "Thomas/Scene/Scene.h"
//#include "Thomas/Scene/Entity.h"
//#include "Thomas/Collision/Collision.h"

namespace Thomas {
	using EntityID = uint32_t;

	class Physics {

		public:
			//void Init();
			void Update(Scene* m_Context, Timestep timestep);

			void addForce(RigidBody &x, float force, Timestep timestep);
			inline void ZeroForce() { m_Force = Vector2D(0, 0); }

			//Friction
			inline void ApplyFriction(Vector2D friction) { m_Friction = friction; }
			inline void ZeroFriction() { m_Friction = Vector2D(0, 0); }

            //void temp(float &x, float force);

			inline static double Physic_timetaken = 0;

			void ClickButton(Scene* m_Context);

		private:
			//Vector2D m_Velocity;
			//Vector2D m_Acceleration;
			Vector2D m_Force;
			Vector2D m_Friction;

			

	};


	static Physics physicsSystem;
}
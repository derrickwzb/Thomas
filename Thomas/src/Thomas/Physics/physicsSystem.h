#pragma once
#include "Thomas/Math/Matrix3x3.h"
#include "Thomas/Math/Vector2D.h"
#include "RigidBody.hpp"
#include "Thomas/Scene/Entity.h"
//#include "Thomas/Collision/Collision.h"

namespace Thomas {
	using Entity = unsigned int;
	void Print_physics(std::vector<Entity> allentity);

	class Physics {

		public:
			//void Init();
			void Update(std::vector<Entity> allentity, Timestep timestep);
			void Input(Entity entity, Timestep timestep);

			void addForce(RigidBody &x, float force, Timestep timestep);
			inline void ZeroForce() { m_Force = Vector2D(0, 0); }

			//Friction
			inline void ApplyFriction(Vector2D friction) { m_Friction = friction; }
			inline void ZeroFriction() { m_Friction = Vector2D(0, 0); }

            //void temp(float &x, float force);

			inline static double Physic_timetaken = 0;

		private:
			//Vector2D m_Velocity;
			//Vector2D m_Acceleration;
			Vector2D m_Force;
			Vector2D m_Friction;

	};


	static Physics physicsSystem;

}
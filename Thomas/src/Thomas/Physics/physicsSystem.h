#pragma once
#include "Thomas/Math/Matrix3x3.h"
#include "Thomas/Math/Vector2D.h"
#include "RigidBody.hpp"
#include "Thomas/Scene/Entity.h"
#include "Thomas/Collision/Collision.hpp"

namespace Thomas {
	
	void Print_physics(std::vector<Entity> allentity);

	class Physics {

		public:
			//void Init();
			void Update(std::vector<Entity> allentity);

			void addForce(RigidBody &x, int force);
			inline void ZeroForce() { m_Force = Vector2D(0, 0); }

			//Friction
			inline void ApplyFriction(Vector2D friction) { m_Friction = friction; }
			inline void ZeroFriction() { m_Friction = Vector2D(0, 0); }

		private:
			//Vector2D m_Velocity;
			//Vector2D m_Acceleration;
			Vector2D m_Force;
			Vector2D m_Friction;

	};


	static Physics physicsSystem;

    //void Print_physics(std::vector<Entity> allentity) {

    //    for (auto const& entity : allentity) {

    //        if (factory.HasComponent<RigidBody>(entity))
    //        {
    //            auto print = factory.GetComponent<RigidBody>(entity);
    //            std::cout << "entity " << entity << ": " << print.m_Position.x << "," << print.m_Position.y << std::endl;

    //        }

    //        if (factory.HasComponent<BoxCollider2D>(entity))
    //        {
    //            auto print = factory.GetComponent<BoxCollider2D>(entity);
    //            std::cout << "entity " << entity << ": " << print.bounds.min.x << "," << print.bounds.min.y
    //                << "," << print.bounds.max.x << "," << print.bounds.max.y << std::endl;

    //        }
    //    }

    //    std::cout << std::endl;
    //}


    //void Physics::addForce(RigidBody& x, int force) {

    //    x.m_Position.x += force;
    //    x.m_Position.y += force;

    //}

    //void Physics::Update(std::vector<Entity> allentity) {

    //    for (auto const& entity : allentity) {

    //        if (factory.HasComponent<RigidBody>(entity)) {

    //            auto getRigid = factory.GetComponent<RigidBody>(entity);

    //            //Adding force
    //            physicsSystem.addForce(getRigid, 10);//force should be user input harcoded atm
    //            factory.ChangeComponent<Thomas::RigidBody>(entity, getRigid);//Updates data for component

    //        }

    //        //Static rect to rect collision
    //        if (factory.HasComponent<BoxCollider2D>(entity)) {

    //            auto getbox = factory.GetComponent<BoxCollider2D>(entity);
    //            auto getRigid1 = factory.GetComponent<RigidBody>(entity);

    //            for (auto const& entity2 : allentity) {

    //                if (entity != entity2) {

    //                    if (factory.HasComponent<BoxCollider2D>(entity2)) {

    //                        auto getbox2 = factory.GetComponent<BoxCollider2D>(entity2);
    //                        auto getRigid2 = factory.GetComponent<RigidBody>(entity2);

    //                        //Velocity here is a placeholder
    //                        if (Thomas::CollisionIntersection_RectRect(getbox.bounds, getRigid1.Velocity, getbox2.bounds, getRigid2.Velocity) == true) {
    //                            std::cout << entity << ", " << entity2 << ": colliding" << std::endl;
    //                        }

    //                        else {
    //                            std::cout << entity << ", " << entity2 << ": not colliding" << std::endl;
    //                        }
    //                    }
    //                }
    //            }
    //        }
    //    }
    //    std::cout << std::endl;
    //}

}
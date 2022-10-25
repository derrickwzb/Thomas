 #include "thpch.h"
#include <iostream>
#include "physicsSystem.h"
#include "Platform/Windows/WindowsInput.h"
#include "Thomas/Core/KeyCodes.h"

int g_dt = 5;
//float acceleration = 0.02;

namespace Thomas {

    //std::vector<Entity> entities;

    void Print_physics(std::vector<Entity> allentity) {

        for (auto const& entity : allentity) {

            if (factory.HasComponent<RigidBody>(entity))
            {
                auto print = factory.GetComponent<RigidBody>(entity);
                std::cout << "entity " << entity << ": " << print.m_Position.x << "," << print.m_Position.y << std::endl;

            }

            if (factory.HasComponent<BoxCollider2D>(entity))
            {
                auto print = factory.GetComponent<BoxCollider2D>(entity);
                std::cout << "entity " << entity << ": " << print.bounds.min.x << "," << print.bounds.min.y
                    << "," << print.bounds.max.x << "," << print.bounds.max.y << std::endl;

            }
        }

        std::cout << std::endl;
    }


    void Physics::addForce(RigidBody& x, float force, Timestep timestep) {
        x.Velocity += ( (1 / x.GetMass()) * force) * timestep;
    }


    void Physics::Update(std::vector<Entity> allentity, Timestep timestep) {
       
        for (auto const& entity : allentity) {
            /*
            if (factory.HasComponent<RigidBody>(entity)) {

                auto getRigid = factory.GetComponent<RigidBody>(entity);

                //Adding force

                physicsSystem.addForce(getRigid, 10);//force should be user input harcoded atm
                factory.ChangeComponent<Thomas::RigidBody>(entity, getRigid);//Updates data for component

            }
            */

            //Static rect to rect collision
            if (factory.HasComponent<BoxCollider2D>(entity)) {

                auto getbox = factory.GetComponent<BoxCollider2D>(entity);
                auto getRigid1 = factory.GetComponent<RigidBody>(entity);

                for (auto const& entity2 : allentity) {

                    if (entity != entity2) {

                        if (factory.HasComponent<BoxCollider2D>(entity2)) {

                            auto getbox2 = factory.GetComponent<BoxCollider2D>(entity2);
                            auto getRigid2 = factory.GetComponent<RigidBody>(entity2);

                            //Velocity here is a placeholder
                            /*if (Thomas::CollisionIntersection_RectRect(getbox.bounds, getRigid1.Velocity, getbox2.bounds, getRigid2.Velocity) == true) {
                                std::cout << entity << ", " << entity2 << ": colliding" << std::endl;
                            }

                            else {
                                std::cout << entity << ", " << entity2 << ": not colliding" << std::endl;
                            }*/
                        }
                    }
                }
            }
        }
        std::cout << std::endl;
    }

    void Physics::Input(Entity entity, Timestep timestep) {

        auto getRigid = factory.GetComponent<RigidBody>(Graphics::sel); //next time we will use player entity id instead of graphics::sel
        auto transform = factory.GetComponent<Transform>(Graphics::sel); //next time we will use player entity id instead of graphics::sel

        if (Input::IsKeyPressed(TH_KEY_W)) {

            getRigid.m_Position.y = transform.translation.y;

            physicsSystem.addForce(getRigid, 10, timestep);
            //std::cout << getRigid.Velocity << std::endl;
            //getRigid.m_Position.x = transform.translation.x;

            //getRigid.m_Position.x += getRigid.Velocity * ts;
            getRigid.m_Position.y += -getRigid.Velocity * timestep;

            //transform.translation.x = getRigid.m_Position.x;
            transform.translation.y = getRigid.m_Position.y;

        }

        if (Input::IsKeyPressed(TH_KEY_A)) {
            getRigid.m_Position.x = transform.translation.x;
            physicsSystem.addForce(getRigid, 10, timestep);
            getRigid.m_Position.x += -getRigid.Velocity * timestep;
            transform.translation.x = getRigid.m_Position.x;

            //physicsSystem.temp(transform.translation.x, -rigidbody.Velocity);
            //std::cout << "move a\n";
        }
        
        if (Input::IsKeyPressed(TH_KEY_S)) {
            getRigid.m_Position.y = transform.translation.y;
            physicsSystem.addForce(getRigid, 10, timestep);
            getRigid.m_Position.y += getRigid.Velocity * timestep;
            transform.translation.y = getRigid.m_Position.y;
            
            //physicsSystem.temp(transform.translation.y, rigidbody.Velocity);
            //std::cout << "move s\n";
        }
        
        if (Input::IsKeyPressed(TH_KEY_D)) {
            getRigid.m_Position.x = transform.translation.x;
            physicsSystem.addForce(getRigid, 10, timestep);
            getRigid.m_Position.x += getRigid.Velocity * timestep;
            transform.translation.x = getRigid.m_Position.x;
            // physicsSystem.temp(transform.translation.x, rigidbody.Velocity);
            //std::cout << "move d\n";
        }
        

        getRigid.Velocity = 0.0f;
        factory.ChangeComponent<Thomas::RigidBody>(Graphics::sel, getRigid);//Updates data for component
        factory.ChangeComponent<Thomas::Transform>(Graphics::sel, transform);//Updates data for component
    }
}
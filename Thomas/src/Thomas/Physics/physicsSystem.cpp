#include "thpch.h"
#include <iostream>
#include "physicsSystem.h"

int g_dt = 5;

namespace Thomas {

    std::vector<Entity> entities;
    void Print_physics(std::vector<Entity> allentity);

    //void Physics::Init() {

    //    //factory.Init();

    //    //Registers the name of the component into the system
    //    factory.RegisterComponent<RigidBody>();
    //    factory.RegisterComponent<BoxCollider2D>();

    //    //Signature of current component
    //    Signature signature;
    //    signature.set(factory.GetComponentType<RigidBody>());
    //    signature.set(factory.GetComponentType<BoxCollider2D>());

    //    Entity object = factory.CreateEmptyComposition();
    //    Entity object2 = factory.CreateEmptyComposition();
    //    Entity object3 = factory.CreateEmptyComposition();

    //    Thomas::RigidBody newrigid;
    //    newrigid.SetPositionX(1.f);
    //    newrigid.SetPositionY(1.f);
    //    newrigid.Velocity.x = 10.f;
    //    newrigid.Velocity.y = 10.f;

    //    Thomas::RigidBody newrigid2;
    //    newrigid2.SetPositionX(1.f);
    //    newrigid2.SetPositionY(1.f);
    //    newrigid2.Velocity.x = 10.f;
    //    newrigid2.Velocity.y = 10.f;

    //    Thomas::BoxCollider2D newCollidor1;
    //    newCollidor1.bounds.min.x = 10.f;
    //    newCollidor1.bounds.max.x = 20.f;
    //    newCollidor1.bounds.min.y = 10.f;
    //    newCollidor1.bounds.max.y = 20.f;
    //    Thomas::Vector2D vel1{ 10, 10 };

    //    Thomas::BoxCollider2D newCollidor2;
    //    newCollidor2.bounds.min.x = 30.f;
    //    newCollidor2.bounds.max.x = 40.f;
    //    newCollidor2.bounds.min.y = 30.f;
    //    newCollidor2.bounds.max.y = 40.f;
    //    Thomas::Vector2D vel2{ 20, 20 };

    //    factory.AddComponent<Thomas::RigidBody>(object, newrigid);
    //    factory.AddComponent<Thomas::BoxCollider2D>(object2, newCollidor1);
    //    factory.AddComponent<Thomas::BoxCollider2D>(object3, newCollidor2);
    //    factory.AddComponent<Thomas::RigidBody>(object2, newrigid2);
    //    factory.AddComponent<Thomas::RigidBody>(object3, newrigid2);

    //    entities.push_back(object); //pushing back data of the object into the entity
    //    entities.push_back(object2); //pushing back data of the object into the entity
    //    entities.push_back(object3);

    //    Print_physics(entities);

    //}

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


    void Physics::addForce(RigidBody& x, int force) {

        x.m_Position.x += force;
        x.m_Position.y += force;

    }

    void Physics::Update(std::vector<Entity> allentity) {

        for (auto const& entity : allentity) {

            if (factory.HasComponent<RigidBody>(entity)) {

                auto getRigid = factory.GetComponent<RigidBody>(entity);

                //Adding force
                physicsSystem.addForce(getRigid, 10);//force should be user input harcoded atm
                factory.ChangeComponent<Thomas::RigidBody>(entity, getRigid);//Updates data for component

            }

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
                            if (Thomas::CollisionIntersection_RectRect(getbox.bounds, getRigid1.Velocity, getbox2.bounds, getRigid2.Velocity) == true) {
                                std::cout << entity << entity2 << "colliding" << std::endl;
                            }

                            else {
                                std::cout << "not colliding" << std::endl;
                            }
                        }
                    }
                }
            }
        }
    }

}
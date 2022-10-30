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
                /*std::cout << "entity " << entity << ": " << print.m_Position.x << "," << print.m_Position.y << std::endl;*/

            }

            if (factory.HasComponent<BoxCollider2D>(entity))
            {
                auto print = factory.GetComponent<BoxCollider2D>(entity);
               /* std::cout << "entity " << entity << ": " << print.bounds.min.x << "," << print.bounds.min.y
                    << "," << print.bounds.max.x << "," << print.bounds.max.y << std::endl;*/

            }
        }

        //std::cout << std::endl;
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
                auto getTransform1 = factory.GetComponent<Transform>(entity);
                auto getbounding_box = factory.GetComponent<Box_collider>(entity);

                //getbox.ArrayToVector();
                
               /* std::cout << "A ( " << getTransform1.vertice0.x << "," << getTransform1.vertice0.y << ")"  << std::endl;
                std::cout << "A ( " << getTransform1.vertice1.x << "," << getTransform1.vertice1.y << ")" << std::endl;
                std::cout << "A ( " << getTransform1.vertice2.x << "," << getTransform1.vertice2.y << ")" << std::endl;
                std::cout << "A ( " << getTransform1.vertice3.x << "," << getTransform1.vertice3.y << ")" << std::endl;*/
                getbox.verticesList[0] = Vec2{ getbounding_box.box_trans.vertice0.x , getbounding_box.box_trans.vertice0.y };
                getbox.verticesList[1] = Vec2{ getbounding_box.box_trans.vertice1.x , getbounding_box.box_trans.vertice1.y };
                getbox.verticesList[2] = Vec2{ getbounding_box.box_trans.vertice2.x , getbounding_box.box_trans.vertice2.y };
                getbox.verticesList[3] = Vec2{ getbounding_box.box_trans.vertice3.x , getbounding_box.box_trans.vertice3.y };

                /*std::cout << "A ( " << getbox.verticesList[0].x << "," << getbox.verticesList[0].y << ")" << std::endl;
                std::cout << "A ( " << getbox.verticesList[1].x << "," << getbox.verticesList[1].y << ")" << std::endl;
                std::cout << "A ( " << getbox.verticesList[2].x << "," << getbox.verticesList[2].y << ")" << std::endl;
                std::cout << "A ( " << getbox.verticesList[3].x << "," << getbox.verticesList[3].y << ")" << std::endl;*/
                //std::cout << "SIZE: " << getbox.verticesList.size() <<"\n";
                
       /*         Vec2 obj1_vertice0 = Vec2(getTransform1.min.x, getTransform1.max.y);
                Vec2 obj1_vertice1 = Vec2(getTransform1.max.x, getTransform1.max.y);
                Vec2 obj1_vertice2 = Vec2(getTransform1.max.x, getTransform1.min.y);
                Vec2 obj1_vertice3 = Vec2(getTransform1.min.x, getTransform1.min.y);*/
                //getbox.vertices.clear();
                //getbox.vertices.shrink_to_fit();
                //getbox.vertices.push_back(obj1_vertice0);
                //getbox.vertices.push_back(obj1_vertice1);
                //getbox.vertices.push_back(obj1_vertice2);
                //getbox.vertices.push_back(obj1_vertice3);
                //pInst->vertices.clear();
                //pInst->vertices.shrink_to_fit();
                ////if (pInst != nullptr)
                ////{
                //pInst->vertices.push_back(vertice0);
                //pInst->vertices.push_back(vertice1);
                //pInst->vertices.push_back(vertice2);
                //pInst->vertices.push_back(vertice3);
                
                for (auto const& entity2 : allentity) {

                    if (entity != entity2) {

                        if (factory.HasComponent<BoxCollider2D>(entity2)) {

                            auto getbox2 = factory.GetComponent<BoxCollider2D>(entity2);
                            auto getRigid2 = factory.GetComponent<RigidBody>(entity2);
                            auto getTransform2 = factory.GetComponent<Transform>(entity2);
                            auto getbounding_box2 = factory.GetComponent<Box_collider>(entity2);

    
                            getbox2.verticesList[0] = Vec2{ getbounding_box2.box_trans.vertice0.x , getbounding_box2.box_trans.vertice0.y };
                            getbox2.verticesList[1] = Vec2{ getbounding_box2.box_trans.vertice1.x , getbounding_box2.box_trans.vertice1.y };
                            getbox2.verticesList[2] = Vec2{ getbounding_box2.box_trans.vertice2.x , getbounding_box2.box_trans.vertice2.y };
                            getbox2.verticesList[3] = Vec2{ getbounding_box2.box_trans.vertice3.x , getbounding_box2.box_trans.vertice3.y };
                            /*std::cout << "B ( " << getbox2.verticesList[0].x << "," << getbox2.verticesList[0].y << ")" << std::endl;
                            std::cout << "B ( " << getbox2.verticesList[1].x << "," << getbox2.verticesList[1].y << ")" << std::endl;
                            std::cout << "B ( " << getbox2.verticesList[2].x << "," << getbox2.verticesList[2].y << ")" << std::endl;
                            std::cout << "B ( " << getbox2.verticesList[3].x << "," << getbox2.verticesList[3].y << ")" << std::endl;*/

                            /*std::cout << "B ( " << getTransform2.vertice0.x << "," << getTransform2.vertice0.y << ")" << std::endl;
                            std::cout << "B ( " << getTransform2.vertice1.x << "," << getTransform2.vertice1.y << ")" << std::endl;
                            std::cout << "B ( " << getTransform2.vertice2.x << "," << getTransform2.vertice2.y << ")" << std::endl;
                            std::cout << "B ( " << getTransform2.vertice3.x << "," << getTransform2.vertice3.y << ")" << std::endl;*/
                            /* 
                            //getbox.vertices.clear();
                            //getbox.vertices.shrink_to_fit();
                            //getbox.vertices.push_back(obj2_vertice0);
                            //getbox.vertices.push_back(obj2_vertice1);
                            //getbox.vertices.push_back(obj2_vertice2);
                            //getbox.vertices.push_back(obj2_vertice3);

                            //Velocity here is a placeholder
                            /*if (Thomas::CollisionIntersection_RectRect(getbox.bounds, getRigid1.Velocity, getbox2.bounds, getRigid2.Velocity) == true) {
                                std::cout << entity << ", " << entity2 << ": colliding" << std::endl;
                            }

                            else {
                                std::cout << entity << ", " << entity2 << ": not colliding" << std::endl;
                            }*/
                            Vec2 normal;
                            float depth;
                            if (Thomas::SATPolygonIntersection(getbox.verticesList, getbox2.verticesList, normal, depth))
                            {
                                /*std::cout << "___________________________Colliding___________________________";*/
                                getbounding_box.collision_detected = 1;
                                getbounding_box2.collision_detected = 1;

                                //getRigid1.m_Position.x = getTransform1.translation.x;
                                //getRigid1.m_Position.y = getTransform1.translation.y;
     
                                //physicsSystem.addForce(getRigid1, depth / 2.f, timestep);
                                //getRigid1.m_Position += -normal * timestep;

                                //
                                //getTransform1.translation.x = getRigid1.m_Position.x;
                                //getTransform1.translation.y = getRigid1.m_Position.y;

                                //getRigid2.m_Position.x = getTransform2.translation.x;
                                //getRigid2.m_Position.y = getTransform2.translation.y;

                                //physicsSystem.addForce(getRigid2, depth / 2.f, timestep);
                                //getRigid2.m_Position += normal * timestep;

                                ////transform.translation.x = getRigid.m_Position.x;
                                //getTransform2.translation.x = getRigid2.m_Position.x;
                                //getTransform2.translation.y = getRigid2.m_Position.y;
                            }
                            else {
                                getbounding_box.collision_detected = 0;
                                getbounding_box2.collision_detected = 0;
                            }
                                factory.ChangeComponent<Thomas::RigidBody>(entity, getRigid1);//Updates data for component
                                factory.ChangeComponent<Thomas::Transform>(entity, getTransform1);//Updates data for component
                                factory.ChangeComponent<Thomas::Box_collider>(entity, getbounding_box);//Updates data for component
                                factory.ChangeComponent<Thomas::RigidBody>(entity2, getRigid2);//Updates data for component
                                factory.ChangeComponent<Thomas::Transform>(entity2, getTransform2);//Updates data for component
                                factory.ChangeComponent<Thomas::Box_collider>(entity2, getbounding_box2);//Updates data for component

                            
                        }
                    }
                }
            }
        }
        /*std::cout << std::endl;*/
    }

    void Physics::Input(Entity entity, Timestep timestep) {

        auto getRigid = factory.GetComponent<RigidBody>(Graphics::sel); //next time we will use player entity id instead of graphics::sel
        auto transform = factory.GetComponent<Transform>(Graphics::sel); //next time we will use player entity id instead of graphics::sel
        auto boxCollider = factory.GetComponent<Box_collider>(Graphics::sel);

        if (Input::IsKeyPressed(TH_KEY_W)) {

            getRigid.m_Position.y = transform.translation.y;

            physicsSystem.addForce(getRigid, 10, timestep);
            //std::cout << getRigid.Velocity << std::endl;
            //getRigid.m_Position.x = transform.translation.x;

            //getRigid.m_Position.x += getRigid.Velocity * ts;

            getRigid.m_Position.y += -getRigid.Velocity * timestep;

            boxCollider.box_trans.translation.y += -getRigid.Velocity * timestep;

            //transform.translation.x = getRigid.m_Position.x;
            transform.translation.y = getRigid.m_Position.y;

        }

        if (Input::IsKeyPressed(TH_KEY_A)) {
            getRigid.m_Position.x = transform.translation.x;
            physicsSystem.addForce(getRigid, 10, timestep);
            getRigid.m_Position.x += -getRigid.Velocity * timestep;
            boxCollider.box_trans.translation.x += -getRigid.Velocity * timestep;
            transform.translation.x = getRigid.m_Position.x;

            //physicsSystem.temp(transform.translation.x, -rigidbody.Velocity);
            //std::cout << "move a\n";
        }
        
        if (Input::IsKeyPressed(TH_KEY_S)) {
            getRigid.m_Position.y = transform.translation.y;
            physicsSystem.addForce(getRigid, 10, timestep);
            getRigid.m_Position.y += getRigid.Velocity * timestep;
            boxCollider.box_trans.translation.y += getRigid.Velocity * timestep;
            transform.translation.y = getRigid.m_Position.y;
            
            //physicsSystem.temp(transform.translation.y, rigidbody.Velocity);
            //std::cout << "move s\n";
        }
        
        if (Input::IsKeyPressed(TH_KEY_D)) {
            getRigid.m_Position.x = transform.translation.x;
            physicsSystem.addForce(getRigid, 10, timestep);
            getRigid.m_Position.x += getRigid.Velocity * timestep;
            boxCollider.box_trans.translation.x += getRigid.Velocity * timestep;
            transform.translation.x = getRigid.m_Position.x;
            // physicsSystem.temp(transform.translation.x, rigidbody.Velocity);
            //std::cout << "move d\n";
        }
        

        getRigid.Velocity = 0.0f;
        factory.ChangeComponent<Thomas::RigidBody>(Graphics::sel, getRigid);//Updates data for component
        factory.ChangeComponent<Thomas::Transform>(Graphics::sel, transform);//Updates data for component
        factory.ChangeComponent<Thomas::Box_collider>(Graphics::sel, boxCollider);//Updates data for component
    }
}
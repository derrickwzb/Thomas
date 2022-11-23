 #include "thpch.h"
#include "physicsSystem.h"
#include "Platform/Windows/WindowsInput.h"
#include "Thomas/Core/KeyCodes.h"
#include "Thomas/Scene/Entity.h"
#include "Thomas/Scene/Scene.h"

int g_dt = 5;
//float acceleration = 0.02;

namespace Thomas {



    void Physics::addForce(RigidBody& x, float force, Timestep timestep) {
        x.Velocity += ( (1 / x.GetMass()) * force) * timestep;
    }


    void Physics::Update(Scene* m_Context, Timestep timestep) {

        auto start = std::chrono::steady_clock::now();
        std::map<EntityID, Signature>& entities = m_Context->m_Registry->GetEntities();
       
        for (auto const& e : entities) {
            Entity entity{ e.first , m_Context };
            //Static rect to rect collision
            if (entity.HasComponent<BoxCollider2D>()) {

                auto& getbox = entity.GetComponent<BoxCollider2D>();
                auto& getRigid1 = entity.GetComponent<RigidBody>();
                auto& getTransform1 = entity.GetComponent<Transform>();
                auto& getbounding_box = entity.GetComponent<Box_collider>();

               
                getbox.verticesList[0] = Vec2{ getbounding_box.box_trans.vertice0.x , getbounding_box.box_trans.vertice0.y };
                getbox.verticesList[1] = Vec2{ getbounding_box.box_trans.vertice1.x , getbounding_box.box_trans.vertice1.y };
                getbox.verticesList[2] = Vec2{ getbounding_box.box_trans.vertice2.x , getbounding_box.box_trans.vertice2.y };
                getbox.verticesList[3] = Vec2{ getbounding_box.box_trans.vertice3.x , getbounding_box.box_trans.vertice3.y };

                //getbox.verticesList = getbounding_box.box_trans.vertices;
                
                for (auto const& e2 : entities) {
                    Entity entity2{ e2.first , m_Context };
                    if (entity != entity2 ){

                        if (entity2.HasComponent<BoxCollider2D>()) {

                            auto& getbox2 = entity2.GetComponent<BoxCollider2D>();
                            auto& getRigid2 = entity2.GetComponent<RigidBody>();
                            auto& getTransform2 = entity2.GetComponent<Transform>();
                            auto& getbounding_box2 = entity2.GetComponent<Box_collider>();

    
                            getbox2.verticesList[0] = Vec2{ getbounding_box2.box_trans.vertice0.x , getbounding_box2.box_trans.vertice0.y };
                            getbox2.verticesList[1] = Vec2{ getbounding_box2.box_trans.vertice1.x , getbounding_box2.box_trans.vertice1.y };
                            getbox2.verticesList[2] = Vec2{ getbounding_box2.box_trans.vertice2.x , getbounding_box2.box_trans.vertice2.y };
                            getbox2.verticesList[3] = Vec2{ getbounding_box2.box_trans.vertice3.x , getbounding_box2.box_trans.vertice3.y };

                            //getbox2.verticesList = getbounding_box2.box_trans.vertices;
                            
                            Vec2 normal;
                            float depth;
                            if (Thomas::SATPolygonIntersection(getbox.verticesList, getbox2.verticesList, normal, depth))
                            {
                                getbounding_box.collision_detected = 1;
                                getbounding_box2.collision_detected = 1;

                                glm::vec2 diff_1, diff_2;
                                diff_1 = glm::vec2(getTransform1.translation.x - getbounding_box.box_trans.translation.x, getTransform1.translation.y - getbounding_box.box_trans.translation.y);
                                diff_2 = glm::vec2(getTransform2.translation.x - getbounding_box2.box_trans.translation.x, getTransform2.translation.y - getbounding_box2.box_trans.translation.y);

                                getRigid1.m_Position.x = getbounding_box.box_trans.translation.x;
                                getRigid1.m_Position.y = getbounding_box.box_trans.translation.y;
                                
                                physicsSystem.addForce(getRigid1, depth / 2.f, timestep);
                                getRigid1.m_Position += -normal * timestep;

                                getbounding_box.box_trans.translation.x = getRigid1.m_Position.x;
                                getbounding_box.box_trans.translation.y = getRigid1.m_Position.y;

                                getTransform1.translation.x = (getRigid1.m_Position.x + diff_1.x);
                                getTransform1.translation.y = (getRigid1.m_Position.y + diff_1.y);
                                
                                getRigid2.m_Position.x = getbounding_box2.box_trans.translation.x;
                                getRigid2.m_Position.y = getbounding_box2.box_trans.translation.y;

                                physicsSystem.addForce(getRigid2, depth / 2.f, timestep);
                                getRigid2.m_Position += normal * timestep;

                                getbounding_box2.box_trans.translation.x = getRigid2.m_Position.x;
                                getbounding_box2.box_trans.translation.y = getRigid2.m_Position.y;

                               
                                getTransform2.translation.x = getbounding_box2.box_trans.translation.x + diff_2.x;
                                getTransform2.translation.y = getbounding_box2.box_trans.translation.y + diff_2.y;
                            }
                            else {
                                getbounding_box.collision_detected = 0;
                                getbounding_box2.collision_detected = 0;
                            }
                                
                        }
                    }
                }
            }
        }
        /*std::cout << std::endl;*/

        auto stop = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = (stop - start);
        Physic_timetaken = duration.count();
    }

    //void Physics::Input(EntityID entity, Timestep timestep) {

    //    auto getRigid = factory.GetComponent<RigidBody>(Graphics::sel); //next time we will use player entity id instead of graphics::sel
    //    auto transform = factory.GetComponent<Transform>(Graphics::sel); //next time we will use player entity id instead of graphics::sel
    //    auto boxCollider = factory.GetComponent<Box_collider>(Graphics::sel);

    //    if (Input::IsKeyPressed(TH_KEY_W)) {

    //        getRigid.m_Position.y = transform.translation.y;

    //        physicsSystem.addForce(getRigid, 50, timestep);
    //        //std::cout << getRigid.Velocity << std::endl;
    //        //getRigid.m_Position.x = transform.translation.x;

    //        //getRigid.m_Position.x += getRigid.Velocity * ts;

    //        getRigid.m_Position.y += -getRigid.Velocity * timestep;

    //        boxCollider.box_trans.translation.y += -getRigid.Velocity * timestep;

    //        //transform.translation.x = getRigid.m_Position.x;
    //        transform.translation.y = getRigid.m_Position.y;

    //    }

    //    if (Input::IsKeyPressed(TH_KEY_A)) {
    //        getRigid.m_Position.x = transform.translation.x;
    //        physicsSystem.addForce(getRigid, 50, timestep);
    //        getRigid.m_Position.x += -getRigid.Velocity * timestep;
    //        boxCollider.box_trans.translation.x += -getRigid.Velocity * timestep;
    //        transform.translation.x = getRigid.m_Position.x;

    //        //physicsSystem.temp(transform.translation.x, -rigidbody.Velocity);
    //        //std::cout << "move a\n";
    //    }
    //    
    //    if (Input::IsKeyPressed(TH_KEY_S)) {
    //        getRigid.m_Position.y = transform.translation.y;
    //        physicsSystem.addForce(getRigid, 50, timestep);
    //        getRigid.m_Position.y += getRigid.Velocity * timestep;
    //        boxCollider.box_trans.translation.y += getRigid.Velocity * timestep;
    //        transform.translation.y = getRigid.m_Position.y;
    //        
    //        //physicsSystem.temp(transform.translation.y, rigidbody.Velocity);
    //        //std::cout << "move s\n";
    //    }
    //    
    //    if (Input::IsKeyPressed(TH_KEY_D)) {
    //        getRigid.m_Position.x = transform.translation.x;
    //        physicsSystem.addForce(getRigid, 50, timestep);
    //        getRigid.m_Position.x += getRigid.Velocity * timestep;
    //        boxCollider.box_trans.translation.x += getRigid.Velocity * timestep;
    //        transform.translation.x = getRigid.m_Position.x;
    //        // physicsSystem.temp(transform.translation.x, rigidbody.Velocity);
    //        //std::cout << "move d\n";
    //    }
    //    

    //    getRigid.Velocity = 0.0f;
    //    factory.UpdateComponent<Thomas::RigidBody>(Graphics::sel, getRigid);//Updates data for component
    //    factory.UpdateComponent<Thomas::Transform>(Graphics::sel, transform);//Updates data for component
    //    factory.UpdateComponent<Thomas::Box_collider>(Graphics::sel, boxCollider);//Updates data for component
    //}
}
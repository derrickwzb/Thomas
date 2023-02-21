 #include "thpch.h"
#include "physicsSystem.h"
#include "Platform/Windows/WindowsInput.h"
#include "Thomas/Core/KeyCodes.h"
#include "Thomas/Scene/Entity.h"
#include "Thomas/Scene/Scene.h"

int g_dt = 5;


namespace Thomas {

    void Physics::addForce(RigidBody& x, float force, Timestep timestep) {
        x.Velocity += ((1 / x.GetMass()) * force) * static_cast<float>(timestep);
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
                auto& gettype = entity.GetComponent<ObjectType>();
                
                getbox.verticesList[0] = Vec2{ getbounding_box.box_trans.global_vertice0.x , getbounding_box.box_trans.global_vertice0.y };
                getbox.verticesList[1] = Vec2{ getbounding_box.box_trans.global_vertice1.x , getbounding_box.box_trans.global_vertice1.y };
                getbox.verticesList[2] = Vec2{ getbounding_box.box_trans.global_vertice2.x , getbounding_box.box_trans.global_vertice2.y };
                getbox.verticesList[3] = Vec2{ getbounding_box.box_trans.global_vertice3.x , getbounding_box.box_trans.global_vertice3.y };

                for (auto const& e2 : entities) {
                    Entity entity2{ e2.first , m_Context };
                    if (entity != entity2) {

                        if (entity2.HasComponent<BoxCollider2D>()) {

                            auto& getbox2 = entity2.GetComponent<BoxCollider2D>();
                            auto& getRigid2 = entity2.GetComponent<RigidBody>();
                            auto& getTransform2 = entity2.GetComponent<Transform>();
                            auto& getbounding_box2 = entity2.GetComponent<Box_collider>();
                            auto& gettype2 = entity2.GetComponent<ObjectType>();

                            getbox2.verticesList[0] = Vec2{ getbounding_box2.box_trans.global_vertice0.x , getbounding_box2.box_trans.global_vertice0.y };
                            getbox2.verticesList[1] = Vec2{ getbounding_box2.box_trans.global_vertice1.x , getbounding_box2.box_trans.global_vertice1.y };
                            getbox2.verticesList[2] = Vec2{ getbounding_box2.box_trans.global_vertice2.x , getbounding_box2.box_trans.global_vertice2.y };
                            getbox2.verticesList[3] = Vec2{ getbounding_box2.box_trans.global_vertice3.x , getbounding_box2.box_trans.global_vertice3.y };

                            Vec2 normal;
                            float depth;
                            if (Thomas::SATPolygonIntersection(getbox.verticesList, getbox2.verticesList, normal, depth))
                            {
                                getbounding_box.collision_detected = 1;
                                getbounding_box2.collision_detected = 1;

                                glm::vec2 diff_1, diff_2;
                                diff_1 = glm::vec2(getTransform1.translation.x - getbounding_box.box_trans.translation.x, getTransform1.translation.y - getbounding_box.box_trans.translation.y);
                                diff_2 = glm::vec2(getTransform2.translation.x - getbounding_box2.box_trans.translation.x, getTransform2.translation.y - getbounding_box2.box_trans.translation.y);

                                //collision response between different object
                                if (gettype.type == ObjectTypeID::player)
                                {
                                    //player vs obstacle
                                    if (gettype2.type == ObjectTypeID::obstacle)
                                    {
                                        //push back player
                                        getRigid1.m_Position.x = getbounding_box.box_trans.translation.x;
                                        getRigid1.m_Position.y = getbounding_box.box_trans.translation.y;

                                        physicsSystem.addForce(getRigid1, depth / 2.f, timestep);
                                        getRigid1.m_Position += -normal * timestep;

                                        getbounding_box.box_trans.translation.x = getRigid1.m_Position.x;
                                        getbounding_box.box_trans.translation.y = getRigid1.m_Position.y;

                                        getTransform1.translation.x = (getRigid1.m_Position.x + diff_1.x);
                                        getTransform1.translation.y = (getRigid1.m_Position.y + diff_1.y);
                                    }
                                    //player vs enemy
                                    if (gettype2.type == ObjectTypeID::enemy)
                                    {
                                        auto& getcombatdata = entity.GetComponent<CombatComponent>();
                                        auto& getcombatdata2 = entity2.GetComponent<CombatComponent>();

                                        //push back player
                                        getRigid1.m_Position.x = getbounding_box.box_trans.translation.x;
                                        getRigid1.m_Position.y = getbounding_box.box_trans.translation.y;

                                        physicsSystem.addForce(getRigid1, depth / 2.f, timestep);
                                        getRigid1.m_Position += -normal * timestep;

                                        getbounding_box.box_trans.translation.x = getRigid1.m_Position.x;
                                        getbounding_box.box_trans.translation.y = getRigid1.m_Position.y;

                                        getTransform1.translation.x = (getRigid1.m_Position.x + diff_1.x);
                                        getTransform1.translation.y = (getRigid1.m_Position.y + diff_1.y);


                                        //push back enemy
                                        getRigid2.m_Position.x = getbounding_box2.box_trans.translation.x;
                                        getRigid2.m_Position.y = getbounding_box2.box_trans.translation.y;

                                        physicsSystem.addForce(getRigid2, depth / 2.f, timestep);
                                        getRigid2.m_Position += normal * timestep;

                                        getbounding_box2.box_trans.translation.x = getRigid2.m_Position.x;
                                        getbounding_box2.box_trans.translation.y = getRigid2.m_Position.y;

                                        getTransform2.translation.x = getbounding_box2.box_trans.translation.x + diff_2.x;
                                        getTransform2.translation.y = getbounding_box2.box_trans.translation.y + diff_2.y;


                                        //enemy attack player when collide
                                        getcombatdata2.attack_interval -= timestep;
                                        if (getcombatdata2.attack_interval <= 0)
                                        {
                                            getcombatdata.health -= getcombatdata2.attack;
                                            getcombatdata2.attack_interval = 0.5f;
                                        }
                                    }
                                    //player vs pick ups
                                    if (gettype2.type == ObjectTypeID::pickup)
                                    {
                                        auto& tex2 = entity2.GetComponent<Texture>();

                                        //change pick up texture when collide
                                        if (gettype2.pickup_collide == false) {
                                            tex2.texid += 1;
                                            gettype2.pickup_collide = true;
                                        }
                                        
                                    }
                                    //player vs goal(exit to next level or win screen)
                                    if (gettype2.type == ObjectTypeID::goal) 
                                    {
                                        //check if player has collect 2 recipe
                                        if (gettype.win_point < 2) {
                                            gettype2.win_collide = false;
                                        }
                                        else {
                                            gettype2.win_collide = true;
                                        }

                                        //if win condition not reached then push back player
                                        if (gettype2.win_collide == false) {
                                            getRigid1.m_Position.x = getbounding_box.box_trans.translation.x;
                                            getRigid1.m_Position.y = getbounding_box.box_trans.translation.y;

                                            physicsSystem.addForce(getRigid1, depth / 2.f, timestep);
                                            getRigid1.m_Position += -normal * timestep;

                                            getbounding_box.box_trans.translation.x = getRigid1.m_Position.x;
                                            getbounding_box.box_trans.translation.y = getRigid1.m_Position.y;

                                            getTransform1.translation.x = (getRigid1.m_Position.x + diff_1.x);
                                            getTransform1.translation.y = (getRigid1.m_Position.y + diff_1.y);
                                        }
                                        else {
                                            gettype.win_point = 10;
                                        }
                                    }
                                }

                                    if (gettype.type == ObjectTypeID::enemy)
                                    {
                                        //enemy vs obstacle
                                        if (gettype2.type == ObjectTypeID::obstacle)
                                        {
                                            //push back enemy
                                            getRigid1.m_Position.x = getbounding_box.box_trans.translation.x;
                                            getRigid1.m_Position.y = getbounding_box.box_trans.translation.y;

                                            physicsSystem.addForce(getRigid1, depth / 2.f, timestep);
                                            getRigid1.m_Position += -normal * timestep;

                                            getbounding_box.box_trans.translation.x = getRigid1.m_Position.x;
                                            getbounding_box.box_trans.translation.y = getRigid1.m_Position.y;

                                            getTransform1.translation.x = (getRigid1.m_Position.x + diff_1.x);
                                            getTransform1.translation.y = (getRigid1.m_Position.y + diff_1.y);
                                        }
                                        //enemy vs bullet
                                        if (gettype2.type == ObjectTypeID::bullet)
                                        {
                                            auto& getcombatdata = entity.GetComponent<CombatComponent>();
                                            auto& getcombatdata2 = entity2.GetComponent<CombatComponent>();

                                            //reduce enemy health base on bullet attack
                                            getcombatdata.health -= getcombatdata2.attack;

                                            getbounding_box.collision_detected = 0;
                                            getbounding_box2.collision_detected = 0;

                                            //destory the bullet after collide
                                            m_Context->DestroyEntity(entity2);
                                            break;
                                        }
                                    }

                                    if (gettype.type == ObjectTypeID::obstacle)
                                    {
                                        //obstacle vs bullet
                                        if (gettype2.type == ObjectTypeID::bullet)
                                        {
                                            //destory the bullet after collide
                                            m_Context->DestroyEntity(entity2);
                                            break;
                                        }
                                    }
                                }
                                else {
                                    getbounding_box.collision_detected = 0;
                                    getbounding_box2.collision_detected = 0;

                                    //change back the pick up texture 
                                    if (gettype.type == ObjectTypeID::pickup) {
                                        auto& tex = entity.GetComponent<Texture>();
                                        if (gettype.pickup_collide == true) {
                                            tex.texid -= 1;
                                            gettype.pickup_collide = false;
                                        }
                                        
                                    }
                                }


                            }
                        }
                    }


                    //check if enemy is dead
                    if (gettype.type == ObjectTypeID::enemy)
                    {
                        auto& getcombatdata = entity.GetComponent<CombatComponent>();
                        //if dead
                        if (getcombatdata.health <= 0)
                        {
                            entity.RemoveComponent<Box_collider>();
                            getcombatdata.attack = 0.f;
                            auto& tex = entity.GetComponent<Texture>();

                            getcombatdata.death_timer -= timestep;

                            //death animation
                            if (getcombatdata.death_timer >= 1.f) {
                                tex.texid = stash.Text_Storage["die 1.png"];
                            }
                            else if (getcombatdata.death_timer >= 0.5f) {
                                tex.texid = stash.Text_Storage["die 2.png"];
                            }
                            else if (getcombatdata.death_timer >= 0.f) {
                                tex.texid = stash.Text_Storage["die 3.png"];
                            }
                            else if (getcombatdata.death_timer <= 0.f) {
                                //destoory enemy
                                m_Context->DestroyEntity(entity);
                                break;
                            }
                        }
                    }


                }
            }

        auto stop = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = (stop - start);
        Physic_timetaken = duration.count();

    }
}

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
        x.Velocity += ((1 / x.GetMass()) * force) * static_cast<float>(timestep);
    }


    void Physics::Update(Scene* m_Context, Timestep timestep) {

        auto start = std::chrono::steady_clock::now();
        std::map<EntityID, Signature>& entities = m_Context->m_Registry->GetEntities();
        //std::map<EntityID, Signature>::iterator e = entities.begin();
        for (auto const& e : entities) {
            Entity entity{ e.first , m_Context };
            //Static rect to rect collision
            if (entity.HasComponent<BoxCollider2D>()) {

                auto& getbox = entity.GetComponent<BoxCollider2D>();
                auto& getRigid1 = entity.GetComponent<RigidBody>();
                auto& getTransform1 = entity.GetComponent<Transform>();
                auto& getbounding_box = entity.GetComponent<Box_collider>();
                auto& gettype = entity.GetComponent<ObjectType>();
                auto& getcombatdata = entity.GetComponent<CombatComponent>();

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

                                //getRigid1.m_Position.x = getbounding_box.box_trans.translation.x;
                                //getRigid1.m_Position.y = getbounding_box.box_trans.translation.y;
                                //
                                //physicsSystem.addForce(getRigid1, depth / 2.f, timestep);
                                //getRigid1.m_Position += -normal * timestep;

                                //getbounding_box.box_trans.translation.x = getRigid1.m_Position.x;
                                //getbounding_box.box_trans.translation.y = getRigid1.m_Position.y;

                                //getTransform1.translation.x = (getRigid1.m_Position.x + diff_1.x);
                                //getTransform1.translation.y = (getRigid1.m_Position.y + diff_1.y);


                                //getRigid2.m_Position.x = getbounding_box2.box_trans.translation.x;
                                //getRigid2.m_Position.y = getbounding_box2.box_trans.translation.y;

                                //physicsSystem.addForce(getRigid2, depth / 2.f, timestep);
                                //getRigid2.m_Position += normal * timestep;

                                //getbounding_box2.box_trans.translation.x = getRigid2.m_Position.x;
                                //getbounding_box2.box_trans.translation.y = getRigid2.m_Position.y;


                                //getTransform2.translation.x = getbounding_box2.box_trans.translation.x + diff_2.x;
                                //getTransform2.translation.y = getbounding_box2.box_trans.translation.y + diff_2.y;

                                if (gettype.type == ObjectTypeID::player)
                                {
                                    if (gettype2.type == ObjectTypeID::obstacle)
                                    {
                                        getRigid1.m_Position.x = getbounding_box.box_trans.translation.x;
                                        getRigid1.m_Position.y = getbounding_box.box_trans.translation.y;

                                        physicsSystem.addForce(getRigid1, depth / 2.f, timestep);
                                        getRigid1.m_Position += -normal * timestep;

                                        getbounding_box.box_trans.translation.x = getRigid1.m_Position.x;
                                        getbounding_box.box_trans.translation.y = getRigid1.m_Position.y;

                                        getTransform1.translation.x = (getRigid1.m_Position.x + diff_1.x);
                                        getTransform1.translation.y = (getRigid1.m_Position.y + diff_1.y);
                                    }
                                    if (gettype2.type == ObjectTypeID::enemy)
                                    {
                                        
                                        auto& getcombatdata2 = entity2.GetComponent<CombatComponent>();

                                        getRigid1.m_Position.x = getbounding_box.box_trans.translation.x;
                                        getRigid1.m_Position.y = getbounding_box.box_trans.translation.y;

                                        //if (getbox.isTrigger == false)
                                        //{
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


                                            getcombatdata2.attack_interval -= timestep;
                                            if (getcombatdata2.attack_interval <= 0)
                                            {
                                                getcombatdata.health -= getcombatdata2.attack;
                                                getcombatdata2.attack_interval = 0.5f;
                                            }

                                            //if (getcombatdata.health <= 0)
                                            //{
                                            //    m_Context->DestroyEntity(entity);
                                            //}
                                    }
                                }

                                    if (gettype.type == ObjectTypeID::enemy)
                                    {
                                        if (gettype2.type == ObjectTypeID::obstacle)
                                        {
                                            getRigid1.m_Position.x = getbounding_box.box_trans.translation.x;
                                            getRigid1.m_Position.y = getbounding_box.box_trans.translation.y;

                                            physicsSystem.addForce(getRigid1, depth / 2.f, timestep);
                                            getRigid1.m_Position += -normal * timestep;

                                            getbounding_box.box_trans.translation.x = getRigid1.m_Position.x;
                                            getbounding_box.box_trans.translation.y = getRigid1.m_Position.y;

                                            getTransform1.translation.x = (getRigid1.m_Position.x + diff_1.x);
                                            getTransform1.translation.y = (getRigid1.m_Position.y + diff_1.y);
                                        }
                                        if (gettype2.type == ObjectTypeID::bullet)
                                        {
                                            //auto& getcombatdata = entity.GetComponent<CombatComponent>();
                                            auto& getcombatdata2 = entity2.GetComponent<CombatComponent>();

                                            getcombatdata.health -= getcombatdata2.attack;

                                            auto& adddelete2 = entity2.AddComponent<DeleteComponent>();
                                            adddelete2.isdeleted = true;
                                            //m_Context->DestroyEntity(entity2);
                                            getbounding_box.collision_detected = 0;
                                            getbounding_box2.collision_detected = 0;

                                            //if (getcombatdata.health <= 0)
                                            //{
                                            //    auto& adddelete = entity.AddComponent<DeleteComponent>();
                                            //    adddelete.isdeleted = true;
                                            //    //m_Context->DestroyEntity(entity);
                                            //}
                                        }
                                    }

                                    if (gettype.type == ObjectTypeID::bullet)
                                    {

                                    }
                                }
                                else {
                                    getbounding_box.collision_detected = 0;
                                    getbounding_box2.collision_detected = 0;
                                }


                            }
                        }
                    }



                    if (gettype.type == ObjectTypeID::enemy && getcombatdata.health <= 0)
                    {
                        auto& tex = entity.GetComponent<Texture>();

                        getcombatdata.death_timer -= timestep;

                        if (getcombatdata.death_timer >= 1.f) {
                            tex.texid = 55;
                        }
                        else if (getcombatdata.death_timer >= 0.5f) {
                            tex.texid = 56;
                        }
                        else if (getcombatdata.death_timer >= 0.f) {
                            tex.texid = 57;
                        }
                        else if (getcombatdata.death_timer <= 0.f) {
                            //auto& adddelete = entity.AddComponent<DeleteComponent>();
                            //adddelete.isdeleted = true;
                            m_Context->DestroyEntity(entity);
                        }
                    }

                }
            }
            /*std::cout << std::endl;*/

        //}

        auto stop = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = (stop - start);
        Physic_timetaken = duration.count();

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

    void Physics::ClickButton(Scene* m_Context) {

        
        
        //if (Input::IsMouseButtonPressed(0)) {
        //    std::cout << Input::GetMouseX() << ", " << Input::GetMouseY() << std::endl;
        //}



        //std::map<EntityID, Signature>& entities = m_Context->m_Registry->GetEntities();

        //for (auto const& e : entities) {
        //    Entity entity{ e.first , m_Context };
        //    auto& get_trans = entity.GetComponent<Transform>();

        //    float minx = get_trans.translation.x - get_trans.scaling.x;
        //    float miny = get_trans.translation.y - get_trans.scaling.y;
        //    float maxx = get_trans.translation.x + get_trans.scaling.x;
        //    float maxy = get_trans.translation.y + get_trans.scaling.y;

        //    if (Input::GetMouseX() >= minx && Input::GetMouseY() >= miny &&
        //        Input::GetMouseX() <= maxx && Input::GetMouseY() <= maxy &&
        //        Input::IsMouseButtonPressed(0)) {
        //        get_trans.mouse_clicking = true;
        //        std::cout << "clicked" << std::endl;
        //    }
        //    else {
        //        get_trans.mouse_clicking = false;
        //    }
        //}



        //double Viewport_CursX, Viewport_CursY;
        //Viewport_CursX = Input::GetMouseX() - ImGui::GetWindowPos().x - (Graphics::m_ViewportSize.x / 2.f) - vp_pos.x + 10.f;
        //Viewport_CursY = -(Input::GetMouseY() - ImGui::GetWindowPos().y - (Graphics::m_ViewportSize.y / 2.f) - vp_pos.y + (button_offset.y / 2) + (button_size.y / 2));

        //std::map<EntityID, Signature> group = m_Context->m_Registry->GetEntities();
        //for (auto& e : group) {
        //    if (m_Context->m_Registry->HasComponent<Transform>(e.first)) {
        //        Entity objs = { e.first, m_Context };
        //        auto& trans_stuff = objs.GetComponent<Transform>();
        //        auto& box_stuff = objs.GetComponent<Box_collider>();

        //        trans_stuff.minmax_screen(Graphics::m_ViewportSize.x, Graphics::m_ViewportSize.y);

        //        // Collision check between the on_screen mouse cursor and the on_screen objects
        //        if ((Viewport_CursX > trans_stuff.screen_min.x && Viewport_CursX<trans_stuff.screen_max.x && Viewport_CursY>trans_stuff.screen_min.y && Viewport_CursY < trans_stuff.screen_max.y) && Input::IsMouseButtonPressed(0) && objs.GetID() != 0) {
        //            ++Graphics::obj_counter;
        //            if (Graphics::obj_counter == 1) {
        //                Graphics::sel = objs.GetID();
        //                Graphics::sel_layer = trans_stuff.z_axis;
        //                Entity e = { objs.GetID() , m_ActiveScene.get() };
        //                m_SceneHierarchyPanel.GetSelection() = e;
        //                Graphics::obj_clicked = true;
        //            }
        //            else {
        //                if (trans_stuff.z_axis < Graphics::sel_layer) {
        //                    Graphics::sel = objs.GetID();
        //                    Graphics::sel_layer = trans_stuff.z_axis;
        //                    Entity e = { objs.GetID() , m_ActiveScene.get() };
        //                    m_SceneHierarchyPanel.GetSelection() = e;
        //                    Graphics::obj_clicked = true;
        //                }
        //            }
        //            //std::cout << "Items: " << Graphics::obj_clicked << std::endl;
        //        }
        //    }
        //}
    }


}

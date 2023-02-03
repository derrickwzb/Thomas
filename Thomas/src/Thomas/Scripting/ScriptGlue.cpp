#include "thpch.h"
#include "ScriptGlue.h"
#include "Thomas/Scene/Entity.h"
#include "Thomas/Scene/Scene.h"
#include  "Thomas/Scripting/ScriptEngine.h"
#include "Thomas/Core/KeyCodes.h"
#include "Thomas/Core/Input.h"
#include "Thomas/Scene/Components.h"
#include "Thomas/Audio/AudioEngine.h"

#include "mono/metadata/object.h"
#include "mono/metadata/reflection.h"
#include "glm/glm.hpp"

#include "Thomas/Scene/SceneSerializer.h"

namespace Thomas {

    static std::unordered_map<MonoType*, std::function<bool(Entity)>> s_EntityHasComponentFuncs;
    static std::unordered_map<MonoType*, std::function<bool(Entity)>> s_EntityAddComponentFuncs;


//Using internal call must have the namespace of where the function is followed by
//the class or wherever the function is inside the namespace follow by the scope operator
#define TH_ADD_INTERNAL_CALL(Name) mono_add_internal_call("Thomas.InternalCalls::" #Name, Name)

    static void NativeLog(MonoString* string, int parameter)
    {
        char* cStr = mono_string_to_utf8(string);
        std::string str(cStr);
        mono_free(cStr);
        std::cout << str << ", " << parameter << std::endl;
    }

    //Having an outresult to copy the data into the pre existing memory in C#
    //Memory management and garbage collection is done in C#
    static void NativeLog_Vector(glm::vec3* parameter, glm::vec3* outResult)
    {
        std::cout << (parameter->x) << "," << (parameter->y) << "," << (parameter->z) << std::endl;
        *outResult = glm::normalize(*parameter);
    }

    static float NativeLog_VectorDot(glm::vec3* parameter)
    {
        std::cout << (parameter->x) << "," << (parameter->y) << "," << (parameter->z) << std::endl;
        return glm::dot(*parameter, *parameter);
    }
    
    static bool Entity_HasComponent(EntityID entityID, MonoReflectionType* componentType)
    {
        Scene* scene = ScriptEngine::GetSceneContext();
        //TH_CORE_ASSERT(scene);
        Entity entity = { entityID , scene }; //This is the way to find the particular entity for a particular scene
        //TH_CORE_ASSERT(entity);

        MonoType* managedType = mono_reflection_type_get_type(componentType);
        //TH_CORE_ASSERT(s_EntityHasComponentFuncs.find(managedType) != s_EntityHasComponentFuncs.end());
        return s_EntityHasComponentFuncs.at(managedType)(entity);
    }

    //static void Entity_AddComponent(EntityID entityID, MonoReflectionType* componentType)
    //{
    //    Scene* scene = ScriptEngine::GetSceneContext();
    //    //TH_CORE_ASSERT(scene);
    //    Entity entity = { entityID , scene }; //This is the way to find the particular entity for a particular scene
    //    //TH_CORE_ASSERT(entity);

    //    MonoType* managedType = mono_reflection_type_get_type(componentType);
    //}

    static void Transform_GetTranslation(EntityID entityID, glm::vec2* outTranslation)
    { 
        Scene* scene = ScriptEngine::GetSceneContext();
        Entity entity = { entityID , scene }; //This is the way to find the particular entity for a particular scene
        *outTranslation = entity.GetComponent<Transform>().translation;  
    }

    static void Transform_SetTranslation(EntityID entityID, glm::vec3* translation)
    {
        Scene* scene = ScriptEngine::GetSceneContext();
        Entity entity = { entityID , scene }; //This is the way to find the particular entity for a particular scene
        entity.GetComponent<Transform>().translation = *translation;
    }

    static void RigidBody_ChangePosition(EntityID entityID, float posX, float posY)
    {
        Scene* scene = ScriptEngine::GetSceneContext();
        //TH_CORE_ASSERT(scene);
        Entity entity = { entityID , scene }; //This is the way to find the particular entity for a particular scene
        //TH_CORE_ASSERT(entity);

        auto& rb2d = entity.GetComponent<RigidBody>();
        rb2d.SetPositionX(posX);
        rb2d.SetPositionY(posY);

    }

    static bool Input_IsKeyDown(int keycode)
    {
        return Input::IsKeyPressed(keycode);
    }

    static void LoadScene(MonoString* text)
    {
        char* cStr = mono_string_to_utf8(text);
        std::string str(cStr);
        mono_free(cStr);

        Scene* scene = ScriptEngine::GetSceneContext();
        SceneSerializer serializer(scene);
        serializer.Deserialize(str);

        ScriptEngine::OnRuntimeStart(scene);
    }

    static void SaveScene(MonoString* text)
    {
        char* cStr = mono_string_to_utf8(text);
        std::string str(cStr);
        mono_free(cStr);

        Scene* scene = ScriptEngine::GetSceneContext();
        SceneSerializer serializer(scene);
        serializer.Deserialize(str);

    }

    static bool Input_MouseButtonPressed(int button)
    {
        return Input::IsMouseButtonPressed(button);
    }

    static float Input_GetMouseX()
    {
        return Input::GetMouseX();
    }


    static float Input_GetMouseY()
    {
        return Input::GetMouseY();
    }

    static bool CreateEntityCSharp(MonoString* name, MonoReflectionType* componentType)
    {
        char* cStr = mono_string_to_utf8(name);
        std::string str(cStr);
        mono_free(cStr);

        Scene* scene = ScriptEngine::GetSceneContext();
        Entity entity = scene->CreateEntity(str);

        
        MonoType* managedType = mono_reflection_type_get_type(componentType);
        //TH_CORE_ASSERT(s_EntityHasComponentFuncs.find(managedType) != s_EntityHasComponentFuncs.end());
        return s_EntityAddComponentFuncs.at(managedType)(entity);
    }

    static int Audio_PlaySound(MonoString* path)
    {
        char* cStr = mono_string_to_utf8(path);
        std::string str(cStr);
        mono_free(cStr);

        return CAudioEngine::PlaySound(str);
    }

    static void Audio_PauseSound(int channel)
    {
        return CAudioEngine::PauseChannel(channel);
    }

    static bool Audio_IsPlaying(int channel)
    {
        return CAudioEngine::IsPlaying(channel);
    }



    

    template <typename Component>
    static void RegisterComponent()
    {
        std::string_view typeName = typeid(Component).name();
        size_t pos = typeName.find_last_of(':');
        std::string_view structName = typeName.substr(pos + 1);
        std::string managedTypename = fmt::format("Thomas.{}", structName);
        std::cout << managedTypename;

        MonoType* managedType = mono_reflection_type_from_name(managedTypename.data(), ScriptEngine::GetCoreAssemblyImage());
        if (!managedType)
        {
            TH_CORE_ERROR("Could not find component type {}", managedTypename);
            return;
        }

        s_EntityHasComponentFuncs[managedType] = [](Entity entity) {return entity.HasComponent<Component>(); };
        s_EntityAddComponentFuncs[managedType] = [](Entity entity) {return entity.AddComponent<Component>(); };

    }
     
    void ScriptGlue::RegisterComponents()
    {
        //RegisterComponent(AllComponents{});
        RegisterComponent<TagComponent>();
        RegisterComponent<Transform>();
        RegisterComponent<Shader_manager>();
        RegisterComponent<Mesh>();
        RegisterComponent<Texture>();
        RegisterComponent<Box_collider>();
        RegisterComponent<RigidBody>();
        RegisterComponent<BoxCollider2D>();
        RegisterComponent<AudioComponent>();
        RegisterComponent<BulletComponent>();
        RegisterComponent<ScriptComponent>();
        RegisterComponent<ParticleComponent>();
        RegisterComponent<Particle>();
        RegisterComponent<ObjectType>();
        RegisterComponent<CombatComponent>();
        RegisterComponent<AStarPathfindingAgent>();
        RegisterComponent<Grid>();
        RegisterComponent<AStarPathfindingObstacle>();
        RegisterComponent<Target>();
    }

    void ScriptGlue::RegisterFunctions()
	{
        TH_ADD_INTERNAL_CALL(NativeLog);
        TH_ADD_INTERNAL_CALL(NativeLog_Vector);
        TH_ADD_INTERNAL_CALL(NativeLog_VectorDot);
        
        TH_ADD_INTERNAL_CALL(Entity_HasComponent);
        TH_ADD_INTERNAL_CALL(Transform_GetTranslation);
        TH_ADD_INTERNAL_CALL(Transform_SetTranslation);

        TH_ADD_INTERNAL_CALL(RigidBody_ChangePosition);

        TH_ADD_INTERNAL_CALL(Input_IsKeyDown);
        TH_ADD_INTERNAL_CALL(Input_MouseButtonPressed);
        TH_ADD_INTERNAL_CALL(Input_GetMouseX);
        TH_ADD_INTERNAL_CALL(Input_GetMouseY);

        TH_ADD_INTERNAL_CALL(LoadScene);
        TH_ADD_INTERNAL_CALL(SaveScene);

        TH_ADD_INTERNAL_CALL(Audio_PlaySound);
        TH_ADD_INTERNAL_CALL(Audio_IsPlaying);
        TH_ADD_INTERNAL_CALL(Audio_PauseSound);

	}   


}
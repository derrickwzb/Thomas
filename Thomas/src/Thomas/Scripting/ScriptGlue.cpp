#include "thpch.h"
#include "ScriptGlue.h"
#include "Thomas/Scene/Entity.h"
#include "Thomas/Scene/Scene.h"
#include  "Thomas/Scripting/ScriptEngine.h"
#include "Thomas/Core/KeyCodes.h"
#include "Thomas/Core/Input.h"
#include "Thomas/Scene/Components.h"

#include "mono/metadata/object.h"
#include "mono/metadata/reflection.h"
#include "glm/glm.hpp"

namespace Thomas {

    static std::unordered_map<MonoType*, std::function<bool(Entity)>> s_EntityHasComponentFuncs;


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

    static void Entity_GetTranslation(EntityID entityID, glm::vec2* outTranslation)
    { 
        Scene* scene = ScriptEngine::GetSceneContext();
        Entity entity = { entityID , scene }; //This is the way to find the particular entity for a particular scene
        *outTranslation = entity.GetComponent<Transform>().translation;  
    }

    static void Entity_SetTranslation(EntityID entityID, glm::vec3* translation)
    {
        Scene* scene = ScriptEngine::GetSceneContext();
        Entity entity = { entityID , scene }; //This is the way to find the particular entity for a particular scene
        entity.GetComponent<Transform>().translation = *translation;
    }

    static bool Input_IsKeyDown(int keycode)
    {
        return Input::IsKeyPressed(keycode);
    }

    template <typename Component>
    static void RegisterComponent()
    {
        //([]()
        //{

            std::string_view typeName = typeid(Component).name();
            size_t pos = typeName.find_last_of(':');
            std::string_view structName = typeName.substr(pos + 1);
            std::string managedTypename = fmt::format("Thomas.{}", structName);
            std::cout << managedTypename;

            MonoType* managedType = mono_reflection_type_from_name(managedTypename.data(), ScriptEngine::GetCoreAssemblyImage());
            s_EntityHasComponentFuncs[managedType] = [](Entity entity) {return entity.HasComponent<Transform>(); };

        //}(), ...);
     
    }
    /*
    template <typename ... Component>
    static void RegisterComponent(ComponentGroup<Component ...>)
    {
        RegisterComponent <Component ...> ();
    }*/
     
    void ScriptGlue::RegisterComponents()
    {
        //RegisterComponent(AllComponents{});
        RegisterComponent<Transform>();
    }

    void ScriptGlue::RegisterFunctions()
	{
        TH_ADD_INTERNAL_CALL(NativeLog);
        TH_ADD_INTERNAL_CALL(NativeLog_Vector);
        TH_ADD_INTERNAL_CALL(NativeLog_VectorDot);
        
        TH_ADD_INTERNAL_CALL(Entity_HasComponent);
        TH_ADD_INTERNAL_CALL(Entity_GetTranslation);
        TH_ADD_INTERNAL_CALL(Entity_SetTranslation);

        TH_ADD_INTERNAL_CALL(Input_IsKeyDown);
	}


}
#include "thpch.h"
#include "ScriptGlue.h"
#include "mono/metadata/object.h"
#include "glm/glm.hpp"

namespace Thomas {

#define TH_ADD_INTERNAL_CALL(Name) mono_add_internal_call("Hazel.InternalCalls::" #Name, Name)

    //Takes in a monostring for type purposes
    static void NativeLog(MonoString* string, int parameter)
    {
        char* cStr = mono_string_to_utf8(string);
        std::string str(cStr);
        mono_free(cStr);
        std::cout << str << ", " << parameter << std::endl;
    }

    //Test case for scripting a struct
    static void NativeLog_Vector(glm::vec3* parameter, glm::vec3* outResult)
    {
        std::cout << (parameter->x) << std::endl;
        std::cout << (parameter->y) << std::endl;
        std::cout << (parameter->z) << std::endl;

        *outResult = glm::normalize(*parameter);
    }

    //Test case for scripting to return a value
    static float NativeLog_VectorDot(glm::vec3* parameter)
    {
        std::cout << (parameter->x) << std::endl;
        std::cout << (parameter->y) << std::endl;
        std::cout << (parameter->z) << std::endl;

        return glm::dot(*parameter, *parameter);
    }

	void ScriptGlue::RegisterFunctions()
	{
		//Using C# to make the internal calls to the funtions 
        TH_ADD_INTERNAL_CALL(NativeLog);
        TH_ADD_INTERNAL_CALL(NativeLog_Vector);
        TH_ADD_INTERNAL_CALL(NativeLog_VectorDot);

	}

}
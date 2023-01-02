#include "thpch.h"
#include "ScriptGlue.h"

#include "mono/metadata/object.h"
#include "glm/glm.hpp"

namespace Thomas {

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


	void ScriptGlue::RegisterFunctions() 
	{
        TH_ADD_INTERNAL_CALL(NativeLog);
        TH_ADD_INTERNAL_CALL(NativeLog_Vector);
        TH_ADD_INTERNAL_CALL(NativeLog_VectorDot);
	}


}
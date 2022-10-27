#pragma once

/*                                                                   includes
----------------------------------------------------------------------------- */
//#include <GL/glew.h> // for access to OpenGL API declarations 
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>

namespace Thomas {
    /*  _________________________________________________________________________ */
    class Shader
        /*! GLSLShader class.
        */
    {
    public:
        //~GLSLShader() { DeleteShaderProgram(); std::cout << "Deleted Shader Program" << std::endl; }
        // default ctor required to initialize GLSLShader object to safe state
        Shader() : pgm_handle(0), is_linked(0) { /* empty by design */ }

        // This function not only compiles individual shader sources but links
        // multiple shader objects to create an exectuable shader program.
        // For each shader source, the function requires the full path to the file 
        // (containing shader source) and the type of shader program (vertex,
        // fragment, geometry, a tessellation type). This information is combined
        // as an std::pair object and the multiple pairs are supplied in a
        // std::vector object.
        // For each shader file, the function implements the six steps described in T
        // CompileShaderFromFile(). After the shader objects are created, a call to
        // Link() will create a shader executable program. This is followed by a call
        // to Validate() ensuring the program can execute in the current OpenGL state.
        unsigned char CompileLinkValidate(std::vector<std::pair<unsigned int, std::string>>);

        // This function does the following:
        // 1) Create a shader program object if one doesn't exist
        // 2) Using first parameter, create a shader object
        // 3) Load shader source code from file specified by second parameter to
        //    shader object
        // 4) Compile shader source by calling CompileShaderFromString
        // 5) Check compilation status and log any messages to data member 
        //    "log_string"
        // 6) If compilation is successful, attach this shader object to previously
        //    created shader program  object
        unsigned char CompileShaderFromFile(unsigned int shader_type, std::string const& file_name);

        // This function does the following:
        // 1) Create a shader program object if one doesn't exist
        // 2) Using first parameter, create a shader object
        // 3) Load the shader code from 2nd parameter to shader object
        // 4) Compile the shader source
        // 5) Check compilation status and log any messages to data member "log_string"
        // 6) If compilation is successful, attach this shader object to previously
        //    created shader program object ...
        unsigned char CompileShaderFromString(unsigned int shader_type, std::string const& shader_src);

        // Link shader objects attached to handle pgm_handle. This member function
        // will also verify the status of the link operation (successful or not?).
        // If the shader objects did not link into a program object, then the
        // member function must retrieve and write the program object's information
        // log to data member log_string. 
        unsigned char Link();

        // Install the shader program object whose handle is encapsulated
        // by member pgm_handle
        void Use();

        // De-install previously installed shader program object using Use().
        // More correctly, after the execution of this member function, the
        // current rendering state is referring to an invalid program object.
        void UnUse();

        // check whether the executable shader program object can execute given the
        // current OpenGL state ...
        // See the glValidateProgram() reference page for more information
        // The function returns true if validatation succeeded 
        unsigned char Validate();

        // return the handle to the shader program object
        unsigned int GetHandle() const;

        // have the different object code linked into a shader program?
        unsigned char IsLinked() const;

        // return logged information from the GLSL compiler and linker and
        // validation information obtained after calling Validate() ...
        std::string GetLog() const;

        // Use an OpenGL API function to dynamically associate a generic vertex 
        // attribute index with a named in attribute variable.
        // Note that labs and assignment sample code did not use the OpenGL API to
        // provide a connection between an input value to a shader and the slot in
        // which these values are fetched from buffer object to shaders. Instead, 
        // the layout qualifier was used in our vertex shaders to statically
        // provide indices to attribute values 
        // But, if users decide to forego the use of the layout qualifier, they'll
        // instead use this function to provide the association between a generic
        // vertex attribute index with a named attribute variable.
        void BindAttribLocation(unsigned int index, char const* name);

        // Use an OpenGL API function to dynamically associate a fragment shader 
        // index location that a user-defined out variable will write to.
        // As with vertex shaders, we did not use the OpenGL API to provide this
        // association in sample code. Instead, we statically assigned a location
        // for an out variable using the layout qualifier. However, this function
        // will be called by users if they forego the use of the layour qualifier.
        void BindFragDataLocation(unsigned int color_number, char const* name);

        // as the name implies, this function deletes a program object
        void DeleteShaderProgram();

        // OpenGL is C-based API and therefore doesn't understand function
        // overloading or templates
        // Therefore, we need a family of functions to specify values of uniform
        // variables of different types for the current program object
        void SetUniform(char const* name, unsigned char val);
        void SetUniform(char const* name, int val);
        void SetUniform(char const* name, float val);
        void SetUniform(char const* name, float x, float y);
        void SetUniform(char const* name, float x, float y, float z);
        void SetUniform(char const* name, float x, float y, float z, float w);
        void SetUniform(char const* name, glm::vec2 const& val);
        void SetUniform(char const* name, glm::vec3 const& val);
        void SetUniform(char const* name, glm::vec4 const& val);
        void SetUniform(char const* name, glm::mat3 const& val);
        void SetUniform(char const* name, glm::mat4 const& val);

        // display the list of active vertex attributes used by vertex shader
        void PrintActiveAttribs() const;

        // display the list of active uniform variables
        void PrintActiveUniforms() const;

    private:
        //enum ShaderType {
        //    VERTEX_SHADER = GL_VERTEX_SHADER,
        //    FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
        //    GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
        //    TESS_CONTROL_SHADER = GL_TESS_CONTROL_SHADER,
        //    TESS_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER,
        //    // ignore compute shader for now because it is not connected to
        //    // the graphics pipe
        //    // COMPUTE_SHADER = GL_COMPUTE_SHADER
        //};

        unsigned int pgm_handle = 0;  // handle to linked shader program object
        unsigned char is_linked = 0; // has the program successfully linked?
        std::string log_string; // log for OpenGL compiler and linker messages

    private:
        // use OpenGL API to return the location of an uniform variable with
        // name "name" using program handle encapsulated by object of this class type
        int GetUniformLocation(char const* name);

        // return true if file (given in relative path) exists, false otherwise
        unsigned char FileExists(std::string const& file_name);
    };
}

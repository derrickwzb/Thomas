#ifndef GLPBO_H
#define GLPBO_H

/*                                                                   includes
----------------------------------------------------------------------------- */
#include <iostream>
#include <random>
#include <GL/glew.h> // for access to OpenGL API declarations 
#include "Thomas/Renderer/Shader.h" // GLSLShader class definition
#include <imgui.h>
#include "Thomas/Renderer/Mesh_manager.h"
#include "Thomas/Renderer/Shader_manager.h"
#include "Thomas/Renderer/Texture.h"
#include "Thomas/Renderer/Texture_system.h"
#include "Thomas/Renderer/Transform.h"
#include "Thomas/Renderer/Camera.h"
#include "Thomas/Scene/Entity.h"

//temp
static int temp_width;
static int temp_height;

/*  _________________________________________________________________________ */
class Graphics {
public:
    inline static int width{};
    inline static int height{};
    inline static GLdouble xpos;
    inline static GLdouble ypos;
    inline static int obj_clicked{};
    inline static int sel{};					                    // Selected object
    inline static Texture_system		text_sys;      // Texture system, container to store textures
    inline static std::default_random_engine dre;

    // Replace by ECS in the future
    struct temp_Obj {
        Mesh						mesh_stuff;                 // Mesh component

        Shader_manager		shader_stuff;              // Shader component

        Texture					text_stuff;                   // Texture component

        Transform               trans_stuff;                 // Transform component

        Camera                   cam_stuff;

        // Collision
        int                   reset_but{};
        int                   collision_detected{};
        glm::vec2			min{};
        glm::vec2			max{};
        void minmax();

        int bounding_on{};

        // Draw functions
        void draw();
        void draw_collider();
    };

    struct Color {
        float r{};
        float g{};
        float b{};
    };

    // Multiple model
    //static std::vector<temp_Obj> mdl_obj;
    //static std::vector<temp_Obj> collider_obj;

    // Member Functions
    static void init();
    static void update(std::vector<unsigned int> allentity);
    static void draw(std::vector<unsigned int> allentity);
    static void cleanup();
   // static void Add_Obj();
   // static void temp_physics();
    static bool simple_collision(glm::vec2 minA, glm::vec2 maxA, glm::vec2 minB, glm::vec2 maxB);
};










#endif /* GLPBO_H */
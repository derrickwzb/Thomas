#pragma once
/*!*************************************************************************
\file:								Graphics.h
\author:						Xie Zhi Xiong
\par DP email:			xiong.x@digipen.edu
\par Course:				CSD2125
\par Programming:	CSD2400 Game project
\date:							31/10/2022
\brief:
    This file contains the declaration for Graphics class.
****************************************************************************/
/*                                                                   includes
----------------------------------------------------------------------------- */
#include <iostream>
#include <random>
#include "Thomas/Renderer/Mesh_manager.h"
#include "Thomas/Renderer/Camera.h"
#include "Thomas/Renderer/Fonts.h"
#include "Thomas/Renderer/Texture.h"
#include "Thomas/Renderer/Box_collider.h"

namespace Thomas {
    class Graphics {
    public:

        // Data Members 
        inline static glm::vec2        m_ViewportSize = { 0.f,0.f };
        inline static int                   width{};
        inline static int                   height{};
        inline static double            xpos;
        inline static double            ypos;
        inline static int                   fps_timer;
        inline static bool                obj_clicked{};
        inline static int                   obj_counter{};
        inline static int                   sel{};					        
        inline static float                sel_layer{};
        inline static Camera           cam_stuff;   // Global Camera
        inline static std::default_random_engine dre;

        struct Color {
            float r{};
            float g{};
            float b{};
        };

        inline static double Graphic_update_timetaken  = 0;
        inline static double Graphic_draw_timetaken     = 0;

        // Member Functions
        static void init();

        // Draw Color
        static void draw(Shader_manager shdr, Mesh mesh, Transform trans);
        // Draw (Texture & Color) || Texture
        static void draw(Shader_manager shdr, Mesh mesh, Transform trans, Texture text);
        // Draw Box Renderer
        static void draw_box(Box_collider box_renderer, glm::vec3 on_color = glm::vec3(1.f, 0.f, 0.f), glm::vec3 off_color = glm::vec3(0.f, 1.f, 0.f));

        static void cleanup();
    };
}





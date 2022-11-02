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
#include "Thomas/Renderer/Texture_system.h"
#include "Thomas/Renderer/Camera.h"
#include "Thomas/Renderer/Fonts.h"
#include "Thomas/Renderer/Framebuffer.h"
#include <sstream>

namespace Thomas {
    class Graphics {
    public:

        // Data Members 
        inline static int width{};
        inline static int height{};
        inline static double xpos;
        inline static double ypos;
        inline static int fps_timer;
  /*      inline static std::stringstream text;*/
        inline static int obj_clicked{};
        inline static int sel{};					                    // Selected object
        inline static Fonts                       font_stuff;
        inline static Camera                   cam_stuff;
        inline static std::default_random_engine dre;

        struct Color {
            float r{};
            float g{};
            float b{};
        };

        inline static double Graphic_update_timetaken = 0;
        inline static double Graphic_draw_timetaken = 0;

        // Member Functions
        static void init();
        static void update(std::vector<unsigned int> allentity);
        static void draw(std::vector<unsigned int> allentity);
        static void cleanup();
    };
}





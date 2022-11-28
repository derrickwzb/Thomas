/*!*************************************************************************
\file           CanvasApp.cpp
\author         Chen XinPeng
\par DP email:  c.xinpeng@digipen.edu
\par Programming CSD2400 Game project
\date           28/11/2022
\brief			This file is the main entry point for game demo

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************/
#pragma warning(suppress : 4996)
#include <Thomas.h>

#include "Thomas/Core/EntryPoint.h"
#include "Canvas2D.h"

#include "imgui/imgui.h"

class Canvas : public Thomas::Application
{
public:
	Canvas()
	{
		PushLayer(new Canvas2D());
	
	}
	~Canvas()
	{

	}
};

Thomas::Application* Thomas::CreateApplication()
{
	return new Canvas();
}

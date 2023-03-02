/******************************************************************************/
/*!
\file		EntryPoint.h
\author 	Derrick Woo
\par    	email: d.woo@digipen.edu
\date   	25/9/2022
\brief		This file is the main entry point of the whole game engine.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma warning(suppress : 4996)
#pragma warning( suppress : 4172 )
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#ifdef TH_PLATFORM_WINDOWS

extern Thomas::Application* Thomas::CreateApplication();

int main(int argc,char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Thomas::Log::Init();
	TH_CORE_INFO("THOMAS ENGINE");

	auto app = Thomas::CreateApplication();
	app->run();
	delete app;
	Thomas::Log::Shutdown();
}


#endif
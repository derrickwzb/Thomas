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

#ifdef TH_PLATFORM_WINDOWS

extern Thomas::Application* Thomas::CreateApplication();

int main(int argc,char** argv)
{
	Thomas::Log::Init();
	TH_CORE_INFO("THOMAS ENGINE");
	/*TH_CORE_INFO("TEST LOG");
	printf("Thomas Engine\n");*/


	auto app = Thomas::CreateApplication();
	app->run();
	delete app;
}


#endif
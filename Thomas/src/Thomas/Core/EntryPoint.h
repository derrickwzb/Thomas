#pragma once

#ifdef TH_PLATFORM_WINDOWS

extern Thomas::Application* Thomas::CreateApplication();

int main(int argc,char** argv)
{
	Thomas::Log::Init();
	TH_CORE_WARN("THOMAS ENGINE");
	TH_CORE_INFO("TEST LOG");
	printf("Thomas Engine\n");


	auto app = Thomas::CreateApplication();
	app->run();
	delete app;
}


#endif
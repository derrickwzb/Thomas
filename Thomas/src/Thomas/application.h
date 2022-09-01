#pragma once

#include"Core.h"

namespace Thomas {
	class THOMAS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};

	//to be defined in client
	Thomas::Application* CreateApplication();
}

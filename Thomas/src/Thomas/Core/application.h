#pragma once

#include"Core.h"
#include "Thomas/Core/LayerStack.h"
#include "Thomas/Events/Event.h" 
#include "Thomas/Events/ApplicationEvent.h"
#include "Window.h"

namespace Thomas {
	class THOMAS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void OnEvent(Event& e);


		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		
	private:

		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	//to be defined in client
	Application* CreateApplication();
}

#pragma once

#include"Core.h"
#include "Thomas/Core/LayerStack.h"
#include "Thomas/Events/Event.h" 
#include "Thomas/Events/ApplicationEvent.h"
#include "Window.h"
#include "Timestep.h"

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

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
		
	private:

		bool OnWindowClosed(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	//to be defined in client
	Application* CreateApplication();
}

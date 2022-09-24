#pragma once

#include"Core.h"
#include "Window.h"
#include "Thomas/Core/LayerStack.h"
#include "Thomas/Events/Event.h" 
#include "Thomas/Events/ApplicationEvent.h"

#include "Thomas/ImGui/ImGuiLayer.h"

#include "Thomas/Renderer/Shader.h"

#include "Thomas/Renderer/Buffer.h"

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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr <VertexBuffer> m_VertexBuffer;
		std::unique_ptr <IndexBuffer> m_IndexBuffer;

	private:
		static Application* s_Instance;
	};

	//to be defined in client
	Application* CreateApplication();
}

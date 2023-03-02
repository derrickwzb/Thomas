/******************************************************************************/
/*!
\file		application.h
\author 	Derrick Woo
\par    	email: d.woo@digipen.edu
\date   	25/9/2022
\brief		This file represents the interface of the source file
			application.cpp, it contains the function prototype declarations
			and class definition. 

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

#include"Core.h"
#include "Window.h"
#include "Thomas/Core/LayerStack.h"
#include "Thomas/Events/Event.h" 
#include "Thomas/Events/ApplicationEvent.h"
#include "Thomas/Scripting/ScriptEngine.h"

#include "Thomas/ImGui/ImGuiLayer.h"
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

		void Close();

		void SetFullscreen();
		void SetWindowed();
		void SetWindowTitle(const std::string& title);

		inline static Application& Get() { return *s_Instance; }

		ImGuiLayer* GetImguiLayer() { return m_ImGuiLayer; }

		inline static std::vector<unsigned int> entities;
		inline static float fps;
		inline static Timestep timestep;		// for delta time;
	private:

		bool OnWindowClosed(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		unsigned int m_VertexArray;

		

	private:
		static Application* s_Instance;
	};

	//to be defined in client
	Application* CreateApplication();
}

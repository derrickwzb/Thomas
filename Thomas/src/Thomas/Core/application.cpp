/******************************************************************************/
/*!
\file		application.cpp
\author 	Derrick Woo
\par    	email: d.woo@digipen.edu
\date   	25/9/2022
\brief		This file represents the implementation of Application class 
			that are specified in the interface file application.h

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "thpch.h"
#include "application.h"
#include <map>
#include "Thomas/Events/ApplicationEvent.h"
#include "Log.h"

#include "Thomas/Renderer/Graphics.h"
#include "Thomas/Scene/Entity.h"
#include "Input.h"
//#include "Thomas/Scene/test.h"
#include "Thomas/Logic/Logic.h"

#include "Thomas/Physics/physicsSystem.h"
#include "Thomas/Audio/AudioEngine.h"
#include "Thomas/Audio/AudioSystem.h"

#include <GLFW/glfw3.h>

namespace Thomas {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	

	/**************************************************************************/
		/*!
			This is the default constructor of the Application class.
		*/
	/**************************************************************************/
	Application::Application()
	{
		TH_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		stash.Load_Texture();
		stash.Load_Font();
		stash.Load_Shader();
		stash.Load_Audio();

		Graphics::init();

		ecs_init();

		entities = factory.BuildAndSerialize("../Assets/Objects/test1.json");

		logic.Init();
		
		//For Audio
		//std::cout << "hi im here";
	
		AudioSystem aSystem;
		aSystem.Init();

		//for (auto const v : entities) {
		//	if (factory.HasComponent<BoxCollider2D>(v)) {
		//		auto test = factory.GetComponent<BoxCollider2D>(0);
		//		Vec2 temp_vertices;
		//		temp_vertices = { 2, 4 };
		//		test.vertices.push_back(temp_vertices);
		//		temp_vertices = { 3, 2 };
		//		test.vertices.push_back(temp_vertices);
		//		temp_vertices = { 3, 5 };
		//		test.vertices.push_back(temp_vertices);
		//		temp_vertices = { 5, 5 };
		//		test.vertices.push_back(temp_vertices);
		//		std::cout << test.vertices.size() << std::endl;
		//		factory.UpdateComponent<BoxCollider2D>(v,test);
		//		//for (int i = 0; i < 4; ++i) {
		//		//	std::cout << test.vertices[i].x << " " << test.vertices[i].y << std::endl;
		//		//}
		//	}
		//}

		//Print_physics(entities);
		//Print_physics(entities);
	}
	/**************************************************************************/
		/*!
			This is the default destructor of the Application class.
		*/
	/**************************************************************************/
	Application::~Application()
	{

	}
	/**************************************************************************/
		/*!
			This is the definition of Push Layer member function.
		*/
	/**************************************************************************/
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	/**************************************************************************/
		/*!
			This is the definition of PushOverlay member function.
		*/
	/**************************************************************************/
	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
	/**************************************************************************/
		/*!
			This is the definition of OnWindowClosed member function.
		*/
	/**************************************************************************/
	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		/*Graphics::OnWindowResize(e.GetWidth(), e.GetHeight());*/

		return false;
	}

	void Application::Close()
	{
		m_Running = false;
	}
	/**************************************************************************/
		/*!
			This is the definition of OnEvent member function.
		*/
	/**************************************************************************/
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		//iterate though layer stack from the end 
		//if an overlay handles an event it will not go forward to the layers
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			
			if (e.Handled)
			{
				break;
			}
			(*--it)->OnEvent(e);
		}
	}
	/**************************************************************************/
			/*!
				This is the definition of run member function.
			*/
	/**************************************************************************/
	void Application::run()
	{
		//Audio
		aSystem.Update(entities);
	
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			timestep = time - m_LastFrameTime; //difference between current frame and last frame
			m_LastFrameTime = time;
			fps = 1 / timestep;
			
				
			//UpdatePhysic(Graphics::sel, time);
			logic.Update(entities, timestep);
		
			

			//Audio
			aSystem.TempSfxInput(entities);


			for (Layer* layer : m_LayerStack)
			{
				//running update with fps
				layer->OnUpdate(timestep);
			}
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
				
			}		
			m_ImGuiLayer->End();

			m_Window->OnUpdate();

			//cout the fps
			/*std::cout << "Fps: " << fps << '\n';*/
		}

		factory.SaveToFile(entities, "../Assets/Objects/test1.json");
	}

	
}

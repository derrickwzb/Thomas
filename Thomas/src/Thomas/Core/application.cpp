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
#include "Thomas/Logic/Logic.h"

#include "Thomas/Physics/physicsSystem.h"
#include "Thomas/Audio/AudioEngine.h"

#include "Thomas/Core/Input.h"

#include <GLFW/glfw3.h>

const double fixedDeltaTime = 1.0f / 60.0f;//user defined
double accumulatedTime = 0.0;//one time definition
int currentNumberOfSteps = 0;

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

		ScriptEngine::Init();

		//ecs_init();
		
		//logic.Init();
	
		////AudioSystem aSystem;
		//aSystem.Init();
		AEngine.Init();
		m_Window->SetWindowed();
	}
	/**************************************************************************/
		/*!
			This is the default destructor of the Application class.
		*/
	/**************************************************************************/
	Application::~Application()
	{
		ScriptEngine::Shutdown();
		//_CrtDumpMemoryLeaks();
		AEngine.Shutdown();
		Input::Delete_Input();
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

	void Application::SetFullscreen()
	{
		m_Window->SetFullscreen();
	}

	void Application::SetWindowed()
	{
		m_Window->SetWindowed();
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
		//aSystem.Update(entities);
	
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			timestep = time - m_LastFrameTime; //difference between current frame and last frame
			m_LastFrameTime = time;

			currentNumberOfSteps = 0;//reset
			accumulatedTime += timestep;
			while (accumulatedTime >= fixedDeltaTime)
			{
				accumulatedTime -= fixedDeltaTime;//this will save the exact accumulated time differences, among all game loops
				currentNumberOfSteps++;
			}

			if (currentNumberOfSteps > 3) {
				currentNumberOfSteps = 3;
			}

			fps = static_cast<float>(currentNumberOfSteps * 60.f);
			//UpdatePhysic(Graphics::sel, time);
			//logic.Update(entities, timestep);
			//Audio
			//aSystem.TempSfxInput(entities);

			for (Layer* layer : m_LayerStack)
			{
				for (int i = 0; i < currentNumberOfSteps; ++i)
				{
				layer->OnUpdate(fixedDeltaTime);
				}

				//running update with fps
				//layer->OnUpdate(timestep);
			}
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
				
			}		
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}
}

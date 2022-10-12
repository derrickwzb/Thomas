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

#include "Thomas/Events/ApplicationEvent.h"
#include "Log.h"

#include "Thomas/Renderer/Graphics.h"
#include "Thomas/Scene/Entity.h"
#include "Input.h"

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
		
		Graphics::init();


		GameObjectFactory factory;
		Signature signature;
		std::vector<Entity> entities;

		factory.Init();
		factory.RegisterComponent<Position>();
		factory.RegisterComponent<Colour>();
		factory.RegisterComponent<Triangle>();
		factory.RegisterComponent<Rigidbody2DComponent>();
		factory.RegisterComponent<Bounds>();

		signature.set(factory.GetComponentType<Position>());
		signature.set(factory.GetComponentType<Colour>());
		signature.set(factory.GetComponentType<Triangle>());
		signature.set(factory.GetComponentType<Rigidbody2DComponent>());
		signature.set(factory.GetComponentType<Bounds>());

		std::cout << std::endl << "/---------------------------------------/" << std::endl;
		std::cout << "reading data from file and create entity\n";
		Entity object0 = factory.BuildAndSerialize("../Assets/Objects/Object0.txt");
		Entity object1 = factory.BuildAndSerialize("../Assets/Objects/Object1.txt");
		Entity object2 = factory.BuildAndSerialize("../Assets/Objects/Object2.txt");

		entities.push_back(object0);
		entities.push_back(object1);
		entities.push_back(object2);
		factory.Print(entities);

		////---------------------// 

		std::cout << std::endl << "/---------------------------------------/" << std::endl;
		std::cout << "Update values for entity 1\n";

		Position newpoint;
		newpoint.x = 100.f;
		newpoint.y = 100.f;

		factory.ChangeComponent<Position>(object1, newpoint);

		Colour newcolour;
		newcolour.r = 1.f;
		newcolour.g = 1.f;
		newcolour.b = 1.f;
		newcolour.a = 1.f;

		factory.ChangeComponent<Colour>(object1, newcolour);

		factory.Print(entities);
		////-----------------------------/ 

		std::cout << std::endl << "/---------------------------------------/" << std::endl;
		std::cout << "clone entity 3 from entity 1\n";
		Entity object3 = factory.Clone(object1);
		entities.push_back(object3);
		factory.Print(entities);

		////-----------------------------/ 

		std::cout << std::endl << "/---------------------------------------/" << std::endl;
		std::cout << "Remove entity 0\n";
		factory.Destroy(object0);
		factory.Print(entities);
		std::cout << std::endl;

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
	/**************************************************************************/
		/*!
			This is the definition of OnEvent member function.
		*/
	/**************************************************************************/
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));

		//TH_CORE_TRACE("{0}", e);


		//iterate though layer stack from the end 
		//if an overlay handles an event it will not go forward to the layers
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
			{
				break;
			}
		}
	}
	/**************************************************************************/
			/*!
				This is the definition of run member function.
			*/
	/**************************************************************************/
	void Application::run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
				
			}
			Graphics::update();
			Graphics::draw();
			m_ImGuiLayer->End();
			
			
			/*glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);*/

			//m_Shader->Bind();
			//glBindVertexArray(m_VertexArray);
			//glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			//iterate through all the layers in layerstack , ranged based for loop as begin and end is already implemented
			for (Layer* layer : m_LayerStack)
			{
				//running update with fps
				layer->OnUpdate(timestep);
			}

			m_Window->OnUpdate();
		}
	}

	
}

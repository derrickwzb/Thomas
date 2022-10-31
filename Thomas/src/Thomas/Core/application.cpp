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


	std::vector<Entity> entities;

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
		Graphics::init();
		//Signature signature;

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

		Print_physics(entities);
		//physicsSystem.Update(entities);
		Print_physics(entities);
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
		//Audio
		//aSystem.Update(entities);
	
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			timestep = time - m_LastFrameTime; //difference between current frame and last frame
			m_LastFrameTime = time;

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
				
			}
			
			physicsSystem.Input(Graphics::sel, timestep);

			physicsSystem.Update(entities, timestep);
				
			//UpdatePhysic(Graphics::sel, time);
			logic.Update(entities, timestep);
			Graphics::update(entities);
			Graphics::draw(entities);
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

		factory.SaveToFile(entities, "../Assets/Objects/test1.json");
	}

	
}

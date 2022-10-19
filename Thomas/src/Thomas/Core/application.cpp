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
#include "Thomas/Scene/Entity.h"

#include "Thomas/Physics/physicsSystem.h"

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
		
		Graphics::init();


		Signature signature;
		

		factory.Init();
		factory.RegisterComponent<Mesh>();
		factory.RegisterComponent<Shader_manager>();
		factory.RegisterComponent<Texture>();
		factory.RegisterComponent<Transform>();
		factory.RegisterComponent<Camera>();
		factory.RegisterComponent<Box_collider>();

		signature.set(factory.GetComponentType<Mesh>());
		signature.set(factory.GetComponentType<Shader_manager>());
		signature.set(factory.GetComponentType<Texture>());
		signature.set(factory.GetComponentType<Transform>());
		signature.set(factory.GetComponentType<Camera>());
		signature.set(factory.GetComponentType<Box_collider>());

		Entity object0 = factory.CreateEmptyComposition();
		//Entity object1 = factory.CreateEmptyComposition();

		Transform trans;
		trans.scaling = glm::vec2(1.f, 1.f);
		trans.translation = glm::vec2(0, 0);
		trans.compute_mdl_to_ndc_xform();
		factory.AddComponent<Transform>(object0, trans);
		//factory.AddComponent<Transform>(object1, trans);

		Shader_manager shader;
		shader.setup_shdr_pgm();
		factory.AddComponent<Shader_manager>(object0, shader);
		//factory.AddComponent<Shader_manager>(object1, shader);

		Mesh mesh;
		mesh.setup_vao();
		factory.AddComponent<Mesh>(object0, mesh);
		//factory.AddComponent<Mesh>(object1, mesh);

		Texture text;
		factory.AddComponent<Texture>(object0, text);

		Camera cam;
		factory.AddComponent<Camera>(object0, cam);

		Box_collider bb_box;
		bb_box.box_trans.scaling = trans.scaling;
		bb_box.box_trans.rotation = trans.rotation;
		bb_box.box_trans.translation = trans.translation;
		bb_box.box_trans.compute_mdl_to_ndc_xform();
		bb_box.box_shader.setup_shdr_pgm();
		bb_box.box_mesh.setup_vao();
		factory.AddComponent<Box_collider>(object0, bb_box);

		entities.push_back(object0);
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
		Graphics::OnWindowResize(e.GetWidth(), e.GetHeight());

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
	}

	
}

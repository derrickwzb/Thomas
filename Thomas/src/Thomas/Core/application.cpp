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


		//physicsSystem.Init();

		//physicsSystem.Update(entities);

		//Print_physics(entities);

				//Registers the name of the component into the system
		factory.RegisterComponent<RigidBody>();
		factory.RegisterComponent<BoxCollider2D>();

		//Signature of current component
		signature.set(factory.GetComponentType<RigidBody>());
		signature.set(factory.GetComponentType<BoxCollider2D>());

		Entity object = factory.CreateEmptyComposition();
		Entity object2 = factory.CreateEmptyComposition();
		Entity object3 = factory.CreateEmptyComposition();

		RigidBody newrigid;
		newrigid.SetPositionX(1.f);
		newrigid.SetPositionY(1.f);
		newrigid.Velocity.x = 10.f;
		newrigid.Velocity.y = 10.f;

		RigidBody newrigid2;
		newrigid2.SetPositionX(1.f);
		newrigid2.SetPositionY(1.f);
		newrigid2.Velocity.x = 10.f;
		newrigid2.Velocity.y = 10.f;

		BoxCollider2D newCollidor1;
		newCollidor1.bounds.min.x = 10.f;
		newCollidor1.bounds.max.x = 20.f;
		newCollidor1.bounds.min.y = 10.f;
		newCollidor1.bounds.max.y = 20.f;
		Vector2D vel1{ 10, 10 };

		BoxCollider2D newCollidor2;
		newCollidor2.bounds.min.x = 30.f;
		newCollidor2.bounds.max.x = 40.f;
		newCollidor2.bounds.min.y = 30.f;
		newCollidor2.bounds.max.y = 40.f;
		Vector2D vel2{ 20, 20 };

		factory.AddComponent<RigidBody>(object, newrigid);
		factory.AddComponent<BoxCollider2D>(object2, newCollidor1);
		factory.AddComponent<BoxCollider2D>(object3, newCollidor2);
		factory.AddComponent<RigidBody>(object2, newrigid2);
		factory.AddComponent<RigidBody>(object3, newrigid2);

		entities.push_back(object); //pushing back data of the object into the entity
		entities.push_back(object2); //pushing back data of the object into the entity
		entities.push_back(object3);

		Print_physics(entities);

		physicsSystem.Update(entities);

		Print_physics(entities);
		
		//factory.RegisterComponent<Position>();
		//factory.RegisterComponent<Colour>();
		//factory.RegisterComponent<Triangle>();
		//factory.RegisterComponent<Rigidbody2DComponent>();
		//factory.RegisterComponent<Bounds>();

		//signature.set(factory.GetComponentType<Position>());
		//signature.set(factory.GetComponentType<Colour>());
		//signature.set(factory.GetComponentType<Triangle>());
		//signature.set(factory.GetComponentType<Rigidbody2DComponent>());
		//signature.set(factory.GetComponentType<Bounds>());

		//std::cout << std::endl << "/---------------------------------------/" << std::endl;
		//std::cout << "reading data from file and create entity\n";
		//Entity object0 = factory.BuildAndSerialize("../Assets/Objects/Object0.txt");
		//Entity object1 = factory.BuildAndSerialize("../Assets/Objects/Object1.txt");
		//Entity object2 = factory.BuildAndSerialize("../Assets/Objects/Object2.txt");

		//entities.push_back(object0);
		//entities.push_back(object1);
		//entities.push_back(object2);
		//factory.Print(entities);

		//////---------------------// 

		//std::cout << std::endl << "/---------------------------------------/" << std::endl;
		//std::cout << "Update values for entity 1\n";

		//Position newpoint;
		//newpoint.x = 100.f;
		//newpoint.y = 100.f;

		//factory.ChangeComponent<Position>(object1, newpoint);

		//Colour newcolour;
		//newcolour.r = 1.f;
		//newcolour.g = 1.f;
		//newcolour.b = 1.f;
		//newcolour.a = 1.f;

		//factory.ChangeComponent<Colour>(object1, newcolour);

		//factory.Print(entities);
		//////-----------------------------/ 

		//std::cout << std::endl << "/---------------------------------------/" << std::endl;
		//std::cout << "clone entity 3 from entity 1\n";
		//Entity object3 = factory.Clone(object1);
		//entities.push_back(object3);
		//factory.Print(entities);

		//////-----------------------------/ 

		//std::cout << std::endl << "/---------------------------------------/" << std::endl;
		//std::cout << "Remove entity 0\n";
		//factory.Destroy(object0);
		//factory.Print(entities);
		//std::cout << std::endl;

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

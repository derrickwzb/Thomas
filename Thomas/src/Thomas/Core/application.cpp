#include "thpch.h"
#include "application.h"

#include "Thomas/Events/ApplicationEvent.h"
#include "Log.h"

#include "Thomas/Renderer/Render.h"
#include "Thomas/Scene/Entity.h"
#include "Input.h"

#include <GLFW/glfw3.h>

namespace Thomas {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		TH_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		
		Render::init();

		//example triangle 
		//glGenVertexArrays(1, &m_VertexArray);
		//glBindVertexArray(m_VertexArray);

		//
		//float vertices[3 * 3] =
		//{
		//	-0.5f,-0.5f,0.0f,
		//	0.5f,-0.5f,0.0f,
		//	0.0f,0.5f,0.0f,
		//};


		////m_VertexBuffer.reset(VertexBuffer::Create( vertices , sizeof(vertices) ));

		//glEnableVertexAttribArray(0);
		//// index 0 no of float 3 normalize false, no of bytes between vertex, 
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE , 3*sizeof(float) , nullptr );

		//unsigned int indices[3] = { 0,1,2 };

		//m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		/*std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";*/

		//m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
		//vertex array
		//vertex buffer
		//index buffer
		//shader

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
		Entity object0 = factory.BuildAndSerialize("..\\Objects\\Object0.txt");
		Entity object1 = factory.BuildAndSerialize("..\\Objects\\Object1.txt");
		Entity object2 = factory.BuildAndSerialize("..\\Objects\\Object2.txt");

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

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

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
			Render::update();
			Render::draw();
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

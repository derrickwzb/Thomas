#include "thpch.h"
#include "application.h"

#include "Thomas/Events/ApplicationEvent.h"
#include "Log.h"

#include "Thomas/Renderer/Render.h"
#include "Thomas/Scene/Entity.h"
#include "Input.h"

namespace Thomas {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		//call assert when assert.h is made
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

		Entity object = factory.CreateEmptyComposition();
		Entity object2 = factory.CreateEmptyComposition();
		Entity object3 = factory.CreateEmptyComposition();

		Position position;
		position.x = 100.f;
		position.y = 100.f;

		std::cout << "add component \n";
		//add component to entity 
		factory.AddComponent<Position>(object, position);
		factory.AddComponent<Position>(object2, position);
		factory.AddComponent<Position>(object3, position);

		Colour colour;
		colour.r = 1.f;
		colour.g = 0.f;
		colour.b = 1.f;
		colour.a = 1.f;

		factory.AddComponent<Colour>(object, colour);
		factory.AddComponent<Colour>(object2, colour);
		factory.AddComponent<Colour>(object3, colour);

		Triangle triangle;
		triangle.positionx = 100.f;
		triangle.positiony = 100.f;
		triangle.positionz = 100.f;

		factory.AddComponent<Triangle>(object, triangle);
		factory.AddComponent<Triangle>(object2, triangle);

		entities.push_back(object);
		entities.push_back(object2);
		entities.push_back(object3);

		factory.Print(entities);

		//---------------------// 

		std::cout << std::endl;
		std::cout << "Update values\n";

		Position newpoint;
		newpoint.x = 10.f;
		newpoint.y = 10.f;

		factory.ChangeComponent<Position>(object2, newpoint);

		Colour newcolour;
		newcolour.r = 0.f;
		newcolour.g = 0.f;
		newcolour.b = 0.f;
		newcolour.a = 0.f;

		factory.ChangeComponent<Colour>(object2, newcolour);

		factory.Print(entities);
		//-----------------------------/ 

		std::cout << std::endl;
		std::cout << "clone entity\n";
		Entity object4 = factory.Clone(object2);
		entities.push_back(object4);
		factory.Print(entities);

		//-----------------------------/ 

		std::cout << std::endl;
		std::cout << "Remove entity\n";
		factory.Destroy(object);
		factory.Print(entities);


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
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	
}

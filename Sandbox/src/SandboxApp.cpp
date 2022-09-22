#include <Thomas.h>

class ExampleLayer : public Thomas::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{}


	void OnUpdate() override
	{
		TH_INFO("EXAMPLE LAYER : UPDATE");
	}

	void OnEvent(Thomas::Event& event) override
	{
		TH_TRACE("{0}", event);
	}
};

class Sandbox : public Thomas::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Thomas::ImGuiLayer());
	}
	~Sandbox()
	{

	}
};

Thomas::Application* Thomas::CreateApplication()
{
	return new Sandbox();
}
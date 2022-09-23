#include <Thomas.h>

class ExampleLayer : public Thomas::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{}


	void OnUpdate() override
	{
		/*if (Thomas::Input::IsKeyPressed(TH_KEY_TAB))
			TH_INFO("Tab key is pressed");*/
	}

	

	void OnEvent(Thomas::Event& event) override
	{
		/*TH_TRACE("{0}", event);*/
	}
};

class Sandbox : public Thomas::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	
	}
	~Sandbox()
	{

	}
};

Thomas::Application* Thomas::CreateApplication()
{
	return new Sandbox();
}
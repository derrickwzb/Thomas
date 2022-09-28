#include <Thomas.h>

#include "imgui/imgui.h"

class ExampleLayer : public Thomas::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{}


	void OnUpdate() override
	{
		//TH_INFO("EXAMPLE LAYER : UPDATE");
		//TH_TRACE("Delta tiem: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());
		/*if (Thomas::Input::IsKeyPressed(TH_KEY_TAB))
			TH_INFO("Tab key is pressed");*/
	}

	virtual void OnImGuiRender() override
	{
		/*ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();*/
	}
	

	void OnEvent(Thomas::Event& event) override
	{
		//TH_INFO("{0}", event);
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
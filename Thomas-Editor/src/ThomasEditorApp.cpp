#pragma warning(suppress : 4996)
#include <Thomas.h>
#include "Thomas/Core/EntryPoint.h"

#include "EditorLayer.h"


#include "imgui/imgui.h"

//class ExampleLayer : public Thomas::Layer
//{
//public:
//	ExampleLayer()
//		:Layer("Example")
//	{}
//
//
//	void OnUpdate(Thomas::Timestep ts) override
//	{
//		TH_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());
//		/*if (Thomas::Input::IsKeyPressed(TH_KEY_TAB))
//			TH_INFO("Tab key is pressed");*/
//	}
//
//	virtual void OnImGuiRender() override
//	{
//		/*ImGui::Begin("Test");
//		ImGui::Text("Hello World");
//		ImGui::End();*/
//	}
//	
//
//	void OnEvent(Thomas::Event& event) override
//	{
//		//TH_INFO("{0}", event);
//	}
//};
namespace Thomas
{


	class HazelEditor : public Application
	{
	public:
		HazelEditor()
		{
			PushLayer(new EditorLayer());

		}
		~HazelEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new HazelEditor();
	}
}
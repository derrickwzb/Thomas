#include "thpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


#include "Thomas/Core/application.h"
#include "Thomas/Renderer/Render.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"


void buttons() {
	if (ImGui::Button("Square")) {
		if (Render::obj_shape != 0)
		{
			Render::obj_shape = 0;
			std::cout << "here" << std::endl;
		}
		
		Render::Add_Obj();
	}
	ImGui::SameLine();
	if (ImGui::Button("Cirlce")) {
		if (Render::obj_shape != 1)
			Render::obj_shape = 1;
		Render::Add_Obj();
	}
	ImGui::SameLine();
	if (ImGui::Button("BB")) {
		if (Render::mdl_obj[Render::sel].BBtog != 1)
			Render::mdl_obj[Render::sel].BBtog = 1;
		else
			Render::mdl_obj[Render::sel].BBtog = 0;
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete")) {
		Render::mdl_obj.erase(Render::mdl_obj.begin() + Render::sel);
		Render::collider_obj.erase(Render::collider_obj.begin() + Render::sel);
	}
}
//
void obj_property() {
	
	ImGui::SliderFloat("dwaScale X", &Render::mdl_obj[Render::sel].scaling.x, 0.f, 2.f);// Edit 1 float using a slider from 0.0f to 1.0f    
	ImGui::SliderFloat("dwaScale Y", &Render::mdl_obj[Render::sel].scaling.y, 0.f, 2.f);// Edit 1 float using a slider from 0.0f to 1.0f    
	ImGui::SliderFloat("dwaRotation", &Render::mdl_obj[Render::sel].rotation, -360.f, 360.f);
	ImGui::SliderFloat("dwaTranslate X", &Render::mdl_obj[Render::sel].translation.x, -1, 1);
	ImGui::SliderFloat("wdaTranslate Y", &Render::mdl_obj[Render::sel].translation.y, 1, -1);
	
}
//
void texture_property() {
	
		if (ImGui::Button("Big Boss")) {
			if (Render::mdl_obj[Render::sel].text_file != 1)
				Render::mdl_obj[Render::sel].text_file = 1;
			else
				Render::mdl_obj[Render::sel].text_file = 0;
		}
		if (ImGui::Button("Background")) {
			if (Render::mdl_obj[Render::sel].text_file != 2)
				Render::mdl_obj[Render::sel].text_file = 2;
			else
				Render::mdl_obj[Render::sel].text_file = 0;
		}
		if (ImGui::Button("Display")) {
			if (Render::mdl_obj[Render::sel].text_file != 3)
				Render::mdl_obj[Render::sel].text_file = 3;
			else
				Render::mdl_obj[Render::sel].text_file = 0;
		}
		if (ImGui::Button("Animation")) {
			if (Render::mdl_obj[Render::sel].animation_but != 1)
				Render::mdl_obj[Render::sel].animation_but = 1;
			else
				Render::mdl_obj[Render::sel].animation_but = 0;
		}
	
}
//
void colliderobj_property() {
	
		ImGui::SliderFloat("Scale X", &Render::collider_obj[Render::sel].scaling.x, 0.f, 2.f);// Edit 1 float using a slider from 0.0f to 1.0f    
		ImGui::SliderFloat("Scale Y", &Render::collider_obj[Render::sel].scaling.y, 0.f, 2.f);// Edit 1 float using a slider from 0.0f to 1.0f    
		ImGui::SliderFloat("Translate X", &Render::collider_obj[Render::sel].translation.x, -1, 1);
		ImGui::SliderFloat("Translate Y", &Render::collider_obj[Render::sel].translation.y, 1, -1);
		if (ImGui::Button("Reset"))
			Render::collider_obj[Render::sel].reset_but = 1;
	
}

namespace Thomas
{
	ImGuiLayer::ImGuiLayer()
		:Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
	
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();
		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");

		ImGui::StyleColorsDark();
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
	}

	void ImGuiLayer::End()
	{
		
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::OnImGuiRender()
	{
		/*static bool show = true;
		ImGui::ShowDemoWindow(&show);
		ImGui::ShowDebugLogWindow(&show);
		ImGui::ShowMetricsWindow(&show);*/

		/*buttons();
		obj_property();*/


		buttons();
		obj_property();
		texture_property();
		colliderobj_property();
	}
}
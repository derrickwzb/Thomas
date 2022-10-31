#include "thpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


#include "Thomas/Core/application.h"
#include "Thomas/Renderer/Graphics.h"
#include "Thomas/Scene/Entity.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"


void buttons() {
	if (ImGui::Button("BB")) {
		auto tex_data = Thomas::factory.GetComponent<Thomas::Box_collider>(Thomas::Graphics::sel);

		if (tex_data.box_tog != 1)
			tex_data.box_tog = 1;
		else
			tex_data.box_tog = 0;
		std::cout << Thomas::Graphics::sel << "             " << tex_data.box_tog << std::endl;

		Thomas::factory.ChangeComponent<Thomas::Box_collider>(Thomas::Graphics::sel, tex_data);
	}
	ImGui::SameLine();
	if (ImGui::Button("No_Tag_Cam")) {
		if (Thomas::Graphics::cam_stuff.cam_mode != 1)
			Thomas::Graphics::cam_stuff.cam_mode = 1;
		else
			Thomas::Graphics::cam_stuff.cam_mode = 0;
		std::cout << Thomas::Graphics::cam_stuff.cam_mode << std::endl;
	}
	ImGui::SameLine();
	if (ImGui::Button("Tag_Cam")) {
		if (Thomas::Graphics::cam_stuff.cam_mode != 2)
			Thomas::Graphics::cam_stuff.cam_mode = 2;
		else
			Thomas::Graphics::cam_stuff.cam_mode = 0;
		std::cout << Thomas::Graphics::cam_stuff.cam_mode << std::endl;
	}
}

void obj_property() {
	auto tex_data = Thomas::factory.GetComponent<Thomas::Transform>(Thomas::Graphics::sel);
	ImGui::SliderFloat("Obj_Scale X", &tex_data.scaling.x, 0.f, 2.f);// Edit 1 float using a slider from 0.0f to 1.0f    
	ImGui::SliderFloat("Obj_Scale Y", &tex_data.scaling.y, 0.f, 2.f);// Edit 1 float using a slider from 0.0f to 1.0f    
	ImGui::SliderFloat("Obj_Rotation", &tex_data.rotation, -360.f, 360.f);
	ImGui::SliderFloat("Obj_Translate X", &tex_data.translation.x, -1, 1);
	ImGui::SliderFloat("Obj_Translate Y", &tex_data.translation.y, 1, -1);

	Thomas::factory.ChangeComponent<Thomas::Transform>(Thomas::Graphics::sel, tex_data);
}

void colliderobj_property() {
	auto tex_data = Thomas::factory.GetComponent<Thomas::Box_collider>(Thomas::Graphics::sel);
	ImGui::SliderFloat("Box_Scale X", &tex_data.box_trans.scaling.x, 0.f, 2.f);// Edit 1 float using a slider from 0.0f to 1.0f    
	ImGui::SliderFloat("Box_Scale Y", &tex_data.box_trans.scaling.y, 0.f, 2.f);// Edit 1 float using a slider from 0.0f to 1.0f    
	ImGui::SliderFloat("Box_Translate X", &tex_data.box_trans.translation.x, -1, 1);
	ImGui::SliderFloat("Box_Translate Y", &tex_data.box_trans.translation.y, 1, -1);
	if (ImGui::Button("Box_Reset"))
		tex_data.reset_but = 1;
	Thomas::factory.ChangeComponent<Thomas::Box_collider>(Thomas::Graphics::sel, tex_data);
}

void texture_property() {
	auto tex_data = Thomas::factory.GetComponent<Thomas::Texture>(Thomas::Graphics::sel);
	if (ImGui::Button("Big Boss")) {
		if (tex_data.text_file != 1)
			tex_data.text_file = 1;
		else
			tex_data.text_file = 0;
	}
	if (ImGui::Button("Background")) {
		if (tex_data.text_file != 2)
			tex_data.text_file = 2;
		else
			tex_data.text_file = 0;
	}
	if (ImGui::Button("Display")) {
		if (tex_data.text_file != 3)
			tex_data.text_file = 3;
		else
			tex_data.text_file = 0;
	}
	if (ImGui::Button("Animation")) {
		if (tex_data.animation_but != 1)
			tex_data.animation_but = 1;
		else
			tex_data.animation_but = 0;
	}

	Thomas::factory.ChangeComponent<Thomas::Texture>(Thomas::Graphics::sel, tex_data);
	
}
//
//void colliderobj_property() {
//		
//		ImGui::SliderFloat("Scale X", &Graphics::collider_obj[Graphics::sel].trans_stuff.scaling.x, 0.f, 2.f);// Edit 1 float using a slider from 0.0f to 1.0f    
//		ImGui::SliderFloat("Scale Y", &Graphics::collider_obj[Graphics::sel].trans_stuff.scaling.y, 0.f, 2.f);// Edit 1 float using a slider from 0.0f to 1.0f    
//		ImGui::SliderFloat("Translate X", &Graphics::collider_obj[Graphics::sel].trans_stuff.translation.x, -1, 1);
//		ImGui::SliderFloat("Translate Y", &Graphics::collider_obj[Graphics::sel].trans_stuff.translation.y, 1, -1);
//		if (ImGui::Button("Reset"))
//			Graphics::collider_obj[Graphics::sel].reset_but = 1;
//	
//}

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
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
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

		//ImGui::StyleColorsDark();
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

		/*static bool show = true;
		ImGui::ShowDemoWindow(&show);*/
	}
}
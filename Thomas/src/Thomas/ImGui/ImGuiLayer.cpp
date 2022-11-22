/******************************************************************************/
/*!
\file		ImGuiLayer.cpp
\author 	Derrick Woo
\par    	email: d.woo@digipen.edu
\date   	25/9/2022
\brief		This file represents the interface of the source file
			ImGuiLayer.cpp, it contains the function prototype declarations
			and class definition.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "thpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


#include "Thomas/Core/application.h"
#include "Thomas/Renderer/Graphics.h"
#include "Thomas/Scene/Entity.h"
#include "Thomas/Audio/AudioSystem.h"
#include "Thomas/Physics/physicsSystem.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

//using EntityID = unsigned int;

//void buttons() {
//	if (Thomas::factory.HasComponent<Thomas::Box_collider>(Thomas::Graphics::sel) && Thomas::Graphics::sel != NULL) {
//		if (ImGui::Button("BB")) {
//			auto tex_data = Thomas::factory.GetComponent<Thomas::Box_collider>(Thomas::Graphics::sel);
//
//			if (tex_data.box_tog != 1)
//				tex_data.box_tog = 1;
//			else
//				tex_data.box_tog = 0;
//			Thomas::factory.UpdateComponent<Thomas::Box_collider>(Thomas::Graphics::sel, tex_data);
//		}
//		ImGui::SameLine();
//	}
//}
//
//void obj_property() {
//	if (Thomas::factory.HasComponent<Thomas::Transform>(Thomas::Graphics::sel) && Thomas::Graphics::sel != NULL) {
//		auto tex_data = Thomas::factory.GetComponent<Thomas::Transform>(Thomas::Graphics::sel);
//		ImGui::SliderFloat("Obj_Scale X", &tex_data.scaling.x, 0.f, 2.f);// Edit 1 float using a slider from 0.0f to 1.0f    
//		ImGui::SliderFloat("Obj_Scale Y", &tex_data.scaling.y, 0.f, 2.f);// Edit 1 float using a slider from 0.0f to 1.0f    
//		ImGui::SliderFloat("Obj_Rotation", &tex_data.rotation, -360.f, 360.f);
//		ImGui::SliderFloat("Obj_Translate X", &tex_data.translation.x, -1, 1);
//		ImGui::SliderFloat("Obj_Translate Y", &tex_data.translation.y, 1, -1);
//
//		Thomas::factory.UpdateComponent<Thomas::Transform>(Thomas::Graphics::sel, tex_data);
//	}
//}
//
//void colliderobj_property() {
//	if (Thomas::factory.HasComponent<Thomas::Box_collider>(Thomas::Graphics::sel) && Thomas::Graphics::sel != NULL) {
//		auto tex_data = Thomas::factory.GetComponent<Thomas::Box_collider>(Thomas::Graphics::sel);
//		ImGui::SliderFloat("Box_Scale X", &tex_data.box_trans.scaling.x, 0.f, 2.f);// Edit 1 float using a slider from 0.0f to 1.0f    
//		ImGui::SliderFloat("Box_Scale Y", &tex_data.box_trans.scaling.y, 0.f, 2.f);// Edit 1 float using a slider from 0.0f to 1.0f    
//		ImGui::SliderFloat("Box_Translate X", &tex_data.box_trans.translation.x, -1, 1);
//		ImGui::SliderFloat("Box_Translate Y", &tex_data.box_trans.translation.y, 1, -1);
//		if (ImGui::Button("Box_Reset"))
//			tex_data.reset_but = 1;
//		Thomas::factory.UpdateComponent<Thomas::Box_collider>(Thomas::Graphics::sel, tex_data);
//	}
//}

//void texture_property() {
//	if (Thomas::factory.HasComponent<Thomas::Texture>(Thomas::Graphics::sel) && Thomas::Graphics::sel != NULL) {
//		auto tex_data = Thomas::factory.GetComponent<Thomas::Texture>(Thomas::Graphics::sel);
//		if (ImGui::Button("Big Boss")) {
//			if (tex_data.text_file != 1)
//				tex_data.text_file = 1;
//			else
//				tex_data.text_file = 0;
//		}
//		if (ImGui::Button("Background")) {
//			if (tex_data.text_file != 2)
//				tex_data.text_file = 2;
//			else
//				tex_data.text_file = 0;
//		}
//		if (ImGui::Button("Display")) {
//			if (tex_data.text_file != 3)
//				tex_data.text_file = 3;
//			else
//				tex_data.text_file = 0;
//		}
//		if (ImGui::Button("Animation")) {
//			if (tex_data.animation_but != 1)
//				tex_data.animation_but = 1;
//			else
//				tex_data.animation_but = 0;
//		}
//
//		Thomas::factory.UpdateComponent<Thomas::Texture>(Thomas::Graphics::sel, tex_data);
//	}
//}

namespace Thomas
{
	ImGuiLayer::ImGuiLayer()
		:Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
		OnDetach();
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

	/*void factory_button();
	void object_data();*/
	inline static double Editor_timetaken = 0;
	inline static bool show_performance = false;

	void ImGuiLayer::OnImGuiRender()
	{
		auto start = std::chrono::steady_clock::now();
		//ImGui::Begin("Properties");

		///*buttons();
		//obj_property();
		//texture_property();
		//colliderobj_property();*/

		//ImGui::Separator();
		////factory_button();

		//ImGui::End();

		//object_data();
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double> duration = (stop - start);
		Editor_timetaken = duration.count();
	}
	void ImGuiLayer::OnEvent(Event& e)
	{
		if (m_BlockEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			e.Handled |= e.IsInCategory(EVENTCATEGORYMOUSE) & io.WantCaptureMouse;
			e.Handled |= e.IsInCategory(EVENTCATEGORYKEYBOARD) & io.WantCaptureKeyboard;
		}


	}

	/*void factory_button() {
		if (ImGui::Button("Add object")) {
			Thomas::Application::entities = Thomas::factory.BuildAndSerialize("../Assets/Objects/New Square.json");
		}
		ImGui::SameLine();
		if (ImGui::Button("Clone current object")) {
			EntityID new_entity = Thomas::factory.Clone(Thomas::Graphics::sel);
			Thomas::Application::entities.push_back(new_entity);
		}

		if (ImGui::Button("Delete current object")) {
			Thomas::factory.Destroy(Thomas::Graphics::sel);
			Graphics::sel = NULL;
		}
		ImGui::SameLine();
		if (ImGui::Button("Delete all object")) {
			Thomas::factory.DestroyAllObjects(Thomas::Application::entities);
			Graphics::sel = NULL;
		}

		if (ImGui::Button("Deserialize from file")) {
			Thomas::Application::entities = Thomas::factory.BuildAndSerialize("../Assets/Objects/test1.json");
		}
		ImGui::SameLine();
		if (ImGui::Button("Serialize to file")) {
			Thomas::factory.SaveToFile(Thomas::Application::entities, "../Assets/Objects/test1.json");
		}
		ImGui::Separator();

		if (ImGui::Button("Show Performance")) {
			if (show_performance == false) {
				show_performance = true;
			}
			else {
				show_performance = false;
			}
		}
		if (show_performance == true) {
			double total_time = Logic::Logic_timetaken + AudioSystem::Audio_timetaken + Editor_timetaken +
				Graphics::Graphic_update_timetaken + Graphics::Graphic_draw_timetaken + Physics::Physic_timetaken;
			ImGui::Text("Logic: %f%%\n", (Logic::Logic_timetaken/total_time) * 100);
			ImGui::Text("Audio: %f%%\n", (AudioSystem::Audio_timetaken / total_time) * 100);
			ImGui::Text("Editor: %f%%\n", (Editor_timetaken / total_time) * 100);
			ImGui::Text("Graphic Update: %f%%\n", (Graphics::Graphic_update_timetaken / total_time) * 100);
			ImGui::Text("Graphic Draw: %f%%\n", (Graphics::Graphic_draw_timetaken / total_time) * 100);
			ImGui::Text("Physic: %f%%\n", (Physics::Physic_timetaken / total_time) * 100);
		}
	}

	void object_data() {
		ImGui::Begin("Data for current object");
		if (Graphics::sel != NULL) {

			ImGui::Text("Object Id: %d\n", Graphics::sel);
			ImGui::Separator();

			if (factory.HasComponent<Transform>(Graphics::sel)) {
				auto trans_data = factory.GetComponent<Transform>(Graphics::sel);
				ImGui::Text("Transform Component:\n");
				ImGui::Text("Translation: %f, %f\n", trans_data.translation.x, trans_data.translation.y);
				ImGui::Text("Rotation: %f\n", trans_data.rotation);
				ImGui::Text("Scaling: %f, %f\n", trans_data.scaling.x, trans_data.scaling.y);

				ImGui::Separator();
			}
			

			if (factory.HasComponent<Texture>(Graphics::sel)) {
				auto tex_data = factory.GetComponent<Texture>(Graphics::sel);
				ImGui::Text("Texture Component:\n");

				if (tex_data.text_file == 1) {
					ImGui::Text("Texture file: bigboss.png\n");
				}
				else if (tex_data.text_file == 2) {
					ImGui::Text("Texture file: background.png\n");
				}
				else if (tex_data.text_file == 3) {
					ImGui::Text("Texture file: sprite.png\n");
				}
				else {
					ImGui::Text("Texture file: nil\n");
				}

				ImGui::Separator();
			}

			
			if (factory.HasComponent<Box_collider>(Graphics::sel)) {
				ImGui::Text("Collider Component:\n");
				auto bb_box_data = factory.GetComponent<Box_collider>(Graphics::sel);
				ImGui::Text("Collider Translation: %f, %f\n", bb_box_data.box_trans.translation.x, bb_box_data.box_trans.translation.y);
				ImGui::Text("Collider Rotation: %f\n", bb_box_data.box_trans.rotation);
				ImGui::Text("Collider Scaling: %f, %f\n", bb_box_data.box_trans.scaling.x, bb_box_data.box_trans.scaling.y);
				if (bb_box_data.collision_detected == 0) {
					ImGui::Text("No Collision");
				}
				else {
					ImGui::Text("Collide with other object");
				}

				if (ImGui::Button("Delete Collider")) {
					factory.RemoveComponent<Box_collider>(Graphics::sel);
				}
				ImGui::Separator();
			}

			if (factory.HasComponent<AudioComponent>(Graphics::sel)) {
				auto audio_data = factory.GetComponent<AudioComponent>(Graphics::sel);
				ImGui::Text("Audio Component:\n");
				if (audio_data.filepath.c_str() == "../Assets/boss.wav") {
					ImGui::Text("Audio file: boss.wav");
				}
				ImGui::Text("Audio volume: %f\n", audio_data.fVolumedB);
				ImGui::Separator();
			}

			ImGui::Text("Logic Component:\n");
			if (factory.HasComponent<Logic01>(Graphics::sel)) {
				ImGui::Text("Using patrol logic");
				if (ImGui::Button("Delete patorl logic")) {
					factory.RemoveComponent<Logic01>(Graphics::sel);
				}
			}

			if (factory.HasComponent<Logic02>(Graphics::sel)) {
				ImGui::Text("Using follow logic");
				if (ImGui::Button("Delete follow logic")) {
					factory.RemoveComponent<Logic02>(Graphics::sel);
				}
			}

			if(!factory.HasComponent<Logic01>(Graphics::sel) && !factory.HasComponent<Logic02>(Graphics::sel)) {
				ImGui::Text("Not running any logic");
			}
			ImGui::Separator();
		}
		else {
			ImGui::Text("Not selecting any object");
		}
		ImGui::End();
	}*/
}

#include "EditorLayer.h"
#include "ImGui/imgui.h"
//#include "Thomas/Core/application.h"
//#include "Thomas/Renderer/Graphics.h"
#include "GLEW/include/GL/glew.h"
//#include "Thomas/Physics/physicsSystem.h"

namespace Thomas
{
	EditorLayer::EditorLayer()
		:Layer("Editor Layer")
	{

	}

	void EditorLayer::OnAttach()
	{
		FramebufferSpec fbSpec;
		fbSpec.Width = 1920;
		fbSpec.Height = 1080;
		m_Framebuffer = std::make_shared<Framebuffer>(fbSpec);

		m_Camera.Camera2D_Init();
	}

	void EditorLayer::OnDetach()
	{
		//profile

	}

	void EditorLayer::OnUpdate(Thomas::Timestep ts)
	{
		//Thomas::Application& app = Thomas::Application::Get();
		//update camera controller here
		
		////render update here
		if (m_ViewportFocused)
		{
			physicsSystem.Input(Graphics::sel, ts);
			physicsSystem.Update(Application::entities, ts);
			m_Camera.Camera2D_Update();

		}
		//m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		
		
		Graphics::update(Application::entities);
		m_Framebuffer->Bind();
		////Graphics::draw();
		glClearColor(0.1f, 0.1f, 0.1f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Graphics::draw(Application::entities);

		m_Framebuffer->Unbind();

	}

	void EditorLayer::OnImGuiRender()
	{
		
			static bool dockspaceOpen = true;
			static bool opt_fullscreen_persistant = true;
			bool opt_fullscreen = opt_fullscreen_persistant;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_fullscreen)
			{
				ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->Pos);
				ImGui::SetNextWindowSize(viewport->Size);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

				if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
					window_flags |= ImGuiWindowFlags_NoBackground;

				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
				ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
				ImGui::PopStyleVar();

				if (opt_fullscreen)
					ImGui::PopStyleVar(2);

				ImGuiIO& io = ImGui::GetIO();
				if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
				{
					ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
					ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
				}

				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("File"))
					{
						// Disabling fullscreen would allow the window to be moved to the front of other windows, 
						// which we can't undo at the moment without finer window depth/z control.
						//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

						if (ImGui::MenuItem("Exit")) Application::Get().Close();
						ImGui::EndMenu();
					}

					ImGui::EndMenuBar();
				}

				ImGui::Begin("Settings");

				//auto stats = Hazel::Renderer2D::GetStats();
				ImGui::Text("Renderer2D Stats:");
				/*ImGui::Text("Draw Calls: %d", stats.DrawCalls);
				ImGui::Text("Quads: %d", stats.QuadCount);
				ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
				ImGui::Text("Indices: %d", stats.GetTotalIndexCount());*/

				//uint32_t textureID = Thomas::Graphics::g_Framebuffer->GetColorAttachmentID();
				
				ImGui::End();


				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
				ImGui::Begin("Viewport");
				m_ViewportFocused = ImGui::IsWindowFocused();
				m_ViewportHovered = ImGui::IsWindowHovered();
				Application::Get().GetImguiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);
				
				//TH_CORE_WARN("Focused{0} " , ImGui::IsWindowFocused());
				//TH_CORE_WARN("Hovered{0} ", ImGui::IsWindowHovered());
				ImVec2 viewportPanelsize = ImGui::GetContentRegionAvail();	
				//TH_WARN()
				if (m_ViewportSize != *((glm::vec2*)&viewportPanelsize) && viewportPanelsize.x > 0 && viewportPanelsize.y > 0)
				{
					//m_Framebuffer->Resize((uint32_t)viewportPanelsize.x , (uint32_t)viewportPanelsize.y);
					m_ViewportSize = { viewportPanelsize.x , viewportPanelsize.y };

				}
				uint32_t textureID = m_Framebuffer->GetColorAttachmentID();
				//m_Framebuffer->GetSpec().Width
				ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x,m_ViewportSize.y}, ImVec2{0, 1}, ImVec2{1, 0});
				ImGui::End();
				ImGui::PopStyleVar();

				ImGui::End();
			}
		
			
			
	}

	void EditorLayer::OnEvent(Thomas::Event& e)
	{
		//push event to camera controller
	}
}
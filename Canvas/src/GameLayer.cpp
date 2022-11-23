#include "GameLayer.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GLEW/include/GL/glew.h"

using namespace Thomas;

GameLayer::GameLayer()
	: Layer("GameLayer")
{
	auto& window = Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());

	m_ActiveScene = std::make_shared<Thomas::Scene>();
	m_player = &(m_ActiveScene->CreateEntity("player"));

	Random::Init();
}

void GameLayer::OnAttach()
{
	m_Level.Init();

	ImGuiIO io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("assets/OpenSans-Regular.ttf", 120.0f);

	
	
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(Thomas::Timestep ts)
{
	m_Time += ts;
	if ((int)(m_Time * 10.0f) % 8 > 4)
		m_Blink = !m_Blink;

	if (m_Level.IsGameOver())
		m_State = GameState::GameOver;

	if (Input::IsKeyPressed(TH_KEY_W)) {
		//*m_player->GetComponent<Transform>()->translation.y += 5.f;

	}

	//std::map<EntityID, Signature> group = m_ActiveScene->GetRegistry()->GetEntities();

	//for (auto e : group) {

	//	auto get_tag = factory.GetComponent<TagComponent>(e.first);

	//	if (get_tag.tag == "player") {

	//		auto get_trans = factory.GetComponent<Transform>(e.first);

	//		if (Input::IsKeyPressed(TH_KEY_W)) {
	//			get_trans.translation.y += 5.f;
	//		}
	//	}
	//}

	
	//const auto& playerPos = m_Level.GetPlayer().GetPosition();
	//m_Camera->SetPosition({ playerPos.x, playerPos.y, 0.0f });

	switch (m_State)
	{
		case GameState::Play:
		{
			glClearColor(1.f, 1.f, 1.f, 0.5f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_ActiveScene->OnUpdate(ts);

			m_Level.OnUpdate(ts);
			break;
		}
	}

	// Render
	//Thomas::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
	//Thomas::RenderCommand::Clear();

	//Thomas::Renderer2D::BeginScene(*m_Camera);
	m_Level.OnRender();
	//Thomas::Renderer2D::EndScene();
}

void GameLayer::OnImGuiRender()
{
	//ImGui::Begin("Settings");
	//m_Level.OnImGuiRender();
	//ImGui::End();

	// UI?

	switch (m_State)
	{
		case GameState::Play:
		{
			uint32_t playerScore = m_Level.GetPlayer().GetScore();
			std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
			ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, scoreStr.c_str());
			
			
			break;
		}
		case GameState::MainMenu:
		{
			auto pos = ImGui::GetWindowPos();
			auto width = Application::Get().GetWindow().GetWidth();
			auto height = Application::Get().GetWindow().GetHeight();
			pos.x += width * 0.5f - 300.0f;
			pos.y += 50.0f;
			if (m_Blink)
				ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");
			break;
		}
		case GameState::GameOver:
		{
			auto pos = ImGui::GetWindowPos();
			auto width = Application::Get().GetWindow().GetWidth();
			auto height = Application::Get().GetWindow().GetHeight();
			pos.x += width * 0.5f - 300.0f;
			pos.y += 50.0f;
			if (m_Blink)
				ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");

			pos.x += 200.0f;
			pos.y += 150.0f;
			uint32_t playerScore = m_Level.GetPlayer().GetScore();
			std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
			ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, pos, 0xffffffff, scoreStr.c_str());
			break;
		}
	}
}

void GameLayer::OnEvent(Thomas::Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(TH_BIND_EVENT_FN(GameLayer::OnWindowResize));
	dispatcher.Dispatch<MouseButtonPressedEvent>(TH_BIND_EVENT_FN(GameLayer::OnMouseButtonPressed));
}

bool GameLayer::OnMouseButtonPressed(Thomas::MouseButtonPressedEvent& e)
{
	if (m_State == GameState::GameOver)
		m_Level.Reset();

	m_State = GameState::Play;
	return false;
}

bool GameLayer::OnWindowResize(Thomas::WindowResizeEvent& e)
{
	CreateCamera(e.GetWidth(), e.GetHeight());
	return false;
}

void GameLayer::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / (float)height;

	float camWidth = 8.0f;
	float bottom = -camWidth;
	float top = camWidth;
	float left = bottom * aspectRatio;
	float right = top *aspectRatio;
	//m_Camera = CreateScope<OrthographicCamera>(left, right, bottom, top);
}

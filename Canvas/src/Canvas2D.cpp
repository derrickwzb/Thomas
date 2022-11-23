#include "Canvas2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GLEW/include/GL/glew.h"

using namespace Thomas;

Canvas2D::Canvas2D()
	: Layer("Canvas2D")
{
	/*auto& window = Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());*/

	//std::cout << m_player->GetComponent<Transform>().translation.y << std::endl;

	//Random::Init();
}

void Canvas2D::OnAttach()
{

	FramebufferSpec fbSpec;
	fbSpec.Width = 1920;
	fbSpec.Height = 1080;
	m_Framebuffer = std::make_shared<Framebuffer>(fbSpec);

	

	//m_Level.Init();
	m_ActiveScene = std::make_shared<Thomas::Scene>();

	

	m_player = m_ActiveScene->CreateEntity("player");
	//TH_CORE_INFO("{0}", m_player->GetID());
	
	m_player.GetComponent<Transform>().scaling.x = 0.5f;
	m_player.GetComponent<Transform>().scaling.y = 0.5f;
	//m_player.GetComponent<Transform>().translation.x = 0.f;
	//m_player.GetComponent<Transform>().translation.y = 0.f;

	//m_test = m_ActiveScene->CreateEntity("test");
	
	//m_ActiveScene->CreateEntity();
	ImGuiIO io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("assets/OpenSans-Regular.ttf", 120.0f);

}

void Canvas2D::OnDetach()
{
}

void Canvas2D::OnUpdate(Thomas::Timestep ts)
{
	m_Time += ts;
	if ((int)(m_Time * 10.0f) % 8 > 4)
		m_Blink = !m_Blink;

	if (m_Level.IsGameOver())
		m_State = GameState::GameOver;

	//if (Input::IsKeyPressed(TH_KEY_SPACE)) {
	//	TH_CORE_TRACE("MouseX :{0}", Input::GetMouseX()); //0 - 1900
	//	TH_CORE_TRACE("MouseY :{0}", Input::GetMouseY()); //0 - 1000
	//}
	
	//std::cout << m_player->GetComponent<Transform>().translation.y << std::endl;

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
		if (Input::IsKeyPressed(TH_KEY_W)) {
			//m_player->GetComponent<Transform>()->translation.y += 5.f;
			/*auto& data = m_player->GetComponent<Transform>();
			data.translation.y += 5.f;*/
			/*TH_CORE_INFO("{0}", m_player->GetID());*/
			
			m_player.GetComponent<Transform>().translation.y -= 5.f * ts;
			//TH_CORE_TRACE("{0}", m_player.GetComponent<Transform>().translation.y);
			//std::cout << m_player->GetComponent<Transform>().translation.y << std::endl;
		}
		if (Input::IsKeyPressed(TH_KEY_S)) {
			m_player.GetComponent<Transform>().translation.y += 5.f * ts;
			//TH_CORE_TRACE("{0}", m_player.GetComponent<Transform>().translation.y);
		}
		if (Input::IsKeyPressed(TH_KEY_A)) {
			m_player.GetComponent<Transform>().translation.x -= 5.f * ts;
			//TH_CORE_TRACE("{0}", m_player.GetComponent<Transform>().translation.x);
		}
		if (Input::IsKeyPressed(TH_KEY_D)) {
			m_player.GetComponent<Transform>().translation.x += 5.f * ts;
			//TH_CORE_TRACE("{0}", m_player.GetComponent<Transform>().translation.x);
		}
		if (Input::IsKeyPressed(TH_KEY_Q)) {
			m_player.GetComponent<Transform>().rotation -= 50.f * ts;
			//TH_CORE_TRACE("{0}", m_player.GetComponent<Transform>().translation.x);
		}
		if (Input::IsKeyPressed(TH_KEY_E)) {
			m_player.GetComponent<Transform>().rotation += 50.f * ts;
			//TH_CORE_TRACE("{0}", m_player.GetComponent<Transform>().translation.x);
		}

		static float timer = 0.f;

		if (Input::IsKeyPressed(TH_KEY_SPACE) && timer <= 0.f) {
			auto bullet = m_ActiveScene->CreateEntity("bullet");

			bullet.AddComponent<BulletComponent>();

			bullet.GetComponent<Transform>().scaling.x = 0.1f;
			bullet.GetComponent<Transform>().scaling.y = 0.1f;
			bullet.GetComponent<Transform>().translation.x = m_player.GetComponent<Transform>().translation.x;
			bullet.GetComponent<Transform>().translation.y = m_player.GetComponent<Transform>().translation.y;
			bullet.GetComponent<Transform>().rotation = m_player.GetComponent<Transform>().rotation;
			
			bullet.GetComponent<BulletComponent>().speed = 0.01f;
			bullet.GetComponent<BulletComponent>().time = 1.f;


			
			//while (bullet.GetComponent<Transform>().translation.x <= 1.f) {
			//	bullet.GetComponent<Transform>().translation.x += 0.01f;
			//	glClearColor(1.f, 1.f, 1.f, 0.5f);
			//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//	m_ActiveScene->OnUpdate(ts);
			//	TH_CORE_TRACE("bullet: {0}", bullet.GetComponent<Transform>().translation.x);
			//}

			//m_ActiveScene->DestroyEntity(bullet);
			timer += 1.f;
		}

		timer -= ts;

		Graphics::cam_stuff.Camera2D_Update(m_Framebuffer->GetSpec().Width, m_Framebuffer->GetSpec().Height);

		glClearColor(1.f, 1.f, 1.f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_ActiveScene->OnUpdate(ts);

		//m_Level.OnUpdate(ts);
		break;
	}
	}


	// Render
	//Thomas::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
	//Thomas::RenderCommand::Clear();

	//Thomas::Renderer2D::BeginScene(*m_Camera);
	//m_Level.OnRender();
	//Thomas::Renderer2D::EndScene();
}

void Canvas2D::OnImGuiRender()
{
	//ImGui::Begin("Settings");
	//m_Level.OnImGuiRender();
	//ImGui::End();

	// UI?

	switch (m_State)
	{
	case GameState::Play:
	{
		//uint32_t playerScore = m_Level.GetPlayer().GetScore();
		//std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
		//ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, scoreStr.c_str());


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
			ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, ImGui::GetWindowPos(), 0xffffffff, "Click to Play!");
		break;
	}
	case GameState::GameOver:
	{
		//auto pos = ImGui::GetWindowPos();
		//auto width = Application::Get().GetWindow().GetWidth();
		//auto height = Application::Get().GetWindow().GetHeight();
		//pos.x += width * 0.5f - 300.0f;
		//pos.y += 50.0f;
		//if (m_Blink)
		//	ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");

		//pos.x += 200.0f;
		//pos.y += 150.0f;
		//uint32_t playerScore = m_Level.GetPlayer().GetScore();
		//std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
		//ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, pos, 0xffffffff, scoreStr.c_str());
		break;
	}
	}
}

void Canvas2D::OnEvent(Thomas::Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(TH_BIND_EVENT_FN(Canvas2D::OnWindowResize));
	dispatcher.Dispatch<MouseButtonPressedEvent>(TH_BIND_EVENT_FN(Canvas2D::OnMouseButtonPressed));
}

bool Canvas2D::OnMouseButtonPressed(Thomas::MouseButtonPressedEvent& e)
{
	if (m_State == GameState::GameOver)
		m_Level.Reset();

	m_State = GameState::Play;
	return false;
}

bool Canvas2D::OnWindowResize(Thomas::WindowResizeEvent& e)
{
	CreateCamera(e.GetWidth(), e.GetHeight());
	return false;
}

void Canvas2D::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / (float)height;

	float camWidth = 8.0f;
	float bottom = -camWidth;
	float top = camWidth;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	//m_Camera = CreateScope<OrthographicCamera>(left, right, bottom, top);
}

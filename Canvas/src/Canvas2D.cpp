#include "Canvas2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GLEW/include/GL/glew.h"
#include "glm/glm.hpp"

using namespace Thomas;

static float PI = 3.1415926;
static float bullet_timer = 0.f;
static bool start = false;
static float player_speed = 1.f;
static bool call_once = false;

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

	//add background
	m_background = m_ActiveScene->CreateEntity("background");

	m_background.AddComponent<Texture>();
	m_background.GetComponent<Texture>().text_file = 1;
	m_background.GetComponent<Texture>().texid = stash.Text_Storage["wallpaper.png"];

	m_background.GetComponent<Transform>().translation.y = -1.f;
	m_background.GetComponent<Transform>().scaling.x = 8.f;
	m_background.GetComponent<Transform>().scaling.y = 6.f;
	m_background.GetComponent<Box_collider>().box_tog = 0; // 1 to show the box

	//add player
	m_player = m_ActiveScene->CreateEntity("player");
	//TH_CORE_INFO("{0}", m_player->GetID());
	
	m_player.GetComponent<Transform>().scaling.x = 0.25f;
	m_player.GetComponent<Transform>().scaling.y = 0.25f;

	m_player.AddComponent<Texture>();
	m_player.GetComponent<Texture>().text_file = 1;
	m_player.GetComponent<Texture>().texid = stash.Text_Storage["Chef_Kay_Top.png"];

	m_player.GetComponent<Box_collider>().box_trans.scaling.x = 0.25f;
	m_player.GetComponent<Box_collider>().box_trans.scaling.y = 0.25f;

	//m_player.GetComponent<Box_collider>().box_tog = 1; // 1 to show the box
	m_player.AddComponent<BoxCollider2D>();
	m_player.GetComponent<BoxCollider2D>().verticesList.push_back(m_player.GetComponent<Box_collider>().box_trans.global_vertice0);
	m_player.GetComponent<BoxCollider2D>().verticesList.push_back(m_player.GetComponent<Box_collider>().box_trans.global_vertice1);
	m_player.GetComponent<BoxCollider2D>().verticesList.push_back(m_player.GetComponent<Box_collider>().box_trans.global_vertice2);
	m_player.GetComponent<BoxCollider2D>().verticesList.push_back(m_player.GetComponent<Box_collider>().box_trans.global_vertice3);


	//add tables
	auto table = m_ActiveScene->CreateEntity("table");

	table.GetComponent<Transform>().translation.y = -1.f;
	table.GetComponent<Transform>().scaling.x = 1.f;
	table.GetComponent<Transform>().scaling.y = 1.f;

	table.AddComponent<Texture>();
	table.GetComponent<Texture>().text_file = 1;
	table.GetComponent<Texture>().texid = stash.Text_Storage["table5.png"];

	//table.GetComponent<Box_collider>().box_tog = 1; // 1 to show the box
	table.GetComponent<Box_collider>().box_trans.translation.t = -1.f;
	table.GetComponent<Box_collider>().box_trans.scaling.x = 0.65f;
	table.GetComponent<Box_collider>().box_trans.scaling.y = 0.65f;

	table.AddComponent<BoxCollider2D>();
	table.GetComponent<BoxCollider2D>().verticesList.push_back(table.GetComponent<Box_collider>().box_trans.global_vertice0);
	table.GetComponent<BoxCollider2D>().verticesList.push_back(table.GetComponent<Box_collider>().box_trans.global_vertice1);
	table.GetComponent<BoxCollider2D>().verticesList.push_back(table.GetComponent<Box_collider>().box_trans.global_vertice2);
	table.GetComponent<BoxCollider2D>().verticesList.push_back(table.GetComponent<Box_collider>().box_trans.global_vertice3);
	
	ImGuiIO io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("assets/OpenSans-Regular.ttf", 120.0f);

	//Audio Component
	m_player.AddComponent<AudioComponent>();
}

void Canvas2D::OnDetach()
{
}

void Canvas2D::OnUpdate(Thomas::Timestep ts)
{
	switch (m_State)
	{
	case GameState::MainMenu:
	{
		glClearColor(0.f, 0.f, 0.f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		break;
	}
	case GameState::Play:
	{
		if (Input::IsKeyPressed(TH_KEY_M)) {

			if (call_once == false) {
				
				call_once = true;
				m_player.GetComponent<AudioComponent>().nChannelId = AEngine.PlaySound(stash.Audio_Storage["boss.wav"], 100.0);
				int test = m_player.GetComponent<AudioComponent>().nChannelId;

			}

		}

		if (Input::IsKeyPressed(TH_KEY_N)) {
			std::cout << "id for stoppping " << m_player.GetComponent<AudioComponent>().nChannelId;

			AEngine.PauseChannel(m_player.GetComponent<AudioComponent>().nChannelId);
		}

		if (Input::IsKeyPressed(TH_KEY_B)) {
			std::cout << "id for stoppping " << m_player.GetComponent<AudioComponent>().nChannelId;

			AEngine.UnpauseChannel(m_player.GetComponent<AudioComponent>().nChannelId);
		}


		if (Input::IsKeyPressed(TH_KEY_W)) {
			m_player.GetComponent<Transform>().translation.y -= player_speed * ts;
			Graphics::cam_stuff.translation.y = -m_player.GetComponent<Transform>().translation.y;
			m_player.GetComponent<Box_collider>().box_trans.translation.y -= player_speed * ts;
		}
		if (Input::IsKeyPressed(TH_KEY_S)) {
			m_player.GetComponent<Transform>().translation.y += player_speed * ts;
			Graphics::cam_stuff.translation.y = -m_player.GetComponent<Transform>().translation.y;
			m_player.GetComponent<Box_collider>().box_trans.translation.y += player_speed * ts;
		}
		if (Input::IsKeyPressed(TH_KEY_A)) {
			m_player.GetComponent<Transform>().translation.x -= player_speed * ts;
			Graphics::cam_stuff.translation.x = m_player.GetComponent<Transform>().translation.x * 0.55;
			m_player.GetComponent<Box_collider>().box_trans.translation.x -= player_speed * ts;
		}
		if (Input::IsKeyPressed(TH_KEY_D)) {
			m_player.GetComponent<Transform>().translation.x += player_speed * ts;
			Graphics::cam_stuff.translation.x = m_player.GetComponent<Transform>().translation.x * 0.55;
			m_player.GetComponent<Box_collider>().box_trans.translation.x += player_speed * ts;
		}


		if (((Input::GetMouseX() / Application::Get().GetWindow().GetWidth() - 0.5f) * 4) > 0.f) {
			m_player.GetComponent<Transform>().rotation = 90.f + (atan2f(((Input::GetMouseY() / Application::Get().GetWindow().GetHeight() - 0.5f) * 2),
				((Input::GetMouseX() / Application::Get().GetWindow().GetWidth() - 0.5f) * 4)) * 180 / PI);
			//TH_CORE_TRACE("rot: {0}", m_player.GetComponent<Transform>().rotation);
		}
		else if (((Input::GetMouseX() / Application::Get().GetWindow().GetWidth() - 0.5f) * 4) < 0.f) {
			m_player.GetComponent<Transform>().rotation = 270.f + (atan2f(-((Input::GetMouseY() / Application::Get().GetWindow().GetHeight() - 0.5f) * 2),
				-((Input::GetMouseX() / Application::Get().GetWindow().GetWidth() - 0.5f) * 4)) * 180 / PI);
			//TH_CORE_TRACE("-rot: {0}", m_player.GetComponent<Transform>().rotation);
		}

		//TH_CORE_TRACE("p_x: {0}", m_player.GetComponent<Transform>().translation.x);
		//TH_CORE_TRACE("x: {0}", (Input::GetMouseX() / Application::Get().GetWindow().GetWidth() - 0.5f) * 4);
		//TH_CORE_TRACE("y: {0}", (Input::GetMouseY() / Application::Get().GetWindow().GetHeight() - 0.5f) * 2);


		if (bullet_timer >= 0.f) {
			bullet_timer -= ts;
		}

		Graphics::cam_stuff.Camera2D_Update(m_Framebuffer->GetSpec().Width, m_Framebuffer->GetSpec().Height);

		glClearColor(1.f, 1.f, 1.f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_ActiveScene->OnUpdate(ts);

		break;

	}
	case GameState::Pause:
	{
		glClearColor(0.f, 0.f, 0.f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		break;
	}
	case GameState::Quit:
	{
		glClearColor(0.f, 0.f, 0.f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		break;
	}
	case GameState::Htp:
	{
		glClearColor(0.f, 0.f, 0.f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		break;
	}
	}
}

void Canvas2D::OnImGuiRender()
{

	switch (m_State)
	{
	case GameState::MainMenu:
	{
		//start button
		auto width = Application::Get().GetWindow().GetWidth();
		auto height = Application::Get().GetWindow().GetHeight();

		ImVec2 pos;
		pos.x = width * 0.5f - 220.0f;
		pos.y = 150.f;

		//main menu text
		ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Main Menu");

		//start button
		ImVec2 pos1;
		pos1.x = width * 0.5f - 220.0f;
		pos1.y = 350.f;

		ImVec2 p1, p2, p3, p4;
		p1.x = pos1.x;
		p1.y = pos1.y;

		p2.x = pos1.x;
		p2.y = pos1.y + 130.f;

		p3.x = pos1.x + 465.f;
		p3.y = pos1.y + 130.f;

		p4.x = pos1.x + 465.f;
		p4.y = pos1.y;

		ImGui::GetForegroundDrawList()->AddQuadFilled(p1, p2, p3, p4, 0xffffffff);
		ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos1, 0xFF000000, "Start Game");

		//quit button
		ImVec2 pos2 = pos1;
		pos2.x += 10.f;
		pos2.y += 200.f;

		p1.x = pos2.x;
		p1.y = pos2.y;

		p2.x = pos2.x;
		p2.y = pos2.y + 130.f;

		p3.x = pos2.x + 445.f;
		p3.y = pos2.y + 130.f;

		p4.x = pos2.x + 445.f;
		p4.y = pos2.y;

		ImGui::GetForegroundDrawList()->AddQuadFilled(p1, p2, p3, p4, 0xffffffff);
		ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos2, 0xFF000000, "Quit Game");

		break;
	}
	case GameState::Play:
	{
		break;
	}
	case GameState::GameOver:
	{
		break;
	}
	case GameState::Pause:
	{
		//resume button
		auto width = Application::Get().GetWindow().GetWidth();
		auto height = Application::Get().GetWindow().GetHeight();

		ImVec2 pos;
		pos.x = width * 0.5f - 120.0f;
		pos.y = 150.f;

		//pause text
		ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Pause");

		ImVec2 pos1;
		pos1.x = width * 0.5f - 300.0f;
		pos1.y = 350.f;

		ImVec2 p1, p2, p3, p4;
		p1.x = pos1.x;
		p1.y = pos1.y;

		p2.x = pos1.x;
		p2.y = pos1.y + 130.f;

		p3.x = pos1.x + 600.f;
		p3.y = pos1.y + 130.f;

		p4.x = pos1.x + 600.f;
		p4.y = pos1.y;

		ImGui::GetForegroundDrawList()->AddQuadFilled(p1, p2, p3, p4, 0xffffffff);
		ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos1, 0xFF000000, "Resume Game");


		//How to play button
		ImVec2 pos2 = pos1;
		pos2.x += 50.f;
		pos2.y += 200.f;

		p1.x = pos2.x;
		p1.y = pos2.y;

		p2.x = pos2.x;
		p2.y = pos2.y + 130.f;

		p3.x = pos2.x + 510.f;
		p3.y = pos2.y + 130.f;

		p4.x = pos2.x + 510.f;
		p4.y = pos2.y;

		ImGui::GetForegroundDrawList()->AddQuadFilled(p1, p2, p3, p4, 0xffffffff);
		ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos2, 0xFF000000, "How To Play");


		//quit button
		ImVec2 pos3 = pos1;
		pos3.x += 75.f;
		pos3.y += 400.f;

		p1.x = pos3.x;
		p1.y = pos3.y;

		p2.x = pos3.x;
		p2.y = pos3.y + 130.f;

		p3.x = pos3.x + 445.f;
		p3.y = pos3.y + 130.f;

		p4.x = pos3.x + 445.f;
		p4.y = pos3.y;

		ImGui::GetForegroundDrawList()->AddQuadFilled(p1, p2, p3, p4, 0xffffffff);
		ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos3, 0xFF000000, "Quit Game");


		break;
	}
	case GameState::Quit:
	{
		auto width = Application::Get().GetWindow().GetWidth();
		auto height = Application::Get().GetWindow().GetHeight();

		ImVec2 pos;
		pos.x = width * 0.5f - 100.0f;
		pos.y = 300.f;

		//quit text
		ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Quit?");

		//yes button
		ImVec2 pos1;;
		pos1.x = width * 0.5f - 300.0f;
		pos1.y = 500.f;

		ImVec2 p1, p2, p3, p4;
		p1.x = pos1.x;
		p1.y = pos1.y;

		p2.x = pos1.x;
		p2.y = pos1.y + 130.f;

		p3.x = pos1.x + 140.f;
		p3.y = pos1.y + 130.f;

		p4.x = pos1.x + 140.f;
		p4.y = pos1.y;

		ImGui::GetForegroundDrawList()->AddQuadFilled(p1, p2, p3, p4, 0xffffffff);
		ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos1, 0xFF000000, "Yes");

		//no button
		ImVec2 pos2 = pos1;
		pos2.x += 500.0f;

		p1.x = pos2.x;
		p1.y = pos2.y;

		p2.x = pos2.x;
		p2.y = pos2.y + 130.f;

		p3.x = pos2.x + 120.f;
		p3.y = pos2.y + 130.f;

		p4.x = pos2.x + 120.f;
		p4.y = pos2.y;

		ImGui::GetForegroundDrawList()->AddQuadFilled(p1, p2, p3, p4, 0xffffffff);
		ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos2, 0xFF000000, "No");
		break;
	}
	case GameState::Htp:
	{
		auto width = Application::Get().GetWindow().GetWidth();
		auto height = Application::Get().GetWindow().GetHeight();

		ImVec2 pos;
		pos.x = width * 0.5f - 280.0f;
		pos.y = height / 2 - 300.f;

		ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "How To Play");

		pos.x -= 180.f;
		pos.y += 120.f;
		ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Use W A S D to move");
		
		pos.x += 60.f;
		pos.y += 120.f;
		ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Use mouse to aim");
		
		pos.x -= 320.f;
		pos.y += 120.f;
		ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click on left mouse button to shoot");


		//back button
		ImVec2 pos1;
		pos1.x = width * 0.5f - 120.0f;
		pos1.y = 800.f;
		
		ImVec2 p1, p2, p3, p4;
		p1.x = pos1.x;
		p1.y = pos1.y;

		p2.x = pos1.x;
		p2.y = pos1.y + 130.f;

		p3.x = pos1.x + 200.f;
		p3.y = pos1.y + 130.f;

		p4.x = pos1.x + 200.f;
		p4.y = pos1.y;

		ImGui::GetForegroundDrawList()->AddQuadFilled(p1, p2, p3, p4, 0xffffffff);
		ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos1, 0xFF000000, "Back");
		
		break;
	}
	}
}

void Canvas2D::OnEvent(Thomas::Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(TH_BIND_EVENT_FN(Canvas2D::OnWindowResize));
	dispatcher.Dispatch<MouseButtonPressedEvent>(TH_BIND_EVENT_FN(Canvas2D::OnMouseButtonPressed));
	dispatcher.Dispatch<KeyPressedEvent>(TH_BIND_EVENT_FN(Canvas2D::OnKeyPressed));
}

bool Canvas2D::OnMouseButtonPressed(Thomas::MouseButtonPressedEvent& e)
{
	//start button in main menu
	float start_min_x = Application::Get().GetWindow().GetWidth() * 0.5f - 230.0f;
	float start_min_y = 310.f;
	float start_max_x = start_min_x + 465.f;
	float start_max_y = start_min_y + 130.f;
	if (Input::GetMouseX() >= start_min_x && Input::GetMouseY() >= start_min_y &&
		Input::GetMouseX() <= start_max_x && Input::GetMouseY() <= start_max_y && 
		m_State == GameState::MainMenu) {
		bullet_timer += 0.2f;
		start = true;
		m_State = GameState::Play;
	}

	//quit button in main menu
	float mquit_min_x = start_min_x + 10.f;
	float mquit_min_y = start_min_y + 200.f;
	float mquit_max_x = mquit_min_x + 445.f;
	float mquit_max_y = mquit_min_y + 130.f;
	if (Input::GetMouseX() >= mquit_min_x && Input::GetMouseY() >= mquit_min_y &&
		Input::GetMouseX() <= mquit_max_x && Input::GetMouseY() <= mquit_max_y &&
		m_State == GameState::MainMenu) {
		m_State = GameState::Quit;
	}


	//resume button in pause
	float resume_min_x = Application::Get().GetWindow().GetWidth() * 0.5f - 310.0f;
	float resume_min_y = 310.f;
	float resume_max_x = resume_min_x + 600.f;
	float resume_max_y = resume_min_y + 130.f;
	if (Input::GetMouseX() >= resume_min_x && Input::GetMouseY() >= resume_min_y &&
		Input::GetMouseX() <= resume_max_x && Input::GetMouseY() <= resume_max_y &&
		m_State == GameState::Pause) {
		m_State = GameState::Play;
	}

	//how to play button in pause
	float htp_min_x = resume_min_x + 50.f;
	float htp_min_y = resume_min_y + 200.f;
	float htp_max_x = htp_min_x + 510.f;
	float htp_max_y = htp_min_y + 130.f;
	if (Input::GetMouseX() >= htp_min_x && Input::GetMouseY() >= htp_min_y &&
		Input::GetMouseX() <= htp_max_x && Input::GetMouseY() <= htp_max_y &&
		m_State == GameState::Pause) {
		m_State = GameState::Htp;
	}
	
	//quit button in pause
	float pquit_min_x = resume_min_x + 75.f;
	float pquit_min_y = resume_min_y + 400.f;
	float pquit_max_x = pquit_min_x + 445.f;
	float pquit_max_y = pquit_min_y + 130.f;
	if (Input::GetMouseX() >= pquit_min_x && Input::GetMouseY() >= pquit_min_y &&
		Input::GetMouseX() <= pquit_max_x && Input::GetMouseY() <= pquit_max_y &&
		m_State == GameState::Pause) {
		m_State = GameState::Quit;
	}


	//yes button in quit
	float yes_min_x = Application::Get().GetWindow().GetWidth() * 0.5f - 310.0f;
	float yes_min_y = 460.f;
	float yes_max_x = yes_min_x + 140.f;
	float yes_max_y = yes_min_y + 130.f;
	if (Input::GetMouseX() >= yes_min_x && Input::GetMouseY() >= yes_min_y &&
		Input::GetMouseX() <= yes_max_x && Input::GetMouseY() <= yes_max_y &&
		m_State == GameState::Quit) {

		auto entities = m_ActiveScene->GetRegistry()->GetEntities();
		for (auto e : entities)
		{
			Entity entity = { e.first ,m_ActiveScene.get() };
			m_ActiveScene->DestroyEntity(entity);
		}

		Application::Get().Close();
	}

	//no button in quit
	float no_min_x = yes_min_x + 500.f;
	float no_min_y = yes_min_y;
	float no_max_x = no_min_x + 120.f;
	float no_max_y = no_min_y + 130.f;
	if (Input::GetMouseX() >= no_min_x && Input::GetMouseY() >= no_min_y &&
		Input::GetMouseX() <= no_max_x && Input::GetMouseY() <= no_max_y &&
		m_State == GameState::Quit) {
		if (start == false) {
			m_State = GameState::MainMenu;
		}
		else {
			m_State = GameState::Pause;
		}
	}

	//back button in how to play
	float back_min_x = Application::Get().GetWindow().GetWidth() * 0.5f - 130.0f;
	float back_min_y = 760.f;
	float back_max_x = back_min_x + 200.f;
	float back_max_y = back_min_y + 130.f;
	if (Input::GetMouseX() >= back_min_x && Input::GetMouseY() >= back_min_y &&
		Input::GetMouseX() <= back_max_x && Input::GetMouseY() <= back_max_y &&
		m_State == GameState::Htp) {
		m_State = GameState::Pause;
	}


	//shoot bullet
	if (m_State == GameState::Play && bullet_timer <= 0.f) {
		auto bullet = m_ActiveScene->CreateEntity("bullet");

		bullet.AddComponent<Texture>();
		bullet.GetComponent<Texture>().text_file = 1;
		bullet.GetComponent<Texture>().texid = stash.Text_Storage["display.png"];
		bullet.GetComponent<Box_collider>().box_tog = 0;

		bullet.AddComponent<BulletComponent>();

		bullet.GetComponent<Transform>().scaling.x = 0.1f;
		bullet.GetComponent<Transform>().scaling.y = 0.1f;
		bullet.GetComponent<Transform>().translation.x = m_player.GetComponent<Transform>().translation.x;
		bullet.GetComponent<Transform>().translation.y = m_player.GetComponent<Transform>().translation.y;
		bullet.GetComponent<Transform>().rotation = m_player.GetComponent<Transform>().rotation;

		bullet.GetComponent<BulletComponent>().speed = 0.1f;
		bullet.GetComponent<BulletComponent>().time = 1.f;

		if (((Input::GetMouseX() / Application::Get().GetWindow().GetWidth() - 0.5f) * 4) >= 0.f) {
			bullet.GetComponent<BulletComponent>().dir.x = cosf((bullet.GetComponent<Transform>().rotation - 90.f) * PI / 180);
			bullet.GetComponent<BulletComponent>().dir.y = sinf((bullet.GetComponent<Transform>().rotation - 90.f)* PI / 180);
		}
		else if (((Input::GetMouseX() / Application::Get().GetWindow().GetWidth() - 0.5f) * 4) < 0.f) {
			bullet.GetComponent<BulletComponent>().dir.x = -cosf((bullet.GetComponent<Transform>().rotation - 270.f) * PI / 180);
			bullet.GetComponent<BulletComponent>().dir.y = -sinf((bullet.GetComponent<Transform>().rotation - 270.f) * PI / 180);
		}
		bullet_timer += 0.5f;

		/*m_player.GetComponent<AudioComponent>().nChannelId = AEngine.PlaySound(stash.Audio_Storage["death.mp3"], 100.0);
		int test = m_player.GetComponent<AudioComponent>().nChannelId;
		AEngine.PauseChannel(m_player.GetComponent<AudioComponent>().nChannelId);*/


	}

	return false;
}

bool Canvas2D::OnKeyPressed(Thomas::KeyPressedEvent& e) {
	
	if (e.GetKeyCode() == TH_KEY_ESCAPE) {
		if (m_State == GameState::Play) {
			m_State = GameState::Pause;
		}
	}
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

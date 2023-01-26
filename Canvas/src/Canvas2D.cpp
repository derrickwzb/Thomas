/*!*************************************************************************
\file           Canvas2D.cpp
\author         Chen XinPeng
\par DP email:  c.xinpeng@digipen.edu
\par Programming CSD2400 Game project
\date           28/11/2022
\brief			This file contains functions to run the game demo

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************/
#include "Canvas2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GLEW/include/GL/glew.h"
#include "glm/glm.hpp"

#include "Thomas/Scene/Entity.h"
#include "Thomas/Scene/Scene.h"
#include "Thomas/Scene/SceneSerializer.h"
#include "Thomas/Utils/CoreUtils.h"

using namespace Thomas;

static float PI = 3.1415926f;
static float bullet_timer = 0.f;
static bool start = false;
static float player_speed = 1.f;
static bool call_once = false;
static std::string filepath = " ";

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

	//FramebufferSpec fbSpec;
	//fbSpec.Width = 1920;
	//fbSpec.Height = 1080;
	//m_Framebuffer = std::make_shared<Framebuffer>(fbSpec);

	//m_Level.Init();
	m_ActiveScene = std::make_shared<Thomas::Scene>();

	//std::string filepath = FileDialogs::OpenFile("Thomas Scene\0*.json\0");
	//if (!filepath.empty())
	//{
	//	SceneSerializer serializer(m_ActiveScene);
	//	serializer.Deserialize(filepath);
	//}


	//std::string filepath = ("../Assets/Scene/level1.json");
	/*std::string filepath = ("../Assets/Scene/Mainmenu.json");*/
	//std::string filepath = ("../Assets/Scene/Howtoplay2.json");
	//std::string filepath = ("../Assets/Scene/Confirmquit.json");
	//std::string filepath = ("../Assets/Scene/Credits.json");
	filepath = ("../Assets/Scene/Mainmenu.json");
	SceneSerializer serializer(m_ActiveScene);
	serializer.Deserialize(filepath);
	
	FramebufferSpec fbSpec;
	fbSpec.Width = static_cast<uint32_t>(Graphics::cam_stuff.c_width * Graphics::cam_stuff.scaling.y);
	//fbSpec.Height = fbSpec.Width / (Graphics::cam_stuff.c_aspectratio);
	fbSpec.Height = static_cast<uint32_t>(Graphics::cam_stuff.c_height * Graphics::cam_stuff.scaling.y);
	m_Framebuffer = std::make_shared<Framebuffer>(fbSpec);

	std::map<EntityID, Signature> group = m_ActiveScene->GetRegistry()->GetEntities();

	for (auto e : group) {

		Thomas::Entity entity = { e.first, m_ActiveScene->GetScene() };
		//auto& player = entity.GetComponent<ObjectType>();

		//if (player.type == ObjectTypeID::player) {
		//	m_player = entity;
		//}

		auto& data = entity.GetComponent<TagComponent>();
		if (data.tag == "Play Button") {
			m_player = entity;
		}
		if (data.tag == "Background") {
			m_enemy = entity;
		}

		auto& box = entity.AddComponent<Box_collider>();
		box.box_tog = 1; // 1 to show the box
	}

	//Graphics::cam_stuff.translation.x = m_player.GetComponent<Transform>().translation.x;
	//Graphics::cam_stuff.translation.y = m_player.GetComponent<Transform>().translation.y;

	//m_background = m_ActiveScene->CreateEntity("background");

	//m_background.AddComponent<Texture>();
	//m_background.AddComponent<Grid>();
	//m_background.GetComponent<Texture>().text_file = 1;
	//m_background.GetComponent<Texture>().texid = stash.Text_Storage["wallpaper.png"];

	//m_background.GetComponent<Transform>().translation.y = 0;
	//m_background.GetComponent<Transform>().scaling.x = 8.f;
	//m_background.GetComponent<Transform>().scaling.y = 6.f;


	//m_background.GetComponent<Box_collider>().box_tog = 0; // 1 to show the box

	////add player
	//m_player = m_ActiveScene->CreateEntity("player");
	////TH_CORE_INFO("{0}", m_player->GetID());
	//
	//m_player.GetComponent<Transform>().scaling.x = 0.25f;
	//m_player.GetComponent<Transform>().scaling.y = 0.25f;

	//m_player.AddComponent<Texture>();
	//m_player.GetComponent<Texture>().text_file = 1;
	//m_player.GetComponent<Texture>().texid = stash.Text_Storage["Chef_Kay_Top.png"];

	//m_player.GetComponent<Box_collider>().box_trans.scaling.x = 0.25f;
	//m_player.GetComponent<Box_collider>().box_trans.scaling.y = 0.25f;

	//m_player.GetComponent<Box_collider>().box_tog = 0; // 1 to show the box
	//m_player.AddComponent<BoxCollider2D>();
	//m_player.GetComponent<BoxCollider2D>().verticesList.push_back(m_player.GetComponent<Box_collider>().box_trans.global_vertice0);
	//m_player.GetComponent<BoxCollider2D>().verticesList.push_back(m_player.GetComponent<Box_collider>().box_trans.global_vertice1);
	//m_player.GetComponent<BoxCollider2D>().verticesList.push_back(m_player.GetComponent<Box_collider>().box_trans.global_vertice2);
	//m_player.GetComponent<BoxCollider2D>().verticesList.push_back(m_player.GetComponent<Box_collider>().box_trans.global_vertice3);

	////m_player.AddComponent<ParticleComponent>();
	////add player
	//m_player = m_ActiveScene->CreateEntity("player");
	//m_enemy = m_ActiveScene->CreateEntity("enemy");
	//m_enemy2 = m_ActiveScene->CreateEntity("enemy2");
	////TH_CORE_INFO("{0}", m_player->GetID());

	//m_player.GetComponent<Transform>().scaling.x = 0.25f;
	//m_player.GetComponent<Transform>().scaling.y = 0.25f;

	//m_enemy.GetComponent<Transform>().scaling.x = 0.25f;
	//m_enemy.GetComponent<Transform>().scaling.y = 0.25f;

	//m_enemy2.GetComponent<Transform>().scaling.x = 0.25f;
	//m_enemy2.GetComponent<Transform>().scaling.y = 0.25f;

	//m_player.AddComponent<Texture>();
	//m_player.GetComponent<Texture>().text_file = 1;
	//m_player.GetComponent<Texture>().texid = stash.Text_Storage["Chef_Kay_Top.png"];

	//m_enemy.AddComponent<Texture>();
	//m_enemy.GetComponent<Texture>().text_file = 1;
	//m_enemy.GetComponent<Texture>().texid = stash.Text_Storage["Chef_Kay_Top.png"];

	//m_enemy2.AddComponent<Texture>();
	//m_enemy2.GetComponent<Texture>().text_file = 1;
	//m_enemy2.GetComponent<Texture>().texid = stash.Text_Storage["Chef_Kay_Top.png"];




	//m_player.GetComponent<Box_collider>().box_trans.scaling.x = 0.25f;
	//m_player.GetComponent<Box_collider>().box_trans.scaling.y = 0.25f;

	//m_enemy.GetComponent<Box_collider>().box_trans.scaling.x = 0.25f;
	//m_enemy.GetComponent<Box_collider>().box_trans.scaling.y = 0.25f;
	//m_enemy.GetComponent<Transform>().translation.x = -2.f;
	//m_enemy.GetComponent<Transform>().translation.y = -2.f;

	//m_enemy2.GetComponent<Box_collider>().box_trans.scaling.x = 0.25f;
	//m_enemy2.GetComponent<Box_collider>().box_trans.scaling.y = 0.25f;
	//m_enemy2.GetComponent<Transform>().translation.x = -2.f;
	//m_enemy2.GetComponent<Transform>().translation.y = 2.f;


	//m_player.GetComponent<Box_collider>().box_tog = 1; // 1 to show the box
	//m_player.AddComponent<BoxCollider2D>();
	//m_player.GetComponent<BoxCollider2D>().verticesList.push_back(m_player.GetComponent<Box_collider>().box_trans.global_vertice0);
	//m_player.GetComponent<BoxCollider2D>().verticesList.push_back(m_player.GetComponent<Box_collider>().box_trans.global_vertice1);
	//m_player.GetComponent<BoxCollider2D>().verticesList.push_back(m_player.GetComponent<Box_collider>().box_trans.global_vertice2);
	//m_player.GetComponent<BoxCollider2D>().verticesList.push_back(m_player.GetComponent<Box_collider>().box_trans.global_vertice3);



	//m_enemy.GetComponent<Box_collider>().box_tog = 1; // 1 to show the box
	//m_enemy.AddComponent<BoxCollider2D>();
	//m_enemy.GetComponent<BoxCollider2D>().verticesList.push_back(m_enemy.GetComponent<Box_collider>().box_trans.global_vertice0);
	//m_enemy.GetComponent<BoxCollider2D>().verticesList.push_back(m_enemy.GetComponent<Box_collider>().box_trans.global_vertice1);
	//m_enemy.GetComponent<BoxCollider2D>().verticesList.push_back(m_enemy.GetComponent<Box_collider>().box_trans.global_vertice2);
	//m_enemy.GetComponent<BoxCollider2D>().verticesList.push_back(m_enemy.GetComponent<Box_collider>().box_trans.global_vertice3);


	//m_enemy.GetComponent<Box_collider>().box_trans.translation.x = -2.f;
	//m_enemy.GetComponent<Box_collider>().box_trans.translation.y = -2.f;


	//m_enemy2.GetComponent<Box_collider>().box_tog = 1; // 1 to show the box
	//m_enemy2.AddComponent<BoxCollider2D>();
	//m_enemy2.GetComponent<BoxCollider2D>().verticesList.push_back(m_enemy2.GetComponent<Box_collider>().box_trans.global_vertice0);
	//m_enemy2.GetComponent<BoxCollider2D>().verticesList.push_back(m_enemy2.GetComponent<Box_collider>().box_trans.global_vertice1);
	//m_enemy2.GetComponent<BoxCollider2D>().verticesList.push_back(m_enemy2.GetComponent<Box_collider>().box_trans.global_vertice2);
	//m_enemy2.GetComponent<BoxCollider2D>().verticesList.push_back(m_enemy2.GetComponent<Box_collider>().box_trans.global_vertice3);

	//m_enemy2.GetComponent<Box_collider>().box_trans.translation.x = -2.f;
	//m_enemy2.GetComponent<Box_collider>().box_trans.translation.y = -2.f;

	//m_enemy.AddComponent<AStarPathfindingAgent>();
	//m_enemy.GetComponent<AStarPathfindingAgent>().target = &(m_player.GetComponent<Transform>());


	//m_enemy2.AddComponent<AStarPathfindingAgent>();
	//m_enemy2.GetComponent<AStarPathfindingAgent>().target = &(m_player.GetComponent<Transform>());
	////m_player.AddComponent<ParticleComponent>();

	////add tables
	//auto table = m_ActiveScene->CreateEntity("table");

	//table.GetComponent<Transform>().translation.y = 0.8f;
	//table.GetComponent<Transform>().scaling.x = 1.f;
	//table.GetComponent<Transform>().scaling.y = 1.f;

	//table.AddComponent<Texture>();
	//table.GetComponent<Texture>().text_file = 1;
	//table.GetComponent<Texture>().texid = stash.Text_Storage["table5.png"];

	//table.GetComponent<Box_collider>().box_tog = 0; // 1 to show the box
	//table.GetComponent<Box_collider>().box_trans.translation.t = table.GetComponent<Transform>().translation.y;
	//table.GetComponent<Box_collider>().box_trans.scaling.x = 0.5f;
	//table.GetComponent<Box_collider>().box_trans.scaling.y = 0.5f;

	//table.AddComponent<BoxCollider2D>();
	//table.GetComponent<BoxCollider2D>().verticesList.push_back(table.GetComponent<Box_collider>().box_trans.global_vertice0);
	//table.GetComponent<BoxCollider2D>().verticesList.push_back(table.GetComponent<Box_collider>().box_trans.global_vertice1);
	//table.GetComponent<BoxCollider2D>().verticesList.push_back(table.GetComponent<Box_collider>().box_trans.global_vertice2);
	//table.GetComponent<BoxCollider2D>().verticesList.push_back(table.GetComponent<Box_collider>().box_trans.global_vertice3);
	//
	ImGuiIO io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("assets/OpenSans-Regular.ttf", 120.0f);

	////Audio Component
	//m_player.AddComponent<AudioComponent>();
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
			Graphics::cam_stuff.Camera2D_Update(m_Framebuffer->GetSpec().Width, m_Framebuffer->GetSpec().Height);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_ActiveScene->OnUpdate(ts);
			break;
		}
		case GameState::Play:
		{
			Graphics::cam_stuff.Camera2D_Update(m_Framebuffer->GetSpec().Width, m_Framebuffer->GetSpec().Height);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_ActiveScene->OnUpdate(ts);
			break;
		}
		case GameState::Pause:
		{
			Graphics::cam_stuff.Camera2D_Update(m_Framebuffer->GetSpec().Width, m_Framebuffer->GetSpec().Height);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_ActiveScene->OnUpdate(ts);
			break;
		}
		case GameState::Quit:
		{
			Graphics::cam_stuff.Camera2D_Update(m_Framebuffer->GetSpec().Width, m_Framebuffer->GetSpec().Height);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_ActiveScene->OnUpdate(ts);
			break;
		}
		case GameState::Htp:
		{
			Graphics::cam_stuff.Camera2D_Update(m_Framebuffer->GetSpec().Width, m_Framebuffer->GetSpec().Height);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_ActiveScene->OnUpdate(ts);
			break;
		}
	}
}

void Canvas2D::OnImGuiRender()
{
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
	std::map<EntityID, Signature> group = m_ActiveScene->GetRegistry()->GetEntities();
	for (auto& e : group) {
		if (m_ActiveScene->GetRegistry()->HasComponent<TagComponent>(e.first)) {
			Entity objs = { e.first, m_ActiveScene.get() };
			auto& name_data = objs.GetComponent<TagComponent>();
			
			//auto& trans_stuff = objs.GetComponent<Transform>();
			//auto& box_stuff = objs.GetComponent<Box_collider>();
	//		trans_stuff.minmax_screen(m_Framebuffer->GetSpec().Width, m_Framebuffer->GetSpec().Height);

	//		// Collision check between the on_screen mouse cursor and the on_screen objects
	//		if ((Viewport_CursX > trans_stuff.screen_min.x && Viewport_CursX<trans_stuff.screen_max.x && Viewport_CursY>trans_stuff.screen_min.y && Viewport_CursY < trans_stuff.screen_max.y) && Input::IsMouseButtonPressed(0) && objs.GetID() != 0) {
	//			++Graphics::obj_counter;
	//			if (Graphics::obj_counter == 1) {
	//				Graphics::sel = objs.GetID();
	//				Graphics::sel_layer = trans_stuff.z_axis;
	//				//Entity e = { objs.GetID() , m_ActiveScene.get() };
	//				//m_SceneHierarchyPanel.GetSelection() = e;
	//				Graphics::obj_clicked = true;
	//			}
	//			else {
	//				if (trans_stuff.z_axis < Graphics::sel_layer) {
	//					Graphics::sel = objs.GetID();
	//					Graphics::sel_layer = trans_stuff.z_axis;
	//					//Entity e = { objs.GetID() , m_ActiveScene.get() };
	//					//m_SceneHierarchyPanel.GetSelection() = e;
	//					Graphics::obj_clicked = true;
	//				}
	//			}
	//			std::cout << "Items: " << Graphics::obj_clicked << std::endl;
	//		}
	//		//if (objs.GetID() == Graphics::sel) {
	//		//	// Upon clicking, game object follows mouse cursor
	//		//	if ((Graphics::obj_clicked != 0) && Graphics::sel == objs.GetID() && trans_stuff.mouse_following == FALSE) {
	//		//		glm::vec2 move = glm::vec2(Viewport_CursX, Viewport_CursY);
	//		//		glm::vec2 diff_dist = glm::vec2(trans_stuff.translation.x - box_stuff.box_trans.translation.x, trans_stuff.translation.y - box_stuff.box_trans.translation.y);

	//		//		trans_stuff.translation = trans_stuff.world_to_screen(move, m_ViewportSize);
	//		//		box_stuff.box_trans.translation.x = trans_stuff.translation.x - diff_dist.x;
	//		//		box_stuff.box_trans.translation.y = trans_stuff.translation.y - diff_dist.y;
	//		//	}
	//		//}
	//		if (!Input::IsMouseButtonPressed(0)) {
	//			Graphics::obj_clicked = false;
	//			Graphics::obj_counter = 0;
	//		}
	//	}
	//}

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
		std::string filepath = ("../Assets/Scene/Howtoplay2.json");
		SceneSerializer serializer(m_ActiveScene);
		serializer.Deserialize(filepath);
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


	////shoot bullet
	//if (m_State == GameState::Play && bullet_timer <= 0.f) {
	//	auto bullet = m_ActiveScene->CreateEntity("bullet");

	//	bullet.AddComponent<Texture>();
	//	bullet.GetComponent<Texture>().text_file = 1;
	//	bullet.GetComponent<Texture>().texid = stash.Text_Storage["display.png"];
	//	bullet.GetComponent<Box_collider>().box_tog = 0;

	//	bullet.AddComponent<BulletComponent>();

	//	bullet.GetComponent<Transform>().scaling.x = 0.3f;
	//	bullet.GetComponent<Transform>().scaling.y = 0.3f;
	//	bullet.GetComponent<Transform>().translation.x = m_player.GetComponent<Transform>().translation.x;
	//	bullet.GetComponent<Transform>().translation.y = m_player.GetComponent<Transform>().translation.y;
	//	bullet.GetComponent<Transform>().rotation = m_player.GetComponent<Transform>().rotation;

	//	bullet.AddComponent<ObjectType>();
	//	bullet.GetComponent<ObjectType>().type = ObjectTypeID::bullet;

	//	auto& box = bullet.GetComponent<Box_collider>();
	//	auto& boxCollider = bullet.AddComponent<BoxCollider2D>();
	//	auto& data = bullet.AddComponent<RigidBody>();
	//	boxCollider.verticesList.push_back(box.box_trans.global_vertice0);
	//	boxCollider.verticesList.push_back(box.box_trans.global_vertice1);
	//	boxCollider.verticesList.push_back(box.box_trans.global_vertice2);
	//	boxCollider.verticesList.push_back(box.box_trans.global_vertice3);

	//	bullet.GetComponent<BulletComponent>().speed = 0.1f;
	//	bullet.GetComponent<BulletComponent>().time = 1.f;

	//	if (((Input::GetMouseX() / Application::Get().GetWindow().GetWidth() - 0.5f) * 4) >= 0.f) {
	//		bullet.GetComponent<BulletComponent>().dir.x = cosf((bullet.GetComponent<Transform>().rotation - 90.f) * PI / 180);
	//		bullet.GetComponent<BulletComponent>().dir.y = sinf((bullet.GetComponent<Transform>().rotation - 90.f)* PI / 180);
	//	}
	//	else if (((Input::GetMouseX() / Application::Get().GetWindow().GetWidth() - 0.5f) * 4) < 0.f) {
	//		bullet.GetComponent<BulletComponent>().dir.x = -cosf((bullet.GetComponent<Transform>().rotation - 270.f) * PI / 180);
	//		bullet.GetComponent<BulletComponent>().dir.y = -sinf((bullet.GetComponent<Transform>().rotation - 270.f) * PI / 180);
	//	}
	//	bullet_timer += 0.5f;

	//	/*m_player.GetComponent<AudioComponent>().nChannelId = AEngine.PlaySound(stash.Audio_Storage["death.mp3"], 100.0);
	//	int test = m_player.GetComponent<AudioComponent>().nChannelId;
	//	AEngine.PauseChannel(m_player.GetComponent<AudioComponent>().nChannelId);*/


	//}

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
}

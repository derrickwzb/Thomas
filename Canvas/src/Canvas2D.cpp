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
}

void Canvas2D::OnAttach()
{
	m_ActiveScene = std::make_shared<Thomas::Scene>();

	filepath = ("../Assets/Scene/Mainmenu.json");
	SceneSerializer serializer(m_ActiveScene);
	serializer.Deserialize(filepath);
	
	FramebufferSpec fbSpec;
	fbSpec.Width = static_cast<uint32_t>(Graphics::cam_stuff.c_width * Graphics::cam_stuff.scaling.y);
	fbSpec.Height = static_cast<uint32_t>(Graphics::cam_stuff.c_height * Graphics::cam_stuff.scaling.y);
	m_Framebuffer = std::make_shared<Framebuffer>(fbSpec);

	std::map<EntityID, Signature> group = m_ActiveScene->GetRegistry()->GetEntities();

	for (auto e : group) {

		Thomas::Entity entity = { e.first, m_ActiveScene->GetScene() };
		auto& data = entity.GetComponent<TagComponent>();
		if (data.tag == "Play Button") {
			m_player = entity;
		}
		if (data.tag == "Background") {
			m_enemy = entity;
		}
		auto& box = entity.AddComponent<Box_collider>();
		box.box_tog = 0; // 1 to show the box
	}

	//auto& trans_stuff = m_enemy.GetComponent<Transform>();

	//glm::vec2 move = glm::vec2(Viewport_CursX, Viewport_CursY);
	////trans_stuff.translation = trans_stuff.world_to_screen(move);
	//glm::vec2 temp_check = trans_stuff.screen_to_world(trans_stuff.translation);


	//float Viewport_X, Viewport_Y;
	////Viewport_X = ((Input::GetMouseX() / Application::Get().GetWindow().GetWidth() - 0.5f) * 4);
	////Viewport_Y = -((Input::GetMouseY() / Application::Get().GetWindow().GetHeight() - 0.5f) * 2);

	//Viewport_X = ((Input::GetMouseX() / Application::Get().GetWindow().GetWidth() * 2) - 1);
	//Viewport_Y = ((Input::GetMouseY() / Application::Get().GetWindow().GetHeight() * 2) - 1);

	//std::cout << Viewport_X << ", " << Viewport_Y << " temp,\n";



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
	/*ImGuiIO io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("assets/OpenSans-Regular.ttf", 120.0f);*/

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
		case GameState::Level1:
		{
			

			Graphics::cam_stuff.Camera2D_Update(m_Framebuffer->GetSpec().Width, m_Framebuffer->GetSpec().Height);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_ActiveScene->OnUpdate(ts);
			break;
		}
		case GameState::Level2:
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
		case GameState::Htp1:
		{
			Graphics::cam_stuff.Camera2D_Update(m_Framebuffer->GetSpec().Width, m_Framebuffer->GetSpec().Height);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_ActiveScene->OnUpdate(ts);
			break;
		}
		case GameState::Htp2:
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
	// GameMouse, Origin at the center
	float GameMouse_X = Input::GetMouseX() - (Graphics::width / 2.f);
	float GameMouse_Y = -(Input::GetMouseY() - (Graphics::height / 2.f));

	std::map<EntityID, Signature> group = m_ActiveScene->GetRegistry()->GetEntities();
	for (auto& e : group) {
		if (m_ActiveScene->GetRegistry()->HasComponent<TagComponent>(e.first)) {
			Entity objs = { e.first, m_ActiveScene.get() };
			auto& name_data = objs.GetComponent<TagComponent>();
			auto& trans_data = objs.GetComponent<Transform>();
			switch (m_State) {
			case GameState::MainMenu: {
				if (name_data.tag == "Play_Button") {
					if (MouseCollisionChecked(GameMouse_X, GameMouse_Y, trans_data.global_min, trans_data.global_max)){
						std::cout << "PLAY" << std::endl;
						start = true;
						m_State = GameState::Level1;
						std::string filepath = ("../Assets/Scene/Level1.json");
						SceneSerializer serializer(m_ActiveScene);
						serializer.Deserialize(filepath);
					}
				}
				if (name_data.tag == "Credits_Button") {
					if (MouseCollisionChecked(GameMouse_X, GameMouse_Y, trans_data.global_min, trans_data.global_max)) {
						std::cout << "Credits" << std::endl;
						m_State = GameState::Credit;
						std::string filepath = ("../Assets/Scene/Credits.json");
						SceneSerializer serializer(m_ActiveScene);
						serializer.Deserialize(filepath);
					}
				}
				if (name_data.tag == "How_To_Play_Button") {
					if (MouseCollisionChecked(GameMouse_X, GameMouse_Y, trans_data.global_min, trans_data.global_max)) {
						std::cout << "How To Play" << std::endl;
						m_State = GameState::Htp1;
						std::string filepath = ("../Assets/Scene/Howtoplay1.json");
						SceneSerializer serializer(m_ActiveScene);
						serializer.Deserialize(filepath);
					}
				}
				if (name_data.tag == "Exit_Button") {
					if (MouseCollisionChecked(GameMouse_X, GameMouse_Y, trans_data.global_min, trans_data.global_max)) {
						std::cout << "Exit" << std::endl;
						m_State = GameState::Quit;
						std::string filepath = ("../Assets/Scene/Confirmquit.json");
						SceneSerializer serializer(m_ActiveScene);
						serializer.Deserialize(filepath);
					}
				}
				break;
			}
			case GameState::Level1: {

				break;
			}

			case GameState::Pause: {
				break;
			}
			case GameState::Quit: {
				break;
			}
			case GameState::Htp1: {
				if (name_data.tag == "Right_Button") {
					if (MouseCollisionChecked(GameMouse_X, GameMouse_Y, trans_data.global_min, trans_data.global_max)) {
						std::cout << "Next" << std::endl;
						m_State = GameState::Htp2;
						std::string filepath = ("../Assets/Scene/Howtoplay2.json");
						SceneSerializer serializer(m_ActiveScene);
						serializer.Deserialize(filepath);
					}
				}
				if (name_data.tag == "Back_Button") {
					if (MouseCollisionChecked(GameMouse_X, GameMouse_Y, trans_data.global_min, trans_data.global_max)) {
						std::cout << "Back" << std::endl;
						m_State = GameState::MainMenu;
						std::string filepath = ("../Assets/Scene/Mainmenu.json");
						SceneSerializer serializer(m_ActiveScene);
						serializer.Deserialize(filepath);
					}
				}
				break;
			}
			case GameState::Htp2: {
				if (name_data.tag == "Left_Button") {
					if (MouseCollisionChecked(GameMouse_X, GameMouse_Y, trans_data.global_min, trans_data.global_max)) {
						std::cout << "Previous" << std::endl;
						m_State = GameState::Htp1;
						std::string filepath = ("../Assets/Scene/Howtoplay1.json");
						SceneSerializer serializer(m_ActiveScene);
						serializer.Deserialize(filepath);
					}
				}
				if (name_data.tag == "Back_Button") {
					if (MouseCollisionChecked(GameMouse_X, GameMouse_Y, trans_data.global_min, trans_data.global_max)) {
						std::cout << "Back" << std::endl;
						m_State = GameState::MainMenu;
						std::string filepath = ("../Assets/Scene/Mainmenu.json");
						SceneSerializer serializer(m_ActiveScene);
						serializer.Deserialize(filepath);
					}
				}
				break;
			}
			}
		}
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
		m_State == GameState::Htp1) {
		m_State = GameState::Pause;
	}

	return false;
}

bool Canvas2D::OnKeyPressed(Thomas::KeyPressedEvent& e) {
	if (e.GetKeyCode() == TH_KEY_ESCAPE) {
		if (m_State == GameState::Level1 || m_State == GameState::Level2) {
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

bool Canvas2D::MouseCollisionChecked(float Cursor_X, float Cursor_Y, glm::vec2 min_pos, glm::vec2 max_pos){
	if (Cursor_X >= min_pos.x && Cursor_Y >= min_pos.y && Cursor_X <= max_pos.x && Cursor_Y <= max_pos.y)
		return true;
	else
		return false;
}

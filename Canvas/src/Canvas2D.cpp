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
float Cursor_X{};
float Cursor_Y{};

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
	fbSpec.Width = static_cast<uint32_t>(Graphics::width * Graphics::cam_stuff.scaling.y);
	fbSpec.Height = static_cast<uint32_t>(Graphics::height * Graphics::cam_stuff.scaling.y);
	m_Framebuffer = std::make_shared<Framebuffer>(fbSpec);

	Graphics::cam_stuff.Camera2D_Init();
	std::cout << Graphics::cam_stuff.c_width << "     "  << Graphics::cam_stuff.c_height << std::endl;
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
	Cursor_X = Input::GetMouseX() - Graphics::width / 2;
	Cursor_Y = -(Input::GetMouseY() - Graphics::height / 2);
	Graphics::cam_stuff.Camera2D_Update(m_Framebuffer->GetSpec().Width, m_Framebuffer->GetSpec().Height);
	std::map<EntityID, Signature> group = m_ActiveScene->GetRegistry()->GetEntities();
	for (auto& e : group) {
		Entity objs = { e.first, m_ActiveScene.get() };
		if (m_ActiveScene->GetRegistry()->HasComponent<TagComponent>(e.first)) {
			auto& name_data = objs.GetComponent<TagComponent>();
			auto& trans_data = objs.GetComponent<Transform>();
			auto& box_data = objs.GetComponent<Box_collider>();
			switch (m_State) {
			case GameState::Level1: {
				//Entity enemy = m_ActiveScene->CreateEnemyEntity();
				/*enemy.GetComponent<Transform>().translation.x = -2.5f;
				enemy.GetComponent<Transform>().translation.y = -2.5f;*/
				if (name_data.tag == "Player") {
					m_player = objs;
					// Sync the Camera with the Player
					Graphics::cam_stuff.translation.x = trans_data.translation.x / (4.f * Graphics::cam_stuff.ar);
					Graphics::cam_stuff.translation.y = -(trans_data.translation.y / 4.f);
					// Mouse Following
					glm::vec2 A = glm::vec2(0, 1.f);
					glm::vec2 B = glm::vec2(Cursor_X, Cursor_Y);
					B.x -= trans_data.translation.x;
					B.y -= trans_data.translation.y;
					float dot_product = glm::dot(A, B);
					float angle = acos(dot_product / (glm::length(A) * glm::length(B)));
					float degree = (angle / static_cast<float>(M_PI)) * 180.f;
					if ((B.x + trans_data.translation.x) < trans_data.translation.x)
						degree *= -1;
					trans_data.rotation = degree;
					Graphics::cam_stuff.rotation = (degree * -1.f);
					//KeyPress
					if (Input::IsKeyPressed(TH_KEY_W)){
						trans_data.translation.y -= 0.0034f;
						box_data.box_trans.translation.y -= 0.0034f;
					}
					if (Input::IsKeyPressed(TH_KEY_S)) {
						trans_data.translation.y += 0.0034f;
						box_data.box_trans.translation.y += 0.0034f;
					}
					if (Input::IsKeyPressed(TH_KEY_A)) {
						trans_data.translation.x -= 0.0034f;
						box_data.box_trans.translation.x -= 0.0034f;
					}
					if (Input::IsKeyPressed(TH_KEY_D)) {
						trans_data.translation.x += 0.0034f;
						box_data.box_trans.translation.x += 0.0034f;
					}
				}
				
				if (bullet_timer >= 0.f) {
					bullet_timer -= ts;
				}

				if (name_data.tag == "Enemy")
				{
					objs.GetComponent<AStarPathfindingAgent>().pathfindingEnabled = true;
				}
				
				break;
			}
			case GameState::Level2: {
				if (name_data.tag == "Player") {
					// Sync the Camera with the Player
					Graphics::cam_stuff.translation.x = trans_data.translation.x / (4.f * Graphics::cam_stuff.ar);
					Graphics::cam_stuff.translation.y = -(trans_data.translation.y / 4.f);
					// Mouse Following
					glm::vec2 A = glm::vec2(0, 1.f);
					glm::vec2 B = glm::vec2(Cursor_X, Cursor_Y);
					B.x -= trans_data.translation.x;
					B.y -= trans_data.translation.y;
					float dot_product = glm::dot(A, B);
					float angle = acos(dot_product / (glm::length(A) * glm::length(B)));
					float degree = (angle / static_cast<float>(M_PI)) * 180.f;
					if ((B.x + trans_data.translation.x) < trans_data.translation.x)
						degree *= -1;
					trans_data.rotation = degree;
					Graphics::cam_stuff.rotation = (degree * -1.f);
					//KeyPress
					if (Input::IsKeyPressed(TH_KEY_W)) {
						trans_data.translation.y -= 0.0034f;
						box_data.box_trans.translation.y -= 0.0034f;
					}
					if (Input::IsKeyPressed(TH_KEY_S)) {
						trans_data.translation.y += 0.0034f;
						box_data.box_trans.translation.y += 0.0034f;
					}
					if (Input::IsKeyPressed(TH_KEY_A)) {
						trans_data.translation.x -= 0.0034f;
						box_data.box_trans.translation.x -= 0.0034f;
					}
					if (Input::IsKeyPressed(TH_KEY_D)) {
						trans_data.translation.x += 0.0034f;
						box_data.box_trans.translation.x += 0.0034f;
					}
				}
				break;
			}
			}
		}
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_ActiveScene->OnUpdate(ts);
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
						bullet_timer += 0.2f;
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
			case GameState::Credit: {
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
			case GameState::Level1: {

				//shoot bullet
				if (bullet_timer <= 0.f) {
					auto& bullet = m_ActiveScene->CreateEntity("bullet");

					auto& trans = bullet.GetComponent<Transform>();
					trans.scaling.x = 0.3f;
					trans.scaling.y = 0.3f;
					trans.translation.x = m_player.GetComponent<Transform>().translation.x;
					trans.translation.y = m_player.GetComponent<Transform>().translation.y;
					trans.rotation = m_player.GetComponent<Transform>().rotation;

					auto& tex = bullet.AddComponent<Texture>();
					tex.texid = 1;
					//tex.text_file = 132;
					//tex.filename = "rotten_core_glow_1.png";
					
					auto& box = bullet.GetComponent<Box_collider>();
					box.box_tog = 0;
					box.box_trans.scaling.x = 0.2f;
					box.box_trans.scaling.y = 0.2f;

					auto& bullet_data = bullet.AddComponent<BulletComponent>();
					bullet_data.speed = 0.1f;
					bullet_data.time = 1.f;

					if (((Input::GetMouseX() / Application::Get().GetWindow().GetWidth() - 0.5f) * 4) >= 0.f) {
						bullet_data.dir.x = cosf((trans.rotation - 90.f) * PI / 180);
						bullet_data.dir.y = sinf((trans.rotation - 90.f) * PI / 180);
					}
					else if (((Input::GetMouseX() / Application::Get().GetWindow().GetWidth() - 0.5f) * 4) < 0.f) {
						bullet_data.dir.x = -cosf((trans.rotation - 270.f) * PI / 180);
						bullet_data.dir.y = -sinf((trans.rotation - 270.f) * PI / 180);
					}
					bullet_timer += 0.5f;
					/*m_player.GetComponent<AudioComponent>().nChannelId = AEngine.PlaySound(stash.Audio_Storage["death.mp3"], 100.0);
					int test = m_player.GetComponent<AudioComponent>().nChannelId;
					AEngine.PauseChannel(m_player.GetComponent<AudioComponent>().nChannelId);*/
				}

				break;
			}
			case GameState::Pause: {
				break;
			}
			case GameState::Quit: {
				if (name_data.tag == "Yes_Button") {
					if (MouseCollisionChecked(GameMouse_X, GameMouse_Y, trans_data.global_min, trans_data.global_max)) {
						auto entities = m_ActiveScene->GetRegistry()->GetEntities();
						for (auto e : entities)
						{
							Entity entity = { e.first ,m_ActiveScene.get() };
							m_ActiveScene->DestroyEntity(entity);
						}
						Application::Get().Close();
					}
				}
				if (name_data.tag == "No_Button") {
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
	////yes button in quit
	//float yes_min_x = Application::Get().GetWindow().GetWidth() * 0.5f - 310.0f;
	//float yes_min_y = 460.f;
	//float yes_max_x = yes_min_x + 140.f;
	//float yes_max_y = yes_min_y + 130.f;
	//if (Input::GetMouseX() >= yes_min_x && Input::GetMouseY() >= yes_min_y &&
	//	Input::GetMouseX() <= yes_max_x && Input::GetMouseY() <= yes_max_y &&
	//	m_State == GameState::Quit) {

	//	
	//}

	////no button in quit
	//float no_min_x = yes_min_x + 500.f;
	//float no_min_y = yes_min_y;
	//float no_max_x = no_min_x + 120.f;
	//float no_max_y = no_min_y + 130.f;
	//if (Input::GetMouseX() >= no_min_x && Input::GetMouseY() >= no_min_y &&
	//	Input::GetMouseX() <= no_max_x && Input::GetMouseY() <= no_max_y &&
	//	m_State == GameState::Quit) {
	//	if (start == false) {
	//		m_State = GameState::MainMenu;
	//	}
	//	else {
	//		m_State = GameState::Pause;
	//	}
	//}

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


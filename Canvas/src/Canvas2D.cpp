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

int player_Health					= 5;
static bool start					= false;
static float player_speed		= 1.f;
static bool call_once			= false;
static std::string filepath		= " ";
float Cursor_X{};
float Cursor_Y{};
static float bullet_timer{};
float Cut_Scene_timer{};
int Scene_no{};
float Gameover_timer{};
float Win_timer{};

Canvas2D::Canvas2D()
	: Layer("Canvas2D")
{
}

void Canvas2D::OnAttach()
{	
	
	m_ActiveScene = std::make_shared<Thomas::Scene>();	
	filepath = ("../Assets/Scene/Mainmenu.json");
	SceneSerializer serializer(m_ActiveScene.get());
	serializer.Deserialize(filepath);
	
	FramebufferSpec fbSpec;
	fbSpec.Width = static_cast<uint32_t>(Graphics::width * Graphics::cam_stuff.scaling.y);
	fbSpec.Height = static_cast<uint32_t>(Graphics::height * Graphics::cam_stuff.scaling.y);
	m_Framebuffer = std::make_shared<Framebuffer>(fbSpec);

	std::map<EntityID, Signature> group = m_ActiveScene->GetRegistry()->GetEntities();
	ScriptEngine::OnRuntimeStart(m_ActiveScene.get());
}

void Canvas2D::OnDetach()
{
}

void Canvas2D::OnUpdate(Thomas::Timestep ts)
{
	Cursor_X = Input::GetMouseX() - Graphics::width / 2;
	Cursor_Y = -(Input::GetMouseY() - Graphics::height / 2);
	Graphics::cam_stuff.Camera2D_Update();

	std::map<EntityID, Signature> group = m_ActiveScene->GetRegistry()->GetEntities();
	for (auto& e : group) {
		Entity objs = { e.first, m_ActiveScene.get() };
		if (m_ActiveScene->GetRegistry()->HasComponent<TagComponent>(e.first)) {
			auto& name_data = objs.GetComponent<TagComponent>();
			auto& trans_data = objs.GetComponent<Transform>();
			auto& box_data = objs.GetComponent<Box_collider>();
			switch (m_State) {
			case GameState::MainMenu: {
				//change texture when hover
				if (name_data.tag == "Play_Button") {
					if (MouseCollisionChecked(Cursor_X, Cursor_Y, trans_data.global_min, trans_data.global_max)) {
						if (objs.GetComponent<Texture>().button_hover == false) {
							objs.GetComponent<Texture>().texid -= 1;
							objs.GetComponent<Texture>().button_hover = true;
						}
					}
					else {
						if (objs.GetComponent<Texture>().button_hover == true) {
							objs.GetComponent<Texture>().texid += 1;
							objs.GetComponent<Texture>().button_hover = false;
						}
					}
				}
				//change texture when hover
				if (name_data.tag == "Credits_Button") {
					if (MouseCollisionChecked(Cursor_X, Cursor_Y, trans_data.global_min, trans_data.global_max)) {
						if (objs.GetComponent<Texture>().button_hover == false) {
							objs.GetComponent<Texture>().texid -= 1;
							objs.GetComponent<Texture>().button_hover = true;
						}
					}
					else {
						if (objs.GetComponent<Texture>().button_hover == true) {
							objs.GetComponent<Texture>().texid += 1;
							objs.GetComponent<Texture>().button_hover = false;
						}
					}
				}
				//change texture when hover
				if (name_data.tag == "How_To_Play_Button") {
					if (MouseCollisionChecked(Cursor_X, Cursor_Y, trans_data.global_min, trans_data.global_max)) {
						if (objs.GetComponent<Texture>().button_hover == false) {
							objs.GetComponent<Texture>().texid -= 1;
							objs.GetComponent<Texture>().button_hover = true;
						}
					}
					else {
						if (objs.GetComponent<Texture>().button_hover == true) {
							objs.GetComponent<Texture>().texid += 1;
							objs.GetComponent<Texture>().button_hover = false;
						}
					}
				}
				//change texture when hover
				if (name_data.tag == "Exit_Button") {
					if (MouseCollisionChecked(Cursor_X, Cursor_Y, trans_data.global_min, trans_data.global_max)) {
						if (objs.GetComponent<Texture>().button_hover == false) {
							objs.GetComponent<Texture>().texid -= 1;
							objs.GetComponent<Texture>().button_hover = true;
						}
					}
					else {
						if (objs.GetComponent<Texture>().button_hover == true) {
							objs.GetComponent<Texture>().texid += 1;
							objs.GetComponent<Texture>().button_hover = false;
						}
					}
				}

				break;
			}
			case GameState::Credit1: {
				//change texture when hover
				if (name_data.tag == "Back_Button") {
					if (MouseCollisionChecked(Cursor_X, Cursor_Y, trans_data.global_min, trans_data.global_max)) {
						if (objs.GetComponent<Texture>().button_hover == false) {
							objs.GetComponent<Texture>().texid -= 1;
							objs.GetComponent<Texture>().button_hover = true;
						}
					}
					else {
						if (objs.GetComponent<Texture>().button_hover == true) {
							objs.GetComponent<Texture>().texid += 1;
							objs.GetComponent<Texture>().button_hover = false;
						}
					}
				}
				break;
			}
			case GameState::Credit2: {
				//change texture when hover
				if (name_data.tag == "Back_Button") {
					if (MouseCollisionChecked(Cursor_X, Cursor_Y, trans_data.global_min, trans_data.global_max)) {
						if (objs.GetComponent<Texture>().button_hover == false) {
							objs.GetComponent<Texture>().texid -= 1;
							objs.GetComponent<Texture>().button_hover = true;
						}
					}
					else {
						if (objs.GetComponent<Texture>().button_hover == true) {
							objs.GetComponent<Texture>().texid += 1;
							objs.GetComponent<Texture>().button_hover = false;
						}
					}
				}
				break;
			}
			case GameState::Htp1: {
				//change texture when hover
				if (name_data.tag == "Back_Button") {
					if (MouseCollisionChecked(Cursor_X, Cursor_Y, trans_data.global_min, trans_data.global_max)) {
						if (objs.GetComponent<Texture>().button_hover == false) {
							objs.GetComponent<Texture>().texid -= 1;
							objs.GetComponent<Texture>().button_hover = true;
						}
					}
					else {
						if (objs.GetComponent<Texture>().button_hover == true) {
							objs.GetComponent<Texture>().texid += 1;
							objs.GetComponent<Texture>().button_hover = false;
						}
					}
				}
				break;
			}
			case GameState::Htp2: {
				//change texture when hover
				if (name_data.tag == "Back_Button") {
					if (MouseCollisionChecked(Cursor_X, Cursor_Y, trans_data.global_min, trans_data.global_max)) {
						if (objs.GetComponent<Texture>().button_hover == false) {
							objs.GetComponent<Texture>().texid -= 1;
							objs.GetComponent<Texture>().button_hover = true;
						}
					}
					else {
						if (objs.GetComponent<Texture>().button_hover == true) {
							objs.GetComponent<Texture>().texid += 1;
							objs.GetComponent<Texture>().button_hover = false;
						}
					}
				}
				break;
			}
			case GameState::Quit: {
				//change texture when hover
				if (name_data.tag == "Yes_Button") {
					if (MouseCollisionChecked(Cursor_X, Cursor_Y, trans_data.global_min, trans_data.global_max)) {
						if (objs.GetComponent<Texture>().button_hover == false) {
							objs.GetComponent<Texture>().texid -= 1;
							objs.GetComponent<Texture>().button_hover = true;
						}
					}
					else {
						if (objs.GetComponent<Texture>().button_hover == true) {
							objs.GetComponent<Texture>().texid += 1;
							objs.GetComponent<Texture>().button_hover = false;
						}
					}
				}
				//change texture when hover
				if (name_data.tag == "No_Button") {
					if (MouseCollisionChecked(Cursor_X, Cursor_Y, trans_data.global_min, trans_data.global_max)) {
						if (objs.GetComponent<Texture>().button_hover == false) {
							objs.GetComponent<Texture>().texid -= 1;
							objs.GetComponent<Texture>().button_hover = true;
						}
					}
					else {
						if (objs.GetComponent<Texture>().button_hover == true) {
							objs.GetComponent<Texture>().texid += 1;
							objs.GetComponent<Texture>().button_hover = false;
						}
					}
				}
				break;
			}
			case GameState::CutScene: {
				//change texture when hover
				if (name_data.tag == "Skip_Button") {
					if (MouseCollisionChecked(Cursor_X, Cursor_Y, trans_data.global_min, trans_data.global_max)) {
						if (objs.GetComponent<Texture>().button_hover == false) {
							objs.GetComponent<Texture>().texid -= 1;
							objs.GetComponent<Texture>().button_hover = true;
						}
					}
					else {
						if (objs.GetComponent<Texture>().button_hover == true) {
							objs.GetComponent<Texture>().texid += 1;
							objs.GetComponent<Texture>().button_hover = false;
						}
					}
				}

				//change texture of the cut scene
				Cut_Scene_timer += ts;

				if (name_data.tag == "Cut_Scene(Background)") {
					auto& tex_data = objs.GetComponent<Texture>();
					if (Cut_Scene_timer <= (Scene_no + 1) * 3.f) {
						tex_data.texid = stash.Text_Storage["cut1.png"] + Scene_no;
					}
					else {
						Scene_no++;
					}
					if (Scene_no == 6) {
						m_State = GameState::Level1;
						std::string filepath = ("../Assets/Scene/Level0.json");
						SceneSerializer serializer(m_ActiveScene.get());
						serializer.Deserialize(filepath);
						bullet_timer += 0.2f;
						Cut_Scene_timer = 0.f;
						Scene_no = 0;
					}
				}
				break;
			}
			case GameState::Level1: {
				ScriptEngine::OnRuntimeStart(m_ActiveScene.get());
				if (!Sound_IsPlaying)
				{
					Sound_CurrChannel = CAudioEngine::PlaySound("../Assets/Audio/Game_BGM.wav");
					Sound_IsPlaying = true;
				}

				if (Sound_IsPlaying)
				{
					if (CAudioEngine::IsPlaying(Sound_CurrChannel))
					{
						Sound_IsPlaying = false;
					}
				}
				if (name_data.tag == "Player") {
					m_player = objs;
					// Sync the Camera with the Player
					Graphics::cam_stuff.translation.x = trans_data.translation.x;
					Graphics::cam_stuff.translation.y = trans_data.translation.y;
					// Mouse Following
					glm::vec2 A = glm::vec2(0, 1.f);
					glm::vec2 B = glm::vec2(Cursor_X, Cursor_Y);
					B.x -= trans_data.translation.x;
					B.y -= trans_data.translation.y;
					float dot_product = glm::dot(A, B);
					float angle = -acos(dot_product / (glm::length(A) * glm::length(B)));
					if ((B.x + trans_data.translation.x) < trans_data.translation.x)
						angle *= -1;
					trans_data.rotation = angle;
					Graphics::cam_stuff.rotation = (angle * -1.f);
					//KeyPress
					if (Input::IsKeyPressed(TH_KEY_W)) {
						trans_data.translation.y -= 1.f * ts;
						box_data.box_trans.translation.y -= 1.f * ts;
					}
					if (Input::IsKeyPressed(TH_KEY_S)) {
						trans_data.translation.y += 1.f * ts;
						box_data.box_trans.translation.y += 1.f * ts;
					}
					if (Input::IsKeyPressed(TH_KEY_A)) {
						trans_data.translation.x -= 1.f * ts;
						box_data.box_trans.translation.x -= 1.f * ts;
					}
					if (Input::IsKeyPressed(TH_KEY_D)) {
						trans_data.translation.x += 1.f * ts;
						box_data.box_trans.translation.x += 1.f * ts;
					}
					auto& combat_data = objs.GetComponent<CombatComponent>();
					//std::cout << combat_data.health << std::endl;
					if (combat_data.health <= 0) {
						m_State = GameState::GameOver;
						std::string filepath = ("../Assets/Scene/Gameover.json");
						SceneSerializer serializer(m_ActiveScene.get());
						serializer.Deserialize(filepath);
					}
				}
				
				if (bullet_timer >= 0.f) {
					bullet_timer -= ts;
				}

				if (name_data.tag == "Enemy")
				{
					if (objs.GetComponent<CombatComponent>().health > 0)
					{
						objs.GetComponent<AStarPathfindingAgent>().pathfindingEnabled = true;
					}
					else
					{
						objs.GetComponent<AStarPathfindingAgent>().pathfindingEnabled = false;
					}
					
				}

				if (name_data.tag == "Pickup") {
					auto& type = objs.GetComponent<ObjectType>();

					if (type.pickup_collide == true) {
						if (Input::IsKeyPressed(TH_KEY_E)) {
							m_player.GetComponent<ObjectType>().win_point += 1;
							m_ActiveScene->DestroyEntity(objs);
							break;
						}
					}
				}
				if (name_data.tag == "Goal") {
					auto& type = objs.GetComponent<ObjectType>();

					if (m_player.GetComponent<ObjectType>().win_point < 2) {
						type.win_collide = false;
					}
					else if (m_player.GetComponent<ObjectType>().win_point >= 2) {
						type.win_collide = true;
					}

					if (type.win_collide == true && m_player.GetComponent<ObjectType>().win_point == 10) {
						m_State = GameState::Level2;
						std::string filepath = ("../Assets/Scene/Level2.json");
						SceneSerializer serializer(m_ActiveScene.get());
						serializer.Deserialize(filepath);
						m_player.GetComponent<ObjectType>().win_point = 0;
					}
				}
				
				break;
			}
			case GameState::Level2: {
				if (name_data.tag == "Player") {
					m_player = objs;
					// Sync the Camera with the Player
					Graphics::cam_stuff.translation.x = trans_data.translation.x;
					Graphics::cam_stuff.translation.y = trans_data.translation.y;
					// Mouse Following
					glm::vec2 A = glm::vec2(0, 1.f);
					glm::vec2 B = glm::vec2(Cursor_X, Cursor_Y);
					B.x -= trans_data.translation.x;
					B.y -= trans_data.translation.y;
					float dot_product = glm::dot(A, B);
					float angle = -acos(dot_product / (glm::length(A) * glm::length(B)));
					if ((B.x + trans_data.translation.x) < trans_data.translation.x)
						angle *= -1;
					trans_data.rotation = angle;
					Graphics::cam_stuff.rotation = (angle * -1.f);
					//KeyPress
					if (Input::IsKeyPressed(TH_KEY_W)) {
						trans_data.translation.y -= 1.f * ts;
						box_data.box_trans.translation.y -= 1.f * ts;
					}
					if (Input::IsKeyPressed(TH_KEY_S)) {
						trans_data.translation.y += 1.f * ts;
						box_data.box_trans.translation.y += 1.f * ts;
					}
					if (Input::IsKeyPressed(TH_KEY_A)) {
						trans_data.translation.x -= 1.f * ts;
						box_data.box_trans.translation.x -= 1.f * ts;
					}
					if (Input::IsKeyPressed(TH_KEY_D)) {
						trans_data.translation.x += 1.f * ts;
						box_data.box_trans.translation.x += 1.f * ts;
					}

					auto& combat_data = objs.GetComponent<CombatComponent>();
					if (combat_data.health <= 0) {
						m_State = GameState::GameOver;
						std::string filepath = ("../Assets/Scene/Gameover.json");
						SceneSerializer serializer(m_ActiveScene.get());
						serializer.Deserialize(filepath);
					}
				}

				if (bullet_timer >= 0.f) {
					bullet_timer -= ts;
				}

				if (name_data.tag == "Enemy")
				{
					if (objs.GetComponent<CombatComponent>().health > 0)
					{
						objs.GetComponent<AStarPathfindingAgent>().pathfindingEnabled = true;
					}
					else
					{
						objs.GetComponent<AStarPathfindingAgent>().pathfindingEnabled = false;
					}

				}

				if (name_data.tag == "Pickup") {
					auto& type = objs.GetComponent<ObjectType>();

					if (type.pickup_collide == true) {
						if (Input::IsKeyPressed(TH_KEY_E)) {
							m_player.GetComponent<ObjectType>().win_point += 1;
							m_ActiveScene->DestroyEntity(objs);
							break;
						}
					}
				}
				if (name_data.tag == "Goal") {
					auto& type = objs.GetComponent<ObjectType>();

					if (m_player.GetComponent<ObjectType>().win_point < 2) {
						type.win_collide = false;
					}
					else if (m_player.GetComponent<ObjectType>().win_point >= 2) {
						type.win_collide = true;
					}

					if (type.win_collide == true && m_player.GetComponent<ObjectType>().win_point == 10) {
						m_State = GameState::Win;
						std::string filepath = ("../Assets/Scene/Win.json");
						SceneSerializer serializer(m_ActiveScene.get());
						serializer.Deserialize(filepath);
						m_player.GetComponent<ObjectType>().win_point = 0;
					}
				}
				break;
			}
			case GameState::GameOver: {
				Gameover_timer += ts;
				if (Gameover_timer >= 3.f) {
					m_State = GameState::MainMenu;
					filepath = ("../Assets/Scene/Mainmenu.json");
					SceneSerializer serializer(m_ActiveScene.get());
					serializer.Deserialize(filepath);
					Gameover_timer = 0.f;
				}
				break;
			}
			case GameState::Win: {
				Win_timer += ts;
				if (Win_timer >= 5.f) {
					m_State = GameState::MainMenu;
					filepath = ("../Assets/Scene/Mainmenu.json");
					SceneSerializer serializer(m_ActiveScene.get());
					serializer.Deserialize(filepath);
					Win_timer = 0.f;
				}
				break;
			}
			default:
				break;
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
						start = true;
						m_State = GameState::CutScene;
						std::string filepath = ("../Assets/Scene/CutScene.json");
						SceneSerializer serializer(m_ActiveScene.get());
						serializer.Deserialize(filepath);
					}
				}
				if (name_data.tag == "Credits_Button") {
					if (MouseCollisionChecked(GameMouse_X, GameMouse_Y, trans_data.global_min, trans_data.global_max)) {
						m_State = GameState::Credit1;
						std::string filepath = ("../Assets/Scene/Credits1.json");
						SceneSerializer serializer(m_ActiveScene.get());
						serializer.Deserialize(filepath);
					}
				}
				if (name_data.tag == "How_To_Play_Button") {
					if (MouseCollisionChecked(GameMouse_X, GameMouse_Y, trans_data.global_min, trans_data.global_max)) {
						m_State = GameState::Htp1;
						std::string filepath = ("../Assets/Scene/Howtoplay1.json");
						SceneSerializer serializer(m_ActiveScene.get());
						serializer.Deserialize(filepath);
					}
				}
				if (name_data.tag == "Exit_Button") {
					if (MouseCollisionChecked(GameMouse_X, GameMouse_Y, trans_data.global_min, trans_data.global_max)) {
						m_State = GameState::Quit;
						std::string filepath = ("../Assets/Scene/Confirmquit.json");
						SceneSerializer serializer(m_ActiveScene.get());
						serializer.Deserialize(filepath);
					}
				}
				break;
			}
			case GameState::Credit1: {
				if (name_data.tag == "Right_Button") {
					if (MouseCollisionChecked(GameMouse_X, GameMouse_Y, trans_data.global_min, trans_data.global_max)) {
						m_State = GameState::Credit2;
						std::string filepath = ("../Assets/Scene/Credits2.json");
						SceneSerializer serializer(m_ActiveScene.get());
						serializer.Deserialize(filepath);
					}
				}
				if (name_data.tag == "Back_Button") {
					if (MouseCollisionChecked(GameMouse_X, GameMouse_Y, trans_data.global_min, trans_data.global_max)) {
						m_State = GameState::MainMenu;
						std::string filepath = ("../Assets/Scene/Mainmenu.json");
						SceneSerializer serializer(m_ActiveScene.get());
						serializer.Deserialize(filepath);
					}
				}
				break;
			}
			case GameState::Credit2: {
				if (name_data.tag == "Left_Button") {
					if (MouseCollisionChecked(GameMouse_X, GameMouse_Y, trans_data.global_min, trans_data.global_max)) {
						m_State = GameState::Credit1;
						std::string filepath = ("../Assets/Scene/Credits1.json");
						SceneSerializer serializer(m_ActiveScene.get());
						serializer.Deserialize(filepath);
					}
				}
				if (name_data.tag == "Back_Button") {
					if (MouseCollisionChecked(GameMouse_X, GameMouse_Y, trans_data.global_min, trans_data.global_max)) {
						m_State = GameState::MainMenu;
						std::string filepath = ("../Assets/Scene/Mainmenu.json");
						SceneSerializer serializer(m_ActiveScene.get());
						serializer.Deserialize(filepath);
					}
				}
				break;
			}
			case GameState::Htp1: {
				if (name_data.tag == "Right_Button") {
					if (MouseCollisionChecked(GameMouse_X, GameMouse_Y, trans_data.global_min, trans_data.global_max)) {
						m_State = GameState::Htp2;
						std::string filepath = ("../Assets/Scene/Howtoplay2.json");
						SceneSerializer serializer(m_ActiveScene.get());
						serializer.Deserialize(filepath);
					}
				}
				if (name_data.tag == "Back_Button") {
					if (MouseCollisionChecked(GameMouse_X, GameMouse_Y, trans_data.global_min, trans_data.global_max)) {
						m_State = GameState::MainMenu;
						std::string filepath = ("../Assets/Scene/Mainmenu.json");
						SceneSerializer serializer(m_ActiveScene.get());
						serializer.Deserialize(filepath);
					}
				}
				break;
			}
			case GameState::Htp2: {
				if (name_data.tag == "Left_Button") {
					if (MouseCollisionChecked(GameMouse_X, GameMouse_Y, trans_data.global_min, trans_data.global_max)) {
						m_State = GameState::Htp1;
						std::string filepath = ("../Assets/Scene/Howtoplay1.json");
						SceneSerializer serializer(m_ActiveScene.get());
						serializer.Deserialize(filepath);
					}
				}
				if (name_data.tag == "Back_Button") {
					if (MouseCollisionChecked(GameMouse_X, GameMouse_Y, trans_data.global_min, trans_data.global_max)) {
						m_State = GameState::MainMenu;
						std::string filepath = ("../Assets/Scene/Mainmenu.json");
						SceneSerializer serializer(m_ActiveScene.get());
						serializer.Deserialize(filepath);
					}
				}
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
						m_State = GameState::MainMenu;
						std::string filepath = ("../Assets/Scene/Mainmenu.json");
						SceneSerializer serializer(m_ActiveScene.get());
						serializer.Deserialize(filepath);
					}
				}
				break;
			}
			case GameState::CutScene: {
				if (name_data.tag == "Skip_Button") {
					if (MouseCollisionChecked(GameMouse_X, GameMouse_Y, trans_data.global_min, trans_data.global_max)) {
						m_State = GameState::Level1;
						std::string filepath = ("../Assets/Scene/Level1.json");
						SceneSerializer serializer(m_ActiveScene.get());
						serializer.Deserialize(filepath);
						bullet_timer += 0.2f;
						Cut_Scene_timer = 0.f;
						Scene_no = 0;
					}
				}
				break;
			}
			case GameState::Level1: {

				//shoot bullet
				if (bullet_timer <= 0.f) {
					auto bullet = m_ActiveScene->CreateEntity("bullet");

					//set transform data
					auto& trans = bullet.GetComponent<Transform>();
					trans.scaling.x = 0.6f;
					trans.scaling.y = 0.6f;
					trans.translation.x = m_player.GetComponent<Transform>().translation.x;
					trans.translation.y = m_player.GetComponent<Transform>().translation.y;
					trans.rotation = m_player.GetComponent<Transform>().rotation;

					//set texture
					auto& tex = bullet.AddComponent<Texture>();
					tex.texid = stash.Text_Storage["rotten_core_glow_1.png"];
					tex.text_file = 132;
					tex.filename = "rotten_core_glow_1.png";
					
					//set bounding box data
					auto& box = bullet.GetComponent<Box_collider>();
					box.box_tog = 0;
					box.box_trans.scaling.x = 0.4f;
					box.box_trans.scaling.y = 0.4f;
					box.box_trans.translation.x = m_player.GetComponent<Transform>().translation.x;
					box.box_trans.translation.y = m_player.GetComponent<Transform>().translation.y;

					auto& bullet_data = bullet.AddComponent<BulletComponent>();
					bullet_data.speed = 0.5f;
					bullet_data.time = 1.5f;

					auto& type = bullet.AddComponent<ObjectType>();
					type.type = ObjectTypeID::bullet;

					auto& combat = bullet.AddComponent<CombatComponent>();
					combat.attack = 1.f;

					auto& box_collider2d = bullet.AddComponent<BoxCollider2D>();
					auto& data = bullet.AddComponent<RigidBody>();
					box_collider2d.verticesList.push_back(box.box_trans.global_vertice0);
					box_collider2d.verticesList.push_back(box.box_trans.global_vertice1);
					box_collider2d.verticesList.push_back(box.box_trans.global_vertice2);
					box_collider2d.verticesList.push_back(box.box_trans.global_vertice3);

					//bullet movement direction based on the mouse position and center of the screen
					if (((Input::GetMouseX() / Application::Get().GetWindow().GetWidth() - 0.5f) * 4) >= 0.f) {
						bullet_data.dir.x = cosf(static_cast <float>(-trans.rotation - M_PI / 2.f));
						bullet_data.dir.y = sinf(static_cast <float>(-trans.rotation - M_PI / 2.f));
					}
					else if (((Input::GetMouseX() / Application::Get().GetWindow().GetWidth() - 0.5f) * 4) < 0.f) {
						bullet_data.dir.x = -cosf(static_cast <float>(-trans.rotation - (3.f * M_PI) / 2.f));
						bullet_data.dir.y = -sinf(static_cast <float>(-trans.rotation - (3.f * M_PI) / 2.f));
					}
					bullet_timer += 0.5f;
				}
				break;
			}
			case GameState::Level2: {

				//shoot bullet
				if (bullet_timer <= 0.f) {
					auto bullet = m_ActiveScene->CreateEntity("bullet");

					//set transform data
					auto& trans = bullet.GetComponent<Transform>();
					trans.scaling.x = 0.6f;
					trans.scaling.y = 0.6f;
					trans.translation.x = m_player.GetComponent<Transform>().translation.x;
					trans.translation.y = m_player.GetComponent<Transform>().translation.y;
					trans.rotation = m_player.GetComponent<Transform>().rotation;

					//set texture
					auto& tex = bullet.AddComponent<Texture>();
					tex.texid = stash.Text_Storage["rotten_core_glow_1.png"];
					tex.text_file = 132;
					tex.filename = "rotten_core_glow_1.png";

					//set bounding box data
					auto& box = bullet.GetComponent<Box_collider>();
					box.box_tog = 0;
					box.box_trans.scaling.x = 0.4f;
					box.box_trans.scaling.y = 0.4f;
					box.box_trans.translation.x = m_player.GetComponent<Transform>().translation.x;
					box.box_trans.translation.y = m_player.GetComponent<Transform>().translation.y;

					auto& bullet_data = bullet.AddComponent<BulletComponent>();
					bullet_data.speed = 0.5f;
					bullet_data.time = 1.5f;

					auto& type = bullet.AddComponent<ObjectType>();
					type.type = ObjectTypeID::bullet;

					auto& combat = bullet.AddComponent<CombatComponent>();
					combat.attack = 1.f;

					auto& box_collider2d = bullet.AddComponent<BoxCollider2D>();
					auto& data = bullet.AddComponent<RigidBody>();
					box_collider2d.verticesList.push_back(box.box_trans.global_vertice0);
					box_collider2d.verticesList.push_back(box.box_trans.global_vertice1);
					box_collider2d.verticesList.push_back(box.box_trans.global_vertice2);
					box_collider2d.verticesList.push_back(box.box_trans.global_vertice3);

					//bullet movement direction based on the mouse position and center of the screen
					if (((Input::GetMouseX() / Application::Get().GetWindow().GetWidth() - 0.5f) * 4) >= 0.f) {
						bullet_data.dir.x = cosf(static_cast <float>(-trans.rotation - M_PI / 2.f));
						bullet_data.dir.y = sinf(static_cast <float>(-trans.rotation - M_PI / 2.f));
					}
					else if (((Input::GetMouseX() / Application::Get().GetWindow().GetWidth() - 0.5f) * 4) < 0.f) {
						bullet_data.dir.x = -cosf(static_cast <float>(-trans.rotation - (3.f * M_PI) / 2.f));
						bullet_data.dir.y = -sinf(static_cast <float>(-trans.rotation - (3.f * M_PI) / 2.f));
					}
					bullet_timer += 0.5f;
				}
				break;
			}
			case GameState::Pause: {

				break;
			}
			default:
				break;
			}
		}
	}
	return false;
}

bool Canvas2D::OnKeyPressed(Thomas::KeyPressedEvent& e) {
	//if (e.GetKeyCode() == TH_KEY_ESCAPE) {
	//	if (m_State == GameState::Level1 || m_State == GameState::Level2) {
	//		m_State = GameState::Pause;
	//	}
	//}
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


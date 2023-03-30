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
Fonts fps_Display;
float Level_start_timer = 0.f;
bool Level_start_scene = false;
float volume = 5.0f;
float posion_length{};
Fonts recipe_Display;
int recipe_collected = 0;


std::string g_GameName = "Rotten Madness";

Canvas2D::Canvas2D()
	: Layer("Canvas2D")
{
}

void Canvas2D::OnAttach()
{	
	Application::Get().SetWindowTitle(g_GameName);
	m_ActiveScene = std::make_shared<Thomas::Scene>();	
	//filepath = ("../Assets/Scene/New_MainMenu.json");
	filepath = stash.Scene_Storage["New_MainMenu.json"];
	SceneSerializer serializer(m_ActiveScene.get());
	serializer.Deserialize(filepath);
	
	FramebufferSpec fbSpec;
	fbSpec.Width = static_cast<uint32_t>(Graphics::width * Graphics::cam_stuff.scaling.y);
	fbSpec.Height = static_cast<uint32_t>(Graphics::height * Graphics::cam_stuff.scaling.y);
	m_Framebuffer = std::make_shared<Framebuffer>(fbSpec);

	fps_Display.font_type = stash.Font_Storage["FFF_Tusj.ttf"];
	fps_Display.Fonts_init();

	recipe_Display.font_type = stash.Font_Storage["FFF_Tusj.ttf"];
	recipe_Display.Fonts_init();

	std::map<EntityID, Signature> group = m_ActiveScene->GetRegistry()->GetEntities();

	
	CAudioEngine::curr_volume = 1.0f; // do not remove
	CAudioEngine::currSFX_volume = 0.8f;//do not remove
	
}

void Canvas2D::OnDetach()
{
	m_ActiveScene->DestroyAllEntities();
}


void Canvas2D::OnUpdate(Thomas::Timestep ts)
{
	
	Graphics::cam_stuff.Camera2D_Update();

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//std::stringstream fps_text;
	//fps_text << "FPS: " << Application::fps;
	//fps_Display.RenderText(fps_text.str(), 25.f, 910, 1.f, 0.0f, glm::vec3(0.5f, 0.5f, 0.f));
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
	TH_CORE_INFO("Canvas {0}", e.ToString());
	return false;
}

bool Canvas2D::OnKeyPressed(Thomas::KeyPressedEvent& e) {
	//if (e.GetKeyCode() == TH_KEY_ESCAPE) {
	//	if (m_State == GameState::Level1 || m_State == GameState::Level2) {
	//		m_State = GameState::Pause;
	//	}
	//}
	TH_CORE_INFO("Canvas {0}", e.ToString());
	return false;
}

bool Canvas2D::OnWindowResize(Thomas::WindowResizeEvent& e)
{
	//CreateCamera(e.GetWidth(), e.GetHeight());
	TH_CORE_INFO("Canvas {0}", e.ToString());
	return false;
}

//void Canvas2D::CreateCamera(uint32_t width, uint32_t height)
//{
//	float aspectRatio = (float)width / (float)height;
//	float camWidth = 8.0f;
//	float bottom = -camWidth;
//	float top = camWidth;
//	//float left = bottom * aspectRatio;
//	//float right = top * aspectRatio;
//}

bool Canvas2D::MouseCollisionChecked(float Cur_X, float Cur_Y, glm::vec2 min_pos, glm::vec2 max_pos){
	if (Cur_X >= min_pos.x && Cur_Y >= min_pos.y && Cur_X <= max_pos.x && Cur_Y <= max_pos.y)
		return true;
	else
		return false;
}


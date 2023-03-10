/*!*************************************************************************
\file           Canvas2D.h
\author         Chen XinPeng
\par DP email:  c.xinpeng@digipen.edu
\par Programming CSD2400 Game project
\date           28/11/2022
\brief			This file contains declaration for function in Canvas2D.cpp

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************/
#pragma once

#include "Thomas.h"
#include "Thomas/Scene/Entity.h"
#include "Thomas/Renderer/Transform.h"
#include "Thomas/Renderer/Camera.h"
//#include <imgui/imgui.h>
#include "Thomas/Audio/AudioEngine.h"
#include "Thomas/Scene/Scene.h"


class Canvas2D : public Thomas::Layer
{
public:

	enum class GameState
	{
		MainMenu,
		Settings,
		Credit1,
		Credit2,
		Htp1,
		Htp2,
		Quit,
		CutScene,
		Level1,
		Level2,
		Pause,
		GameOver,
		Win
	};

	Canvas2D();
	virtual ~Canvas2D() = default;

	virtual void OnAttach()override;
	virtual void OnDetach()override;

	void OnUpdate(Thomas::Timestep ts)override;
	virtual void OnImGuiRender()override;
	void OnEvent(Thomas::Event& e)override;
	bool OnMouseButtonPressed(Thomas::MouseButtonPressedEvent& e);
	bool OnWindowResize(Thomas::WindowResizeEvent& e);
	bool OnKeyPressed(Thomas::KeyPressedEvent& e);
	bool MouseCollisionChecked(float Cursor_X, float Cursor_Y, glm::vec2 min_pos, glm::vec2 max_pos);

	GameState& GetState() { return m_State; };

//private:
	//void CreateCamera(uint32_t width, uint32_t height);
private:
	//Thomas::Scope<Thomas::OrthographicCamera> m_Camera;
	//Level m_Level;
	//ImFont* m_Font;
	float m_Time = 0.0f;

	std::shared_ptr <Thomas::Framebuffer> m_Framebuffer;
	std::shared_ptr<Thomas::Scene> m_ActiveScene;
	Thomas::GameObjectFactory factory;
	Thomas::Entity m_background;
	Thomas::Entity m_player;
	Thomas::Entity m_enemy;
	Thomas::Entity m_enemy2;

	bool Sound_IsPlaying = false;
	int Sound_CurrChannel = 0;

	int Sound_mm = 0;
	

	GameState m_State = GameState::MainMenu;
};


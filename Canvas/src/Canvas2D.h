#pragma once

#include "Thomas.h"
#include "Thomas/Scene/Entity.h"
#include "Level.h"
#include <imgui/imgui.h>

#include "Thomas/Scene/Scene.h"


class Canvas2D : public Thomas::Layer
{
public:
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
	
private:
	//std::shared_ptr<Thomas::Scene> m_ActiveScene;
	//camera controller

private:
	void CreateCamera(uint32_t width, uint32_t height);
private:
	//Thomas::Scope<Thomas::OrthographicCamera> m_Camera;
	Level m_Level;
	ImFont* m_Font;
	float m_Time = 0.0f;
	bool m_Blink = false;

	std::shared_ptr <Thomas::Framebuffer> m_Framebuffer;
	std::shared_ptr<Thomas::Scene> m_ActiveScene;
	Thomas::GameObjectFactory factory;
	Thomas::Entity m_background;
	Thomas::Entity m_player;
	
	//Thomas::Entity m_start_button;
	//Thomas::Entity m_resume_button;
	//Thomas::Entity m_quit_button;

	enum class GameState
	{
		Play = 0, 
		MainMenu, 
		GameOver, 
		Pause, 
		Quit, 
		Htp
	};

	GameState m_State = GameState::MainMenu;
};


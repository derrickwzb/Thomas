#pragma once

#include "Thomas.h"

#include "Level.h"
#include <imgui/imgui.h>

#include "Thomas/Scene/Scene.h"

class GameLayer : public Thomas::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Thomas::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Thomas::Event& e) override;
	bool OnMouseButtonPressed(Thomas::MouseButtonPressedEvent& e);
	bool OnWindowResize(Thomas::WindowResizeEvent& e);
private:
	void CreateCamera(uint32_t width, uint32_t height);
private:
	//Thomas::Scope<Thomas::OrthographicCamera> m_Camera;
	Level m_Level;
	ImFont* m_Font;
	float m_Time = 0.0f;
	bool m_Blink = false;

	std::shared_ptr<Thomas::Scene> m_ActiveScene;
	Thomas::GameObjectFactory factory;
	Thomas::Entity* m_player = nullptr;

	enum class GameState
	{
		Play = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_State = GameState::MainMenu;
};
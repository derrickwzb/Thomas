#pragma once
#include "../ScriptUtils.h"
#include "../Managers/GameManager.h"
#include "../Managers/AudioManager.h"

class Button : public Thomas::ScriptableEntity
{
public:

	bool CheckBounds(float Cursor_X, float Cursor_Y, glm::vec2 min_pos, glm::vec2 max_pos) {
	if (Cursor_X >= min_pos.x && Cursor_Y >= min_pos.y && Cursor_X <= max_pos.x && Cursor_Y <= max_pos.y)
		return true;
	else
		return false;
}

	void OnCreate()
	{
		TH_CORE_INFO("Button Script Instantiated. ");
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		float Cursor_X = Thomas::Input::GetMouseX() - Thomas::Graphics::width / 2;
		float Cursor_Y = -(Thomas::Input::GetMouseY() - Thomas::Graphics::height / 2);
		auto& data = GetComponent<Thomas::Texture>();
		auto& trans = GetComponent<Thomas::Transform>();

		if (CheckBounds(Cursor_X, Cursor_Y, trans.global_min, trans.global_max))
		{
			if (data.button_hover == false) {
				data.texid -= 1;
				data.button_hover = true;
			}
			if (Thomas::Input::IsMouseButtonPressed(TH_MOUSE_BUTTON_LEFT))
			{
				TH_CORE_INFO("button pressed");
				std::string ButtonName = GetComponent<Thomas::TagComponent>().tag;
				if (ButtonName == "Button_Play")
				{
					g_gameStateNext = GameState::Level1;
				}
				else if (ButtonName == "Button_Credits")
				{
					g_gameStateNext = GameState::Credits;
				}
				else if (ButtonName == "Button_HTP")
				{
					g_gameStateNext = GameState::HTP1;
				}
				else if (ButtonName == "Button_Next")
				{
					if (g_gameStateCurr == GameState::HTP1)
					{
						g_gameStateNext = GameState::HTP2;
					}
					else if (g_gameStateCurr == GameState::Credits)
					{
						g_gameStateNext = GameState::Credits_2;
					}
				}
				else if (ButtonName == "Button_Back")
				{
					g_gameStateNext = g_gameStatePrev;
				}
				else if (ButtonName == "Button_Yes")
				{
					g_gameStateNext = GameState::Exit;
				}
				else if (ButtonName == "Button_No")
				{
					g_gameStateNext = g_gameStatePrev;
				}
				else if (ButtonName == "Button_Exit")
				{
					g_gameStateNext = GameState::QuitConfirmation;
				}
				else if (ButtonName == "Button_Skip")
				{
					g_gameStateNext = GameState::Level1;
				}
				else if (ButtonName == "Button_Plus")
				{
					curr_volume = curr_volume + (max_volume * 0.1f);
				}
				else if (ButtonName == "Button_Minus")
				{
					curr_volume = curr_volume - (max_volume * 0.1f);
				}
			}
		}
		else 
		{
			if (data.button_hover == true) {
				data.texid += 1;
				data.button_hover = false;
			}
		}
	}

	void OnDestroy()
	{

	}

};
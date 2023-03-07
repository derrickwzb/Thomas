#pragma once
#include "../ScriptUtils.h"
#include "../Managers/GameManager.h"
#include "../Managers/AudioManager.h"

class Button : public Thomas::ScriptableEntity
{
public:

	bool IsClicked = false;

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
			auto& name = GetComponent<Thomas::TagComponent>().tag;
			if (name != "Button_Right" && name != "Button_Left" && name != "Button_Plus" && name != "Button_Minus")
			{
				if (data.button_hover == false) {
					data.texid -= 1;
					data.button_hover = true;
				}
			}
			
			if (Thomas::Input::IsMouseButtonPressed(TH_MOUSE_BUTTON_LEFT))
			{
				TH_CORE_INFO("button pressed");
				std::string ButtonName = GetComponent<Thomas::TagComponent>().tag;
				if (ButtonName == "Button_Play")
				{
					if (!g_IsPaused && g_gameStateCurr == GameState::MainMenu)
					g_gameStateNext = GameState::Level1;
				}
				else if (ButtonName == "Button_Credits")
				{
					if (!g_IsPaused && g_gameStateCurr == GameState::MainMenu)
					g_gameStateNext = GameState::Credits;
				}
				else if (ButtonName == "Button_HTP")
				{
					if(!g_IsPaused && g_gameStateCurr == GameState::MainMenu)
					g_gameStateNext = GameState::HTP1;
				}
				else if (ButtonName == "Button_Right")
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
				else if (ButtonName == "Button_Left")
				{
					if (g_gameStateCurr == GameState::HTP2)
					{
						g_gameStateNext = GameState::HTP1;
					}
					else if (g_gameStateCurr == GameState::Credits_2)
					{
						g_gameStateNext = GameState::Credits;
					}
				}
				else if (ButtonName == "Button_Back")
				{
					g_gameStateNext = g_gameStatePrev;
				}
				else if (ButtonName == "Button_QuitConfirm_Yes")
				{
					g_gameStateNext = GameState::Exit;
					//g_IsPaused = true;
				}
				else if (ButtonName == "Button_QuitConfirm_No")
				{
					Thomas::SceneSerializer serializer(GetScene());
					serializer.RemoveScene(Thomas::stash.Scene_Storage["New_QuitConfirm.json"]);
					//g_IsPaused = false;
				}
				else if (ButtonName == "Button_Exit")
				{
					if (!g_IsPaused && g_gameStateCurr == GameState::MainMenu)
					{
						Thomas::SceneSerializer serializer(GetScene());
						serializer.LoadScene(Thomas::stash.Scene_Storage["New_QuitConfirm.json"]);
					}
				}
				else if (ButtonName == "Button_Skip")
				{
					g_gameStateNext = GameState::Level1;
				}
				else if (ButtonName == "Button_Plus")
				{
					if (Thomas::CAudioEngine::curr_volume < max_volume) {
						Thomas::CAudioEngine::curr_volume += (max_volume * 0.1f);
					}
					else if (Thomas::CAudioEngine::curr_volume == min_volume) {
						Thomas::CAudioEngine::curr_volume = max_volume;
					}
					//std::cout << Thomas::CAudioEngine::curr_volume << std::endl;
					IsClicked = true;
				}
				else if (ButtonName == "Button_Minus")
				{
					if (Thomas::CAudioEngine::curr_volume > min_volume) {
						Thomas::CAudioEngine::curr_volume -= (max_volume * 0.1f);
					}
					else if (Thomas::CAudioEngine::curr_volume == min_volume) {
						Thomas::CAudioEngine::curr_volume = min_volume;
					}

					IsClicked = true;
					//std::cout << Thomas::CAudioEngine::curr_volume << std::endl;
				}
				else if (ButtonName == "Button_Pause_Resume")
				{
					Thomas::SceneSerializer serializer(GetScene());
					serializer.RemoveScene(Thomas::stash.Scene_Storage["New_PauseMenu.json"]);
					g_IsPaused = false;

				}
				else if (ButtonName == "Button_Pause_MainMenu")
				{
					g_gameStateNext = GameState::MainMenu;
					g_IsPaused = false;

				}
				else if (ButtonName == "Button_Pause_Exit")
				{
					/*Thomas::SceneSerializer serializer(GetScene());
					serializer.LoadScene(Thomas::stash.Scene_Storage["New_QuitConfirm.json"]);*/
					g_gameStateNext = GameState::Exit;
					//g_IsPaused = false;

				}
				else if (ButtonName == "Button_Settings")
				{
					if (!g_IsPaused && g_gameStateCurr == GameState::MainMenu)
					g_gameStateNext = GameState::Settings;

				}
				else if (ButtonName == "Button_MainMenu")
				{
					if (!g_IsPaused && g_gameStateCurr != GameState::MainMenu)
					g_gameStateNext = GameState::MainMenu;
				}
			}
		}
		else 
		{
			std::string ButtonName = GetComponent<Thomas::TagComponent>().tag;
			if (ButtonName != "Button_Right" || ButtonName != "Button_Left" || ButtonName != "Button_Plus" || ButtonName != "Button_Minus")
			{
				if (data.button_hover == true) {
					data.texid += 1;
					data.button_hover = false;
				}
			}
		}

		IsClicked = false;
	}

	void OnDestroy()
	{

	}

};
#pragma once
#include "../ScriptUtils.h"

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
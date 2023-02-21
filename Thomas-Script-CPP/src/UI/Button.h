#pragma once
#include "../ScriptUtils.h"

class Button : public Thomas::ScriptableEntity
{
public:

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

		/*if (Checkcol(Cursor_X, Cursor_Y, trans.global_min, trans.global_max))
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
		}*/
	}

	void OnDestroy()
	{

	}

};
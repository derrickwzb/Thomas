#include "thpch.h"
#include "WindowsInput.h"
#include "Thomas/Core/application.h"

#include <GLFW/glfw3.h>

namespace Thomas 
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	bool WindowsInput::IsMouseButtonReleasedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_RELEASE;
	}
	bool WindowsInput::IsMouseButtonClickedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		static int oldState = GLFW_RELEASE;
		if (IsMouseButtonPressedImpl(button))
		{
			oldState = GLFW_PRESS;
		}
		int newState = glfwGetMouseButton(window, button);
		if (newState == GLFW_RELEASE && oldState == GLFW_PRESS) {
			// whatever
			oldState = newState;
			return true;
		}
		return false;
		
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto[x,y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto[x,y] = GetMousePositionImpl();
		return y;
	}

	void Input::Delete_Input() {
		delete s_Instance;
	}
}
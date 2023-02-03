#pragma once
#include "Thomas/Core/Window.h"

#include "GLFW/glfw3.h"

#include "Thomas/Renderer/GraphicsContext.h"


namespace Thomas
{

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetFullscreen() const override {
			TH_CORE_WARN("WINDOW : Set to Fullscreen.");
			return glfwSetWindowMonitor(m_Window,
				glfwGetPrimaryMonitor(),
				0,
				0,
				m_Data.Width,
				m_Data.Height,
				GLFW_REFRESH_RATE
			);
		}
		
		inline void SetWindowed() const override {

			TH_CORE_WARN("WINDOW : Set to Borderless Window.");
			return glfwSetWindowMonitor(m_Window,
				NULL,
				0,
				0,
				m_Data.Width,
				m_Data.Height,
				GLFW_REFRESH_RATE
			);
		}

		inline GLFWwindow* GetWindowPtr() { return m_Window; }


		//window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; };
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;

		GraphicsContext* m_Context;	

		struct WindowData
		{
			std::string title;
			unsigned int Width{}, Height{};
			bool VSync{true};
			bool maximized{ true };
			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

	};
}



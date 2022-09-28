#pragma once

#include "Thomas/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Thomas
{
	class OpenGLContext : public GraphicsContext
	{
	public:

		//handle to the windows on construct to be able to control things in the context
		OpenGLContext(GLFWwindow* WindowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override; \

			void PrintSpecs();
		

	private:
		GLFWwindow* m_WindowHandle;
	};

}
#include "thpch.h"

#include "OpenGLContext.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace Thomas
{
	OpenGLContext::OpenGLContext(GLFWwindow* WindowHandle)
		:m_WindowHandle(WindowHandle)
	{
	}
	void OpenGLContext::Init()

	{	
		glfwMakeContextCurrent(m_WindowHandle);

		//GLEW INIT
		GLenum err = glewInit();
		TH_CORE_ASSERT(!err, "Failed to initialize GLEW!");

		/*if (GLEW_OK != err)
		{
			TH_CORE_ERROR("Unable to initialize GLEW - error: {0} abort program", (err));
		}*/
		//print out opengl specs
		PrintSpecs();


	}
	void OpenGLContext::SwapBuffers()
	{

	/*	glBegin(GL_TRIANGLES);
		glEnd();*/
		glfwSwapBuffers(m_WindowHandle);
	}


	void OpenGLContext::PrintSpecs()
	{
		GLubyte const* gpuvendorstr = glGetString(GL_VENDOR);
		GLubyte const* glrendererstr = glGetString(GL_RENDERER);
		GLubyte const* glversionstr = glGetString(GL_VERSION);
		GLubyte const* glshaderversonstr = glGetString(GL_SHADING_LANGUAGE_VERSION);\

		GLint int_1;
		glGetIntegerv(GL_MAJOR_VERSION, &int_1);
		GLint int_2;
		glGetIntegerv(GL_MINOR_VERSION, &int_2);
		GLint int_3;
		glGetIntegerv(GL_DOUBLEBUFFER, &int_3);
		GLint int_4;
		glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &int_4);
		GLint int_5;
		glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &int_5);
		GLint int_6;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &int_6);
		GLint int_7[2];
		glGetIntegerv(GL_MAX_VIEWPORT_DIMS, int_7);

		TH_CORE_INFO("GPU Vendor: {0}", gpuvendorstr);
		TH_CORE_INFO("GL Renderer: {0}", glrendererstr);
		TH_CORE_INFO("GL Version: {0}", glversionstr);
		TH_CORE_INFO("GL Shader Version: {0}", glshaderversonstr);
		TH_CORE_INFO("GL Major Version: {0}", (int)int_1);
		TH_CORE_INFO("GL Minor Version: {0}", (int)int_2);
		if (int_3 == 1) {
			TH_CORE_INFO("Current OpenGL Context is double buffered");
		}
		else
		{
			TH_CORE_INFO("Current OpenGL Context is NOT double buffered");
		}
		
		TH_CORE_INFO("Maximum Vertex Count: {0}", (unsigned long long)int_4);
		TH_CORE_INFO("Maximum Indices Count: {0}", (unsigned long long)int_5);
		TH_CORE_INFO("GL Maximum texture size: {0}", (unsigned long long)int_6);
		TH_CORE_INFO("Maximum Viewport Dimensions: {0}", (unsigned long long)int_7);
	}
}
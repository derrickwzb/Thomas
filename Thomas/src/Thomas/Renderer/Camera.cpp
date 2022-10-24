#include "thpch.h"
#include "Thomas/Renderer/Camera.h"
namespace Thomas {
	void Camera::Camera2D_Init() {
		GLFWwindow* r_Window;
		r_Window = glfwGetCurrentContext();
		GLsizei fb_width, fb_height;
		glfwGetFramebufferSize(r_Window, &fb_width, &fb_height);
		float ar = static_cast<GLfloat>(fb_width) / fb_height;
		glm::mat3 view_xform = { 1,0,0,0,1,0,(translation.x * ar) - translation.x,0,1 };
		glm::mat3 camwin_to_ndc_xform = { 1 / ar,0,0,0,-1,0,0,0,1 };
		world_to_ndc_xform = camwin_to_ndc_xform * view_xform;
	}
}
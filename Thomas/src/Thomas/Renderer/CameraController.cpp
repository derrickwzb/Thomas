#include "thpch.h"
#include "CameraController.h"
#include "Thomas/Core/Input.h"
#include "Thomas/Core/KeyCodes.h"

namespace Thomas
{
	CameraController::CameraController(float aspectratio, bool rotation)
		:m_AspectRatio(aspectratio) , m_Rotation(rotation)
	{

	}

	void CameraController::OnUpdate(Timestep ts)
	{
		//auto& transform = GetComponent<Transform>().translation;
		//float speed = 5.0f;

		//if (Input::IsKeyPressed(TH_KEY_W)) {
		//	transform.y += speed * ts;
		//}
		//if (Input::IsKeyPressed(TH_KEY_S)) {
		//	transform.y -= speed * ts;
		//}
		//if (Input::IsKeyPressed(TH_KEY_A)) {
		//	transform.x -= speed * ts;
		//}
		//if (Input::IsKeyPressed(TH_KEY_D)) {
		//	transform.x += speed * ts;
		//}
	}

	void CameraController::OnEvent(Event& e)
	{

	}

	void CameraController::OnResize(float width, float height)
	{

	}

	bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		return false;
	}

	bool CameraController::OnWindowResized(WindowResizeEvent& e)
	{
		return false;
	}

	//camera constructor need change
	//m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),

}
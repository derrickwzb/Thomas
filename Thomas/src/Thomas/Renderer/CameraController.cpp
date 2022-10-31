#include "thpch.h"
#include "CameraController.h"


namespace Thomas
{
	CameraController::CameraController(float aspectratio, bool rotation)
		:m_AspectRatio(aspectratio) , m_Rotation(rotation)
	{

	}

	void CameraController::OnUpdate(Timestep ts)
	{

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
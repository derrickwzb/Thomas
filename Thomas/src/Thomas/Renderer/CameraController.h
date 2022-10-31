#pragma once

#include "Thomas/Renderer/Camera.h"
#include "Thomas/Core/Timestep.h"

#include "Thomas/Events/ApplicationEvent.h"
#include "Thomas/Events/MouseEvent.h"

namespace Thomas {

	class CameraController
	{
	public:
		CameraController(float aspectratio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);

		Camera& GetCamera() { return m_Camera; }
		const Camera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		Camera m_Camera;
		float m_ZoomLevel = 1.0f;
		float m_AspectRatio;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};

}


